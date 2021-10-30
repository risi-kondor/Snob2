.. Snob documentation master file, created by
   sphinx-quickstart on Mon Oct 25 19:29:42 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Snob
================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


*********************
Combinatorial classes
*********************

Snob provides specialized classes to represent the various combinatorial objects involved in the 
representation theory of :math:`\mathbb{S}_n`.

============
Permutations
============

A permutation :math:`\pi` of n is a bijective map :math:`\{1,2,\ldots,n\}\to\{1,2,\ldots,n\}`. 


>>> pi=Snob2.Permutation([2,3,1,5,4])
>>> print(pi)
[ 2 3 1 5 4 ]
>>> pi[3]
1
>>> 

The product of two permutations :math:`\tau` and :math:`\pi` is the permutation corresponding 
to the composition of maps :math:`\tau\circ\pi`. 

>>> tau=Snob2.Permutation([2,1,3,4,5])
>>> print(tau*pi)
[ 1 3 2 5 4 ]
>>> 

The `inv` method returns the inverse of a permutation.

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

   >>> a=Snob2.IntegerPartition([3,2,1])
   >>> print(a)
   [3,2,1]
   >>> print(a[1])
   2
   >>> 

The ``IntegerPartitions`` class returns an object that contains *all* integer partitions of n.


.. code-block:: python

   Lambda=IntegerPartitions(5)
   for i in range(len(Lambda)):
   	print(Lambda[i])

.. code-block:: python

   [5]
   [4,1]
   [3,2]
   [3,1,1]
   [2,2,1]
   [2,1,1,1]
   [1,1,1,1,1]



==================
Young tableau
==================

A Young tableau is a Young diagram whose cells are filled with integers. 

.. code-block:: python

   >>> T=Snob2.YoungTableau(Snob2.IntegerPartition([3,2,1]))
   >>> print(T)
   1 2 3 
   4 5 
   6 
   >>> print(T.shape())
   [3,2,1]
   >>> 

|

***********************
Symmetric group classes
***********************

|

The symmetric group :math:`\mathbb{S}_n`, represented by the class ``Sn``, 
is the group of all permutations of :math:`\{1,2,\ldots,n\}`.


   >>> G=Snob2.Sn(4)
>>> for i in range(len(G)):
...     print(G.element(i))
... 
[ 1 2 3 4 ]
[ 2 1 3 4 ]
[ 1 3 2 4 ]
[ 2 3 1 4 ]
[ 3 1 2 4 ]
[ 3 2 1 4 ]
[ 1 2 4 3 ]
[ 2 1 4 3 ]
[ 1 3 4 2 ]
[ 2 3 4 1 ]
[ 3 1 4 2 ]
[ 3 2 4 1 ]
[ 1 4 2 3 ]
[ 2 4 1 3 ]
[ 1 4 3 2 ]
[ 2 4 3 1 ]
[ 3 4 1 2 ]
[ 3 4 2 1 ]
[ 4 1 2 3 ]
[ 4 2 1 3 ]
[ 4 1 3 2 ]
[ 4 2 3 1 ]
[ 4 3 1 2 ]
[ 4 3 2 1 ]

The individual group elements are of type ``SnElement``, which have the same methods as the ``Permutation`` class.


=================
Conjugacy classes
=================

The conjugacy classes of :math:`\mathbb{S}_n` are in bijection with the integer partitions of n. 
Snob2 has a separate class ``SnCClass`` to represent conjugacy classes. ``SnCClass`` objects can 
be constructed either from the group object or directly from an integer partition. 




==========
Characters
==========

The characters of :math:`\mathbb{S}_n` can be constructed from the group object or separately. 


===========================
Irreducible representations
===========================

Reference
=========

*********************
Combinatorial classes
*********************

|

..
  ==================
  Integer partitions
  ==================


.. autoclass:: Snob2.IntegerPartition(parts)

|

.. autoclass:: Snob2.IntegerPartitions(n)

|

..
  ==================
  Young tableau
  ==================

.. autoclass:: Snob2.YoungTableau
   :member-order: bysource

|

..
  ==================
  Permutations
  ==================

.. autoclass:: Snob2.Permutation

|

***********************
Symmetric group classes
***********************

|

.. autoclass:: Snob2.Sn(n)

|
|

.. autoclass:: Snob2.SnElement

|
|

.. autoclass:: Snob2.SnCharacter

|
|

.. autoclass:: Snob2.SnIrrep




Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


.. 
   .. class:: IntegerPartition(part)

   Class to represent an integer partition of an integer n.

   .. method:: getn()

      Return n.

   .. method:: height()

      Return the number of parts.
