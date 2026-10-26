"""Student Dropout Prediction | Deep Learning Course Project | Roll Nos. 46, 47, 48.

Train:   python dropout_prediction.py
Predict: python dropout_prediction.py --predict new_students.csv

Binary task: Dropout=1, Graduate=0. Enrolled outcomes are unresolved and are
excluded from supervised training/evaluation. See SUBMISSION_GUIDE.txt.
"""

# %% 1. Imports and configuration
import argparse
import copy
import hashlib
import json
import platform
import random
from dataclasses import asdict, dataclass
from pathlib import Path

import joblib
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sklearn
import torch
from sklearn.compose import ColumnTransformer
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import (
    ConfusionMatrixDisplay, accuracy_score, average_precision_score,
    balanced_accuracy_score, brier_score_loss, classification_report,
    confusion_matrix, f1_score, fbeta_score, log_loss, precision_score,
    recall_score, roc_auc_score, roc_curve,
)
from sklearn.model_selection import StratifiedKFold, train_test_split
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from torch import nn
from torch.utils.data import DataLoader, TensorDataset


@dataclass
class Config:
    seed: int = 42
    epochs: int = 200
    patience: int = 20
    batch_size: int = 64
    learning_rate: float = 0.001
    weight_decay: float = 0.001
    cv_folds: int = 5       # Use 0 to skip; test records never enter CV.
    permutation_repeats: int = 5


# These are category IDs, even though the CSV stores them as integers.
NOMINAL = [
    "Marital status", "Application mode", "Course", "Previous qualification",
    "Nacionality", "Mother's qualification", "Father's qualification",
    "Mother's occupation", "Father's occupation",
]
OTHER_FEATURES = [
    "Application order", "Daytime/evening attendance", "Displaced",
    "Educational special needs", "Debtor", "Tuition fees up to date", "Gender",
    "Scholarship holder", "Age at enrollment", "International",
    "Unemployment rate", "Inflation rate", "GDP",
]
SEMESTER_FEATURES = [
    f"Curricular units {semester} sem ({measure})"
    for semester in ("1st", "2nd")
    for measure in ("credited", "enrolled", "evaluations", "approved", "grade",
                    "without evaluations")
]
FEATURES = NOMINAL + OTHER_FEATURES + SEMESTER_FEATURES
COLORS = {"early": "#c44949", "full": "#2879b9"}
NAMES = {"early": "First-semester", "full": "Through second semester"}


def set_seed(seed):
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.set_num_threads(1)  # Efficient, reproducible CPU training on small data.
    torch.use_deterministic_algorithms(True)


# %% 2. Data validation and stratified train/validation/test split
def read_features(path, columns):
    """Read real CSV data. A missing file is an error; no synthetic fallback."""
    path = Path(path)
    if not path.is_file():
        raise FileNotFoundError(f"Dataset not found: {path.resolve()}")
    frame = pd.read_csv(path, sep=None, engine="python", encoding="utf-8-sig")
    frame.columns = frame.columns.str.strip()
    if frame.columns.duplicated().any():
        raise ValueError("Duplicate column names after whitespace removal.")
    missing = sorted(set(columns) - set(frame.columns))
    if missing:
        raise ValueError(f"Required columns missing: {missing}")
    if frame.empty:
        raise ValueError("The input CSV contains no student records.")
    for col in columns:
        frame[col] = pd.to_numeric(frame[col], errors="raise")
    values = frame[columns].to_numpy(dtype=float)
    if np.isinf(values).any():
        raise ValueError("Infinite feature values found; correct the CSV first.")
    return frame


