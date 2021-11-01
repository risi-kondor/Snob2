************************
Sn Fourier transforms
************************


The Fourier transform on :math:`\mathbb{S}_n` converts a function on :math:`\mathbb{S}_n` 
or a qutient space of :math:`\mathbb{S}_n` into an :math:`\mathbb{S}_n`--vector.  
Snob2 uses Clausen's FFT to compute forward and backward Fourier transforms. 
Fourier transforms employs several internal data structures that can be reused on future transforms. 
Therefore before conducting a Fourier transform a corresponding ``ClausenFFT`` must be constructed. 


==========
FFTs on Sn
==========

The following sets up an ``ClausenFFT`` object for Fourier transformation on :math:`\mathbb{S}_4` and 
defines a random function on the group. 

.. code-block:: python

  >>> fft=Snob2.ClausenFFT(4)
  >>> f=Snob2.SnFunction.gaussian(4)
  >>> print(f)
  [ 1 2 3 4 ] : -1.23974
  [ 2 1 3 4 ] : -0.407472
  [ 1 3 2 4 ] : 1.61201
  [ 2 3 1 4 ] : 0.399771
  [ 3 1 2 4 ] : 1.3828
  [ 3 2 1 4 ] : 0.0523187
  [ 1 2 4 3 ] : -0.904146
  [ 2 1 4 3 ] : 1.87065
  [ 1 3 4 2 ] : -1.66043
  [ 2 3 4 1 ] : -0.688081
  [ 3 1 4 2 ] : 0.0757219
  [ 3 2 4 1 ] : 1.47339
  [ 1 4 2 3 ] : 0.097221
  [ 2 4 1 3 ] : -0.89237
  [ 1 4 3 2 ] : -0.228782
  [ 2 4 3 1 ] : 1.16493
  [ 3 4 1 2 ] : 0.584898
  [ 3 4 2 1 ] : -0.660558
  [ 4 1 2 3 ] : 0.534755
  [ 4 2 1 3 ] : -0.607787
  [ 4 1 3 2 ] : 0.74589
  [ 4 2 3 1 ] : -1.75177
  [ 4 3 1 2 ] : -0.965146
  [ 4 3 2 1 ] : -0.474282
 
We can now use our fft object to take the Fourier transform of f.

.. code-block:: python

  >>> F=fft(f)
  >>> print(F)
  Part [4]:
  [ -0.486197 ]

  Part [3,1]:
  [ 2.56166 1.21663 -0.41762 ]
  [ 1.3139 -1.81861 3.2474 ]
  [ 2.10957 -3.31125 -5.47569 ]

  Part [2,2]:
  [ -3.05059 -2.65296 ]
  [ 1.56762 1.53786 ]

  Part [2,1,1]:
  [ -5.13609 4.39341 1.45563 ]
  [ 3.59791 2.07342 -0.436283 ]
  [ -3.65454 0.381513 -3.60564 ]

  Part [1,1,1,1]:
  [ 7.96084 ]

The inverse Fourier transform can be computed with the same FFT object and should return the 
original function ``f``.

.. code-block:: python

  >>> fd=fft.inv(F)
  >>> print(fd)
  [ 1 2 3 4 ] : -1.23974
  [ 2 1 3 4 ] : -0.407472
  [ 1 3 2 4 ] : 1.61201
  [ 2 3 1 4 ] : 0.399771
  [ 3 1 2 4 ] : 1.3828
  [ 3 2 1 4 ] : 0.0523185
  [ 1 2 4 3 ] : -0.904147
  [ 2 1 4 3 ] : 1.87065
  [ 1 3 4 2 ] : -1.66043
  [ 2 3 4 1 ] : -0.688081
  [ 3 1 4 2 ] : 0.0757219
  [ 3 2 4 1 ] : 1.47339
  [ 1 4 2 3 ] : 0.097221
  [ 2 4 1 3 ] : -0.89237
  [ 1 4 3 2 ] : -0.228782
  [ 2 4 3 1 ] : 1.16493
  [ 3 4 1 2 ] : 0.584898
  [ 3 4 2 1 ] : -0.660558
  [ 4 1 2 3 ] : 0.534755
  [ 4 2 1 3 ] : -0.607787
  [ 4 1 3 2 ] : 0.74589
  [ 4 2 3 1 ] : -1.75177
  [ 4 3 1 2 ] : -0.965146
  [ 4 3 2 1 ] : -0.474282


=============
FFTs on Sn/Sm
=============

The ``ClausenFFT`` can also be used to compute FFTs on :math:`\mathbb{S}_n/\mathbb{S}_m`. 

.. code-block:: python

  >>> fft=Snob2.ClausenFFT(4,2)
  >>> f=Snob2.SnOverSmFunction.gaussian(4,2)
  >>> print(f)
  -0.546571
  -0.0384917
  0.194947
  -0.485144
  -0.370271
  -1.12408
  1.73664
  0.882195
  -1.50279
  0.570759
  -0.929941
  -0.934988

  >>> F=fft(f)
  >>> print(F)
  Part [4]:
  [ -2.54774 ]

  Part [3,1]:
  [ 0.329091 3.59416 ]
  [ -1.78231 0.663375 ]
  [ 1.96793 1.63815 ]

  Part [2,2]:
  [ -3.93037 ]
  [ -1.41466 ]

  Part [2,1,1]:
  [ 0.290743 ]
  [ -1.23415 ]
  [ -1.32773 ]



.. code-block:: python

  >>> fd=fft.inv_snsm(F)
  SnFunction moved
  >>> print(fd)
  [ 1 2 3 ] : -0.546571
  [ 2 1 3 ] : -0.0384917
  [ 1 3 2 ] : 0.194947
  [ 2 3 1 ] : -0.485144
  [ 3 1 2 ] : -0.37027
  [ 3 2 1 ] : -1.12408
  [ 32705 1 2 ] : 1.73664
  [ 3 2 1 ] : 0.882195
  [ 3 1 2 ] : -1.50279
  [ 519242688 2 1 ] : 0.570759
  [ 3 1 2 ] : -0.929941
  [ 3 2 1 ] : -0.934988


