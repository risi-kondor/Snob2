*********************
Combinatorial classes
*********************

`Snob` provides specialized classes to represent various combinatorial objects involved in the 
representation theory of :math:`\mathbb{S}_n`.

============
Permutations
============

A permutation :math:`\pi` of n is a bijective map :math:`\{1,2,\ldots,n\}\to\{1,2,\ldots,n\}`. 


>>> pi=Permutation([2,3,1,5,4])
>>> print(pi)
[ 2 3 1 5 4 ]
>>> pi[3]
1

The product of two permutations :math:`\tau` and :math:`\pi` is the permutation corresponding 
to the composition of maps :math:`\tau\circ\pi`. 

>>> tau=Permutation([2,1,3,4,5])
>>> print(tau*pi)
[ 1 3 2 5 4 ]

The `inv` method returns the inverse of the permutation.

>>> print(pi.inv())
[ 3 1 2 5 4 ]



==================
Integer partitions
==================

An *integer partition* of a positive integer :math:`n` is a vector of positive integers
:math:`\lambda=(\lambda_1,\ldots,\lambda_k)` such that :math:`\sum_{i=1}^k \lambda_i=n` and 
:math:`\lambda_1\geq \lambda_2\geq \ldots\geq\lambda_k`. 
The ``IntegerPartition`` class represents such vectors.
 
.. code-block:: python

   >>> a=IntegerPartition([3,2,1])
   >>> print(a)
   [3,2,1]
   >>> print(a[1])
   2

The ``IntegerPartitions`` class returns an object that contains *all* integer partitions of \math:`n`.


.. code-block:: python

   >>> Lambda=IntegerPartitions(5)
   >>> for i in range(len(Lambda)):
   ...      print(Lambda[i])
   ... 
   [5]
   [4,1]
   [3,2]
   [3,1,1]
   [2,2,1]
   [2,1,1,1]
   [1,1,1,1,1]


==================
Young tableaux
==================

A Young tableau is a Young diagram whose cells are filled with integers. The 
default Young tableau of a given shape is the one where the numbers :math:`1,2,\ldots,n` 
appear sequentially.

.. code-block:: python

   >>> T=YoungTableau(Snob2.IntegerPartition([3,2,1]))
   >>> print(T)
   1 2 3 
   4 5 
   6 
   >>> print(T.shape())
   [3,2,1]
   >>> 

A *standard Young tableau* is a Young tableau filled with the numbers :math:`1,2,\ldots,n` 
in such a way that in any row the numbers increase from left to right and in any 
column the numbers increase top to bottom. 
The ``StandardYoungTableaux`` class returns an object that contains *all* standard Young tableaux 
of a given shape. 

.. code-block:: python

   >>> lamb=IntegerPartition([3,2])
   >>> T=Snob2.StandardYoungTableaux(lamb)
   >>> for i in range(len(T)):
   ...     print(T[i])
   ... 
   1 2 3 
   4 5 

   1 2 4 
   3 5 
   
   1 3 4 
   2 5 
   
   1 2 5 
   3 4  
   
   1 3 5 
   2 4 




