import torch
from Snob2 import *
from math import factorial

s4 = Sn(4)
s42 = SnOverSm(4,2)

print("Testing S4 over S2: elements with the same index (right) should be in the same coset.\n")

for i in range(len(s4)):
	elem  = s4.element(i)
	coset = s42.index(elem)
	print(f"{elem} : {coset}")