def load_dataset(path):
    frame = read_features(path, FEATURES)
    if "Target" not in frame:
        raise ValueError("Training requires the Target column.")
    frame["Target"] = frame["Target"].astype("string").str.strip().str.lower()
    if frame["Target"].isna().any():
        raise ValueError("Missing target labels found.")
    unknown = set(frame["Target"].unique()) - {"graduate", "dropout", "enrolled"}
    if unknown:
        raise ValueError(f"Unsupported Target values: {sorted(unknown)}")
    duplicates = frame.duplicated(subset=FEATURES + ["Target"])
    # The index is the original zero-based CSV data-row position (not student ID).
    frame = frame.loc[~duplicates, FEATURES + ["Target"]].copy()
    counts = frame["Target"].value_counts().to_dict()
    if min(counts.get("graduate", 0), counts.get("dropout", 0)) < 30:
        raise ValueError("At least 30 resolved examples of each class are required.")
    audit = {
        "rows_used": len(frame), "raw_features": len(FEATURES),
        "removed_exact_duplicates": int(duplicates.sum()),
        "missing_feature_cells": int(frame[FEATURES].isna().sum().sum()),
        "label_counts": counts,
        "dataset_sha256": hashlib.sha256(Path(path).read_bytes()).hexdigest(),
    }
    return frame, audit


def split_dataset(frame, seed):
    resolved = frame.index[frame["Target"] != "enrolled"].to_numpy()
    y = frame["Target"].eq("dropout").astype(int)
    development, test = train_test_split(
        resolved, test_size=0.20, stratify=y.loc[resolved], random_state=seed)
    train, validation = train_test_split(
        development, test_size=0.25, stratify=y.loc[development], random_state=seed)
    # 60% train / 20% validation / 20% test of resolved outcomes.
    splits = {"train": train, "validation": validation, "test": test}
    assert not (set(train) & set(validation) or set(train) & set(test)
                or set(validation) & set(test))
    return y, splits, development


# %% 3. Preprocessing fitted on training records only
def make_preprocessor(columns):
    categorical = [c for c in columns if c in NOMINAL]
    numeric = [c for c in columns if c not in NOMINAL]
    return ColumnTransformer([
        ("numeric", Pipeline([
            ("imputer", SimpleImputer(strategy="median", keep_empty_features=True)),
            ("scaler", StandardScaler()),
        ]), numeric),
        ("categorical", Pipeline([
            ("imputer", SimpleImputer(strategy="most_frequent", keep_empty_features=True)),
            ("onehot", OneHotEncoder(handle_unknown="ignore", sparse_output=False)),
        ]), categorical),
    ], sparse_threshold=0)


# %% 4. Feedforward neural network and explicit training loop
class DropoutNetwork(nn.Module):
    """Input -> Dense 64 -> Dense 32 -> Dense 16 -> one output logit."""
    def __init__(self, input_size):
        super().__init__()
        self.layers = nn.Sequential(
            nn.Linear(input_size, 64), nn.ReLU(), nn.Dropout(0.20),
            nn.Linear(64, 32), nn.ReLU(), nn.Dropout(0.15),
            nn.Linear(32, 16), nn.ReLU(), nn.Linear(16, 1),
        )

    def forward(self, x):
        return self.layers(x).squeeze(1)


def predict_scores(model, transformed):
    model.eval()  # Disables dropout during inference.
    with torch.no_grad():
        x = torch.as_tensor(np.asarray(transformed), dtype=torch.float32)
        return torch.sigmoid(model(x)).cpu().numpy()


