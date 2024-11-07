import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class CalculatorApp {

    JFrame frame;
    JTextField num1Field;
    JTextField num2Field;
    JTextField resultField;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new CalculatorApp().createAndShowGUI());
    }

    CalculatorApp() {
        frame = new JFrame("Simple Calculator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 250);
        frame.setLocationRelativeTo(null);
    }

    void createAndShowGUI() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 2, 10, 10));

        JLabel label1 = new JLabel("Enter first number:");
        num1Field = new JTextField(10);
        JLabel label2 = new JLabel("Enter second number:");
        num2Field = new JTextField(10);
        JLabel label3 = new JLabel("Result:");
        resultField = new JTextField(10);
        resultField.setEditable(false);

        JButton addButton = new JButton("+");
        JButton subButton = new JButton("-");
        JButton mulButton = new JButton("*");
        JButton divButton = new JButton("/");

        addButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                performOperation("+");
            }
        });
        subButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                performOperation("-");
            }
        });
        mulButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                performOperation("*");
            }
        });
        divButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                performOperation("/");
            }
        });

        panel.add(label1);
        panel.add(num1Field);
        panel.add(label2);
        panel.add(num2Field);
        panel.add(label3);
        panel.add(resultField);
        panel.add(addButton);
        panel.add(subButton);
        panel.add(mulButton);
        panel.add(divButton);

        frame.getContentPane().add(panel);
        frame.setVisible(true);
    }

    void performOperation(String operator) {
        try {
            double num1 = Double.parseDouble(num1Field.getText());
            double num2 = Double.parseDouble(num2Field.getText());
            double result = 0;

            switch (operator) {
                case "+":
                    result = num1 + num2;
                    break;
                case "-":
                    result = num1 - num2;
                    break;
                case "*":
                    result = num1 * num2;
                    break;
                case "/":
                    if (num2 != 0) {
                        result = num1 / num2;
                    } else {
                        JOptionPane.showMessageDialog(frame, "Error: Division by zero", "Error", JOptionPane.ERROR_MESSAGE);
                        return;
                    }
                    break;
            }

            resultField.setText(String.valueOf(result));
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(frame, "Please enter valid numbers", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
