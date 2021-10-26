import numpy
import torch
import cnine
import Snob2

a=Snob2.IntegerPartition([3,2,1])
print(a)
print(a[2])
a[2]=2
print(a)

Lambda=Snob2.IntegerPartitions(5)
print(Lambda[0])
print(Lambda[1],'\n')

lamb=a
T=Snob2.YoungTableau(lamb)
print(T,'\n')
print(T.shape(),'\n')

Tcal=Snob2.StandardYoungTableaux(lamb)
print(Tcal[0],'\n')
print(Tcal[1],'\n')

pi=Snob2.Permutation.identity(5)
print(pi,'\n')

sigma=Snob2.Permutation([2,1,3,4,5])
print(sigma,'\n')
print(sigma.inv(),'\n')
print(sigma*sigma,'\n')

sn=Snob2.Sn(5)
print(sn.element(0))
print(sn.element(1))
print(sn.element(2))
print(sigma,'\n')

rho=sn.irrep(Snob2.IntegerPartition([4,1]))
print(rho,'\n')
print(rho[Snob2.SnElement(sigma)],'\n')