def train_network(x_train, y_train, x_val, y_val, config, seed):
    set_seed(seed)
    model = DropoutNetwork(x_train.shape[1])
    loss_function = nn.BCEWithLogitsLoss()  # Numerically stable sigmoid + BCE.
    optimizer = torch.optim.Adam(
        model.parameters(), lr=config.learning_rate, weight_decay=config.weight_decay)
    dataset = TensorDataset(torch.tensor(x_train, dtype=torch.float32),
                            torch.tensor(np.asarray(y_train), dtype=torch.float32))
    loader = DataLoader(dataset, batch_size=config.batch_size, shuffle=True,
                        generator=torch.Generator().manual_seed(seed))
    best_loss, best_state, stale = float("inf"), None, 0
    history = []
    for epoch in range(1, config.epochs + 1):
        model.train()
        total = 0.0
        for xb, yb in loader:
            optimizer.zero_grad()
            loss = loss_function(model(xb), yb)
            loss.backward()
            optimizer.step()
            total += loss.item() * len(yb)
        val_scores = predict_scores(model, x_val)
        val_loss = log_loss(y_val, val_scores, labels=[0, 1])
        history.append({"epoch": epoch, "train_loss": total / len(dataset),
                        "validation_loss": val_loss,
                        "validation_accuracy": accuracy_score(y_val, val_scores >= 0.5)})
        if val_loss < best_loss - 1e-5:
            best_loss, best_state, stale = val_loss, copy.deepcopy(model.state_dict()), 0
            best_epoch = epoch
        else:
            stale += 1
        if stale >= config.patience:
            break
    model.load_state_dict(best_state)
    model.eval()
    return model, pd.DataFrame(history), best_epoch


# %% 5. Validation-only threshold selection and held-out metrics
def threshold_table(y_true, scores):
    rows = []
    for threshold in np.linspace(0.05, 0.95, 91):
        pred = scores >= threshold
        rows.append({
            "threshold": float(threshold),
            "precision": precision_score(y_true, pred, zero_division=0),
            "recall": recall_score(y_true, pred, zero_division=0),
            "f2": fbeta_score(y_true, pred, beta=2, zero_division=0),
        })
    return pd.DataFrame(rows)


def select_threshold(table):
    # F2 places more emphasis on recall. Highest threshold wins exact ties.
    best = table["f2"].max()
    return float(table.loc[np.isclose(table["f2"], best, rtol=0, atol=1e-12),
                           "threshold"].max())


def compute_metrics(y_true, scores, threshold):
    pred = scores >= threshold
    tn, fp, fn, tp = confusion_matrix(y_true, pred, labels=[0, 1]).ravel()
    return {
        "threshold": threshold, "accuracy": accuracy_score(y_true, pred),
        "balanced_accuracy": balanced_accuracy_score(y_true, pred),
        "precision": precision_score(y_true, pred, zero_division=0),
        "recall": recall_score(y_true, pred, zero_division=0),
        "f1": f1_score(y_true, pred, zero_division=0),
        "f2": fbeta_score(y_true, pred, beta=2, zero_division=0),
        "roc_auc": roc_auc_score(y_true, scores),
        "average_precision": average_precision_score(y_true, scores),
        "brier_score": brier_score_loss(y_true, scores),
        "tn": int(tn), "fp": int(fp), "fn": int(fn), "tp": int(tp),
    }


def fit_experiment(frame, y, splits, columns, config):
    preprocessor = make_preprocessor(columns)
    x_train = preprocessor.fit_transform(frame.loc[splits["train"], columns])
    x_val = preprocessor.transform(frame.loc[splits["validation"], columns])
    x_test = preprocessor.transform(frame.loc[splits["test"], columns])
    model, history, epoch = train_network(
        x_train, y.loc[splits["train"]], x_val, y.loc[splits["validation"]],
        config, config.seed)
    baseline = LogisticRegression(max_iter=2000, random_state=config.seed)
    baseline.fit(x_train, y.loc[splits["train"]])
    result = {"columns": columns, "preprocessor": preprocessor, "model": model,
              "baseline": baseline, "history": history, "best_epoch": epoch,
              "input_size": x_train.shape[1], "tables": {}, "thresholds": {},
              "test_scores": {}, "metrics": {}}
    for name, val_scores, test_scores in [
        ("NN", predict_scores(model, x_val), predict_scores(model, x_test)),
        ("LR", baseline.predict_proba(x_val)[:, 1], baseline.predict_proba(x_test)[:, 1]),
    ]:
        table = threshold_table(y.loc[splits["validation"]], val_scores)
        threshold = select_threshold(table)
        result["tables"][name] = table
        result["thresholds"][name] = threshold
        result["test_scores"][name] = test_scores
        result["metrics"][name] = compute_metrics(y.loc[splits["test"]], test_scores, threshold)
    return result


