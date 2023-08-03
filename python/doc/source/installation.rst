************
Installation
************

Installing Snob2 as PyTorch module requires the following:

#. C++11 or higher
#. Python and PyTorch
#. pybind11 (available with any PyTorch installation) 

To install the module follow these steps:

#. Download the `cnine <https://github.com/risi-kondor/cnine>`_ and 
   `Snob2 <https://github.com/risi-kondor/Snob2>`_ packages. 
#. Edit the file ``setup.py`` in Snob2's ``python`` directory as needed. 
   In particular, make sure that ``cnine_root`` points to the root of 
   the **cnine** package on your system. 
#. Run ``pip install -e .`` in the ``python`` directory to compile the package and install it on your system.
 
To use Snob2, import the module with the command ``import Snob2``. 

