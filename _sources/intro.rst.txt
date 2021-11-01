Snob2 is a C++ package with a Python interface 
for computing the representations of the symmetric group :math:`\mathbb{S}_n` and 
computing fast Fourier transforms on :math:`\mathbb{S}_n`.
Snob2 is built on the **cnine** library which can be downloaded from https://github.com/risi-kondor/cnine.
GPU functionality in Snob2 is under development but not yet enabled. 

..
  Snob2 is designed to eventually allow GPU functionality, but the GPU routines are currently not enabled.

Snob2 is written by Risi Kondor at the University of Chicago and is released under the 
`Mozilla public license v.2.0 <https://www.mozilla.org/en-US/MPL/2.0/>`_.   

This document provides documentation for Snob2's Python interface. Not all features in the C++ library 
are available through this interface. The documentation of the C++ API can be found in pdf format 
in the package's ``doc`` directory.


********
Features
********

* Custom classes for combinatorial objects such as integer partitions and Young tableau implemented in C++ 
  for efficiency.
* Classes for the symmetric group, conjugacy classes, quotient spaces,
  characters and irreducible representations of :math:`\mathbb{S}_n`.
* Classes for functions on :math:`\mathbb{S}_n` and quotient spaces of :math:`\mathbb{S}_n`. 
* Classes implementing Clausen's FFT algorithm for the forward and backward Fourier transform on 
  :math:`\mathbb{S}_n` and its quotient spaces. 


************
Installation
************

Installing Snob2 requires the following:

#. A C++ installation with C++11 or higher
#. Python

To install Snob2 follow these steps:

#. Download the `cnine <https://github.com/risi-kondor/cnine>`_ and 
   `Snob2 <https://github.com/risi-kondor/Snob2>`_ packages. 
#. Edit the file ``config.txt``, in particular, make sure that ``CNINE_ROOT`` points to the root of 
   the **cnine** package on your system. 
#. Run ``python setup.sty install`` in the ``python`` directory to compile the package and install it on your 
   system.
 
To use Snob2, issue the command ``import Snob2`` in Python. This loads to the `Snob2` module and initializes 
the various static datastructures used by the package. 


******
Design
******

The representation theory of :math:`\mathbb{S}_n` involves some data structures that are relatively 
expensive to compute but only needed to be computed once. Snob2's backend automatically caches these data.  
For example, the class ``IntegerPartitions`` returns all integer partitions of an integer :math:`n`. 
The first time that an ``IntegerPartitions`` object is created for a given value of :math:`n`, Snob2 
constructs the integer partitions from the integer partitions of :math:`m<n` and stores the result 
in a static object so that on subsequent calls the same process does not need to be repeated. 