# %% 6. Cross-validation, feature importance, and subgroup analysis
def cross_validate(frame, y, development, feature_sets, config):
    """CV uses development records only; each fold has a separate inner validation."""
    records = []
    if config.cv_folds == 0:
        return pd.DataFrame(columns=["feature_set", "model", "fold", "roc_auc"])
    cv = StratifiedKFold(config.cv_folds, shuffle=True, random_state=config.seed)
    for fold, (train_pos, eval_pos) in enumerate(cv.split(development, y.loc[development]), 1):
        outer_train, outer_eval = development[train_pos], development[eval_pos]
        inner_train, inner_val = train_test_split(
            outer_train, test_size=0.20, stratify=y.loc[outer_train],
            random_state=config.seed + fold)
        for key, columns in feature_sets.items():
            preprocessor = make_preprocessor(columns)
            xt = preprocessor.fit_transform(frame.loc[inner_train, columns])
            xv = preprocessor.transform(frame.loc[inner_val, columns])
            xe = preprocessor.transform(frame.loc[outer_eval, columns])
            model, _, _ = train_network(xt, y.loc[inner_train], xv, y.loc[inner_val],
                                         config, config.seed + fold)
            lr = LogisticRegression(max_iter=2000, random_state=config.seed + fold)
            lr.fit(xt, y.loc[inner_train])
            for name, score in [("NN", predict_scores(model, xe)),
                                ("LR", lr.predict_proba(xe)[:, 1])]:
                records.append({"feature_set": key, "model": name, "fold": fold,
                                "roc_auc": roc_auc_score(y.loc[outer_eval], score)})
        print(f"  Cross-validation fold {fold}/{config.cv_folds} complete.", flush=True)
    return pd.DataFrame(records)


def raw_feature_importance(result, test_frame, y_test, config):
    """Shuffle original columns so all one-hot columns for a category stay together."""
    rng = np.random.default_rng(config.seed)
    base = result["metrics"]["NN"]["roc_auc"]
    records = []
    for column in result["columns"]:
        decreases = []
        for _ in range(config.permutation_repeats):
            shuffled = test_frame[result["columns"]].copy()
            shuffled[column] = rng.permutation(shuffled[column].to_numpy())
            scores = predict_scores(result["model"], result["preprocessor"].transform(shuffled))
            decreases.append(base - roc_auc_score(y_test, scores))
        records.append({"feature": column, "auc_decrease_mean": np.mean(decreases),
                        "auc_decrease_std": np.std(decreases)})
    return pd.DataFrame(records).sort_values("auc_decrease_mean", ascending=False)


def subgroup_analysis(test_frame, y_test, scores, threshold):
    masks = {}
    for value in sorted(test_frame["Gender"].dropna().unique()):
        masks[f"Gender code {value:g}"] = test_frame["Gender"].eq(value).to_numpy()
    age = test_frame["Age at enrollment"]
    masks.update({"Age <20": age.lt(20).to_numpy(),
                  "Age 20-25": age.between(20, 25).to_numpy(),
                  "Age >25": age.gt(25).to_numpy()})
    pred, truth = scores >= threshold, np.asarray(y_test)
    records = []
    for group, mask in masks.items():
        positive, negative = mask & (truth == 1), mask & (truth == 0)
        records.append({"group": group, "n": int(mask.sum()),
                        "dropout_n": int(positive.sum()), "graduate_n": int(negative.sum()),
                        "recall": float(pred[positive].mean()) if positive.any() else np.nan,
                        "false_alarm_rate": float(pred[negative].mean()) if negative.any() else np.nan})
    return pd.DataFrame(records)


