import pytholog as pl
from sympy import *
from sympy.logic.inference import satisfiable
rain = Symbol("rain")
hagrid = Symbol("hagrid")
dumbledore = Symbol("dumbledore")
logical_sentence = And(rain,hagrid)
print(logical_sentence)
print(logical_sentence.subs({rain:True,hagrid:False}))
