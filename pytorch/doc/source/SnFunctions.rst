***************************
Sn-functions and Sn-vectors
***************************

=================
Sn functions
=================

The class ``SnFunction`` represents functions on :math:`\mathbb{S}_n`. 
The following initializes a function on :math:`\mathbb{S}_3` with random Gaussian entries and 
prints it out.

.. code-block:: python

  >>> f=Snob2.SnFunction.gaussian(3)
  >>> print(f)
  [ 1 2 3 ] : -1.23974
  [ 2 1 3 ] : -0.407472
  [ 1 3 2 ] : 1.61201
  [ 2 3 1 ] : 0.399771
  [ 3 1 2 ] : 1.3828
  [ 3 2 1 ] : 0.0523187


The value of ``f`` at specific group elements can be accessed via the ``SnElement`` object or just its index. 

.. code-block:: python

  >>> f[Snob2.SnElement([1,3,2])]
  1.6120094060897827
  0.1949467808008194
  >>> f[2]
  1.6120094060897827

The *left-translate* of :math:`f` by a permutation :math:`\pi` is defined :math:`g_1(\sigma)=f(\pi^{-1}\sigma)`. 

.. code-block:: python

  >>> g1=f.left_translate(pi)
  SnFunction moved
  >>> print(g1)
  [ 1 2 3 ] : -0.407472
  [ 2 1 3 ] : -1.23974
  [ 1 3 2 ] : 0.399771
  [ 2 3 1 ] : 1.61201
  [ 3 1 2 ] : 0.0523187
  [ 3 2 1 ] : 1.3828

The *right-translate* of :math:`f` by a permutation :math:`\pi` is defined :math:`g_1(\sigma)=f(\sigma \pi^{-1})`. 

.. code-block:: python

  >>> g2=f.right_translate(pi)
  SnFunction moved
  >>> print(g2)
  [ 1 2 3 ] : -0.407472
  [ 2 1 3 ] : -1.23974
  [ 1 3 2 ] : 1.3828
  [ 2 3 1 ] : 0.0523187
  [ 3 1 2 ] : 1.61201
  [ 3 2 1 ] : 0.399771

The *inverse* of :math:`f` is defined :math:`f^{-1}(\sigma)=f(\sigma)`. 

.. code-block:: python

  >>> f=Snob2.SnFunction.gaussian(3)
  >>> finv=f.inv()
  >>> print(finv)
  [ 1 2 3 ] : -1.23974
  [ 2 1 3 ] : -0.407472
  [ 1 3 2 ] : 1.61201
  [ 2 3 1 ] : 1.3828
  [ 3 1 2 ] : 0.399771
  [ 3 2 1 ] : 0.0523187


==================
Sn class functions
==================

The class ``SnClassFunction`` represents functions on the conjugacy classes of :math:`\mathbb{S}_n`. 
An important example of class functions are the characters of the group.  
The following initializes a class function on :math:`\mathbb{S}_4` with random Gaussian entries 
and prints it out.

.. code-block:: python

  >>> f=Snob2.SnClassFunction.gaussian(4)
  >>> print(f)
  SnCClass[4] : -1.23974
  SnCClass[3,1] : -0.407472
  SnCClass[2,2] : 1.61201
  SnCClass[2,1,1] : 0.399771
  SnCClass[1,1,1,1] : 1.3828

The value of ``f`` at specific conjugacy classes can be accessed via the corresponding ``SnCClass``, 
``IntegerPartition`` or just the index.

.. code-block:: python

   >>> f[Snob2.SnCClass([2,2])]
   1.6120094060897827
   >>> f[Snob2.IntegerPartition([2,2])]
   1.6120094060897827
   >>> f[Snob2.SnCClass(2)]
   1.6120094060897827