# %% 7. Plots and reproducible model artifacts
def create_plots(frame, experiments, y_test, cv, importance, fairness, output):
    plots = output / "plots"
    plots.mkdir(parents=True, exist_ok=True)
    plt.rcParams.update({"font.size": 10, "axes.spines.top": False,
                         "axes.spines.right": False, "axes.grid": True, "grid.alpha": 0.2})

    def save(fig, name):
        fig.tight_layout()
        fig.savefig(plots / name, dpi=150, bbox_inches="tight")
        plt.close(fig)

    fig, ax = plt.subplots(figsize=(7, 4))
    counts = frame["Target"].value_counts()
    bars = ax.bar(counts.index.str.title(), counts.values, color=["#407bb0", "#c44949", "#888888"])
    ax.bar_label(bars, padding=3)
    ax.set(title="Original labels (Enrolled excluded from supervised learning)", ylabel="Records")
    ax.set_ylim(0, counts.max() * 1.15)
    save(fig, "01_class_distribution.png")

    fig, axes = plt.subplots(1, 2, figsize=(11, 4))
    for key, result in experiments.items():
        h = result["history"]
        axes[0].plot(h.epoch, h.train_loss, color=COLORS[key], label=NAMES[key] + " train")
        axes[0].plot(h.epoch, h.validation_loss, "--", color=COLORS[key], label=NAMES[key] + " val")
        axes[0].axvline(result["best_epoch"], color=COLORS[key], alpha=0.25)
        axes[1].plot(h.epoch, h.validation_accuracy, color=COLORS[key], label=NAMES[key])
    axes[0].set(title="Binary cross-entropy (best weights restored)", xlabel="Epoch", ylabel="Loss")
    axes[1].set(title="Validation accuracy at threshold 0.50", xlabel="Epoch", ylabel="Accuracy")
    for ax in axes:
        ax.legend(fontsize=8)
    save(fig, "02_training_curves.png")

    fig, ax = plt.subplots(figsize=(7, 5))
    for key, result in experiments.items():
        for name, scores in result["test_scores"].items():
            fpr, tpr, _ = roc_curve(y_test, scores)
            auc = result["metrics"][name]["roc_auc"]
            ax.plot(fpr, tpr, color=COLORS[key], ls="-" if name == "NN" else "--",
                    label=f"{NAMES[key]} {name} (AUC {auc:.3f})")
    ax.plot([0, 1], [0, 1], ":", color="gray")
    ax.set(title="Held-out test ROC curves: resolved outcomes only",
           xlabel="False positive rate", ylabel="True positive rate")
    ax.legend(fontsize=8)
    save(fig, "03_roc_curves.png")

    fig, axes = plt.subplots(1, 2, figsize=(11, 4.5))
    for ax, (key, result) in zip(axes, experiments.items()):
        threshold = result["thresholds"]["NN"]
        ConfusionMatrixDisplay.from_predictions(
            y_test, result["test_scores"]["NN"] >= threshold, labels=[0, 1],
            display_labels=["Graduate", "Dropout"], ax=ax, cmap="Blues", colorbar=False)
        ax.set_title(f"{NAMES[key]} NN\nValidation-selected threshold {threshold:.2f}")
        ax.grid(False)
    save(fig, "04_confusion_matrices.png")

    fig, axes = plt.subplots(1, 2, figsize=(11, 4))
    for ax, (key, result) in zip(axes, experiments.items()):
        table = result["tables"]["NN"]
        for measure, style in [("precision", "--"), ("recall", "-"), ("f2", ":")]:
            ax.plot(table.threshold, table[measure], style, label=measure.title())
        ax.axvline(result["thresholds"]["NN"], color=COLORS[key], alpha=0.7)
        ax.set(title=NAMES[key] + ": validation only", xlabel="Decision threshold", ylabel="Score", ylim=(0, 1.05))
        ax.legend()
    save(fig, "05_threshold_tradeoff.png")

    early = experiments["early"]
    fig, ax = plt.subplots(figsize=(7, 4.5))
    for value, name, color in [(0, "Graduate", "#407bb0"), (1, "Dropout", "#c44949")]:
        ax.hist(early["test_scores"]["NN"][np.asarray(y_test) == value],
                bins=np.linspace(0, 1, 26), alpha=0.6, color=color, label=name)
    ax.axvline(early["thresholds"]["NN"], color="black", ls=":", label="Selected threshold")
    ax.set(title="First-semester NN: held-out test score distribution",
           xlabel="Sigmoid dropout score (not calibrated)", ylabel="Records")
    ax.legend()
    save(fig, "06_risk_distribution.png")

    if not cv.empty:
        fig, ax = plt.subplots(figsize=(8, 4.5))
        grouped = cv.groupby(["feature_set", "model"], sort=False).roc_auc
        means, stds = grouped.mean(), grouped.std(ddof=0)
        bars = ax.bar([f"{'First-semester' if k == 'early' else 'Full'}\n{m}"
                       for k, m in means.index], means.values,
                      yerr=stds.values, capsize=4,
                      color=[COLORS[k] if m == "NN" else "#888888" for k, m in means.index])
        ax.bar_label(bars, fmt="%.3f", padding=4)
        ax.set(title="Development-only CV ROC-AUC (error bars: fold SD)", ylabel="ROC-AUC", ylim=(0, 1.08))
        save(fig, "07_cv_comparison.png")

    fig, axes = plt.subplots(1, 2, figsize=(16, 6))
    for ax, (key, table) in zip(axes, importance.items()):
        top = table.head(10).iloc[::-1]
        labels = [s.replace("Curricular units ", "Units ") for s in top.feature]
        ax.barh(labels, top.auc_decrease_mean, color=COLORS[key])
        ax.set(title=NAMES[key] + " NN: test permutation importance",
               xlabel="Mean decrease in ROC-AUC (association, not causation)")
    save(fig, "08_feature_importance.png")

    fig, ax = plt.subplots(figsize=(10, 4.5))
    positions, width = np.arange(len(fairness)), 0.36
    for delta, column, label, color in [(-width / 2, "recall", "Dropout recall", "#407bb0"),
                                      (width / 2, "false_alarm_rate", "Graduate false-alarm rate", "#d99540")]:
        bars = ax.bar(positions + delta, fairness[column], width, label=label, color=color)
        ax.bar_label(bars, fmt="%.2f", fontsize=9)
    ax.set_xticks(positions, [f"{r.group}\nD={r.dropout_n}, G={r.graduate_n}"
                             for r in fairness.itertuples()])
    ax.set(title="First-semester test subgroup audit (descriptive; no fairness guarantee)", ylim=(0, 1.18))
    ax.legend(fontsize=9, loc="upper left")
    save(fig, "09_fairness.png")


