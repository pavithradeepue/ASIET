import pytholog as pl
from sympy import *
from sympy.logic.inference import satisfiable

implication_logic = Implies(Not(rain),hagrid)
print(implication_logic)
print(satisfiable(implication_logic))
