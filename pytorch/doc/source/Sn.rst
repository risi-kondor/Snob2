***********************
Symmetric group classes
***********************

The symmetric group :math:`\mathbb{S}_n`, represented by the class ``Sn``, 
is the group of all permutations of :math:`\{1,2,\ldots,n\}`.


.. code-block:: python

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


=================
Group elements
=================


The group elements of :math:`\mathbb{S}_n` are of type ``SnElement``, which have the same methods as the 
``Permutation`` class. Group elements are listed in a specific reverse insertion sort order that fits 
the structure of :math:`\sigma\mathbb{S}_m` cosets and hence is well adapted to Clausen-type 
fast Fourier transforms on :math:`\mathbb{S}_n`. The following shows how to extract the i'th 
group element and how to get the index of a particular group element.

.. code-block:: python

   >>> pi=G[17]
   >>> print(pi)
   [ 3 4 2 1 ]
   >>> print(G.index(pi))
   17


=================
Conjugacy classes
=================

The conjugacy classes of :math:`\mathbb{S}_n` are in bijection with the integer partitions of :math:`n`. 
Snob2 has a separate class ``SnCClass`` to represent conjugacy classes. ``SnCClass`` objects can 
be constructed either from the group object or directly from an integer partition. 

.. code-block:: python

   >>> G=Snob2.Sn(5)
   >>> mu=Snob2.IntegerPartition([3,2])
   >>> cc=G.cclass(mu)
   >>> print(cc)
   SnCClass[3,2]

The conjugacy classes are ordered according to majorization order of their integer partitions. 
The ``Sn.index`` method returns the index of a given conjugacy class.

.. code-block:: python

   >>> G.index(cc)
   2


==========
Characters
==========

The characters of :math:`\mathbb{S}_n` are also indexed by the integer partitions of :math:`n`. 
The corresponding ``SnCharacter`` objects can be constructed from the group object or separately. 




===========================
Irreducible representations
===========================

The irreducible representations (irreps) of :math:`\mathbb{S}_n` are captured by ``SnIrrep`` objects. For a 
given integer partition :math:`\lambda` of n, the corresponding irrep can be constructed from 
the group object or directly from the integer partition. 

   >>> lambd=Snob2.IntegerPartition([3,1])
   >>> rho=G.irrep(lambd)
   >>> print(rho)
   SnIrrep([3,1])

   >>> lambd=Snob2.IntegerPartition([3,1])
   >>> rho=Snob2.SnIrrep(lambd)
   >>> print(rho)
   SnIrrep([3,1])

The dimension of the irrep is accessible through the `get_dim()` method. 

   >>> print(rho.get_dim())
   3

All irreps in Snob2 are expressed in Young's orthogonal representation. The representation matrices 
are easy to access.

  >>> pi=Snob2.SnElement([3,2,1,4])
  >>> print(rho[pi])
  [ 1 0 0 ]
  [ -0 -0.5 -0.866025 ]
  [ -0 -0.866025 0.5 ]