def save_model(result, output, key):
    folder = output / "models"
    folder.mkdir(exist_ok=True)
    torch.save({"state_dict": result["model"].state_dict(),
                "input_size": result["input_size"]}, folder / f"{key}_nn.pt")
    joblib.dump(result["preprocessor"], folder / f"{key}_preprocessor.joblib")
    joblib.dump(result["baseline"], folder / f"{key}_logistic.joblib")
    (folder / f"{key}_metadata.json").write_text(json.dumps({
        "feature_columns": result["columns"], "threshold": result["thresholds"]["NN"],
        "best_epoch": result["best_epoch"], "positive_class": "Dropout",
        "negative_class": "Graduate", "snapshot": NAMES[key],
        "score_note": "Uncalibrated sigmoid score; trained on resolved outcomes only.",
    }, indent=2), encoding="utf-8")


def make_risk_report(frame, scores, threshold):
    report = pd.DataFrame({"source_row_id": frame.index.to_numpy() + 1,
                           "dropout_score": scores,
                           "decision_threshold": threshold,
                           "mentoring_flag": np.asarray(scores) >= threshold})
    report["support_priority"] = np.where(report.mentoring_flag,
                                          "Review for mentoring", "Routine follow-up")
    return report.sort_values("dropout_score", ascending=False)


# %% 8. Complete experiment and optional inference
def run_project(data_path="data.csv", output_dir="outputs", config=None):
    config = Config() if config is None else config
    if config.epochs < 1 or config.patience < 1 or config.batch_size < 1:
        raise ValueError("epochs, patience and batch_size must be positive.")
    if config.cv_folds != 0 and config.cv_folds < 2:
        raise ValueError("cv_folds must be 0 or at least 2.")
    if config.permutation_repeats < 1:
        raise ValueError("permutation_repeats must be positive.")
    set_seed(config.seed)
    output = Path(output_dir)
    output.mkdir(parents=True, exist_ok=True)
    frame, audit = load_dataset(data_path)
    y, splits, development = split_dataset(frame, config.seed)
    feature_sets = {"early": [c for c in FEATURES if "2nd sem" not in c], "full": FEATURES}
    print(f"Loaded {len(frame)} real records. Labels: {audit['label_counts']}", flush=True)
    print("Resolved-outcome splits:", {k: len(v) for k, v in splits.items()}, flush=True)
    print("Enrolled outcomes are excluded from training and evaluation.", flush=True)
    assignments = pd.DataFrame({"source_row_id": frame.index + 1, "Target": frame.Target,
                                "split": "enrolled_demo"}, index=frame.index)
    for name, rows in splits.items():
        assignments.loc[rows, "split"] = name
    assignments.to_csv(output / "split_assignments.csv", index=False)

    experiments, metric_rows, importance = {}, [], {}
    y_test = y.loc[splits["test"]]
    test_frame = frame.loc[splits["test"]]
    for key, columns in feature_sets.items():
        print(f"\nTraining {NAMES[key]} NN and logistic baseline...", flush=True)
        result = fit_experiment(frame, y, splits, columns, config)
        experiments[key] = result
        result["history"].to_csv(output / f"{key}_training_history.csv", index=False)
        for model_name, metrics in result["metrics"].items():
            metric_rows.append({"feature_set": key, "model": model_name, **metrics})
            result["tables"][model_name].to_csv(output / f"{key}_{model_name}_validation_thresholds.csv", index=False)
            pred = result["test_scores"][model_name] >= result["thresholds"][model_name]
            report = classification_report(y_test, pred, labels=[0, 1],
                                             target_names=["Graduate", "Dropout"], zero_division=0)
            (output / f"{key}_{model_name}_classification_report.txt").write_text(report, encoding="utf-8")
        print(f"  Best epoch: {result['best_epoch']}; test NN AUC: {result['metrics']['NN']['roc_auc']:.4f}", flush=True)
        save_model(result, output, key)
        importance[key] = raw_feature_importance(result, test_frame, y_test, config)
        importance[key].to_csv(output / f"{key}_feature_importance.csv", index=False)

    cv = cross_validate(frame, y, development, feature_sets, config)
    cv.to_csv(output / "cv_fold_scores.csv", index=False)
    if not cv.empty:
        summary = cv.groupby(["feature_set", "model"]).roc_auc.agg(
            mean="mean", std=lambda scores: scores.std(ddof=0), count="count")
        summary.to_csv(output / "cv_summary.csv")  # Same population SD as the plot.
    metrics = pd.DataFrame(metric_rows)
    metrics.to_csv(output / "test_metrics.csv", index=False)
    predictions = pd.DataFrame({"source_row_id": test_frame.index + 1,
                                "actual_outcome": test_frame.Target.to_numpy(),
                                "actual_dropout": y_test.to_numpy()})
    for key, result in experiments.items():
        for name, score in result["test_scores"].items():
            predictions[f"{key}_{name}_score"] = score
            predictions[f"{key}_{name}_prediction"] = (score >= result["thresholds"][name]).astype(int)
    predictions.to_csv(output / "test_predictions.csv", index=False)
    early = experiments["early"]
    fairness = subgroup_analysis(test_frame, y_test, early["test_scores"]["NN"], early["thresholds"]["NN"])
    fairness.to_csv(output / "subgroup_audit.csv", index=False)

    # Mentor report is only for unresolved records, separate from test evaluation.
    enrolled = frame.loc[frame.Target == "enrolled"]
    if len(enrolled):
        scores = predict_scores(early["model"], early["preprocessor"].transform(enrolled[early["columns"]]))
        mentor = make_risk_report(enrolled, scores, early["thresholds"]["NN"])
        mentor["observed_status"] = "Enrolled - eventual outcome unknown"
        mentor.to_csv(output / "enrolled_mentoring_demo.csv", index=False)
    create_plots(frame, experiments, y_test, cv, importance, fairness, output)
    manifest = {"config": asdict(config), "data_audit": audit,
                "split_sizes": {k: len(v) for k, v in splits.items()},
                "framework": "PyTorch CPU", "python": platform.python_version(),
                "versions": {"torch": torch.__version__, "numpy": np.__version__,
                             "pandas": pd.__version__, "scikit_learn": sklearn.__version__,
                             "matplotlib": matplotlib.__version__, "joblib": joblib.__version__},
                "task": "Dropout versus Graduate; Enrolled excluded from supervised learning",
                "threshold_rule": "Maximum validation F2 on 0.05..0.95 grid; highest threshold on ties",
                "cv_scope": "Development split only, with inner training/validation per fold",
                "dataset_reference": "https://doi.org/10.24432/C5MC89"}
    (output / "run_manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    print("\nHeld-out test results (positive class = Dropout):")
    print(metrics[["feature_set", "model", "threshold", "accuracy", "precision", "recall", "f1", "roc_auc"]].round(4).to_string(index=False))
    print(f"\nSaved models, plots, metrics and demo mentoring report to {output.resolve()}", flush=True)
    return {"metrics": metrics, "experiments": experiments, "cv": cv,
            "fairness": fairness, "audit": audit, "splits": splits, "output_dir": output}


def predict_new_students(csv_path, model_dir, report_path):
    """Use the saved first-semester model without fitting anything on new rows."""
    folder = Path(model_dir)
    metadata = json.loads((folder / "early_metadata.json").read_text(encoding="utf-8"))
    columns = metadata["feature_columns"]
    frame = read_features(csv_path, columns)
    preprocessor = joblib.load(folder / "early_preprocessor.joblib")
    checkpoint = torch.load(folder / "early_nn.pt", map_location="cpu", weights_only=True)
    model = DropoutNetwork(checkpoint["input_size"])
    model.load_state_dict(checkpoint["state_dict"])
    scores = predict_scores(model, preprocessor.transform(frame[columns]))
    report = make_risk_report(frame, scores, metadata["threshold"])
    report_path = Path(report_path)
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report.to_csv(report_path, index=False)
    print(f"Saved {len(report)} student scores to {report_path.resolve()}")
    return report


def main():
    base = Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("data", nargs="?", default=str(base / "data.csv"))
    parser.add_argument("--output", default=str(base / "outputs"))
    parser.add_argument("--epochs", type=int, default=200)
    parser.add_argument("--cv-folds", type=int, default=5, help="0 skips cross-validation")
    parser.add_argument("--predict", metavar="CSV", help="Score students with the saved early model")
    parser.add_argument("--model-dir", default=str(base / "outputs" / "models"))
    parser.add_argument("--report", default=str(base / "new_student_predictions.csv"))
    args = parser.parse_args()
    if args.predict:
        predict_new_students(args.predict, args.model_dir, args.report)
    else:
        run_project(args.data, args.output, Config(epochs=args.epochs, cv_folds=args.cv_folds))


if __name__ == "__main__":
    main()
