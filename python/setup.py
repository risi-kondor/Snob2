import sys,os
import torch 
from setuptools import setup
from torch.utils.cpp_extension import CppExtension, BuildExtension, CUDAExtension

#os.environ['CUDA_HOME']='/usr/local/cuda'
os.environ["CC"] = "clang"

#CUDA_HOME='/usr/local/cuda'
#print(torch.cuda.is_available())

setup(name='Snob2',
      ext_modules=[CppExtension('Snob2', ['Snob2_py.cpp'],
                                include_dirs=['../../cnine/include','../../cnine/objects/scalar','../../cnine/objects/tensor',
                                              '../include','../combinatorial','../Sn'],
                                 extra_compile_args = {
                                                       'cxx': ['-std=c++14',
                                                               '-Wno-sign-compare',
                                                               '-Wno-deprecated-declarations',
                                                               '-Wno-unused-variable',
                                                               '-Wno-reorder-ctor',
                                                               '-Wno-reorder',
#                                                               '-Wl,-rpath,"/Users/risi/opt/anaconda3/lib/python3.8/site-packages/torch/lib"' #this is for sphinx
                                                               ]},
                                 depends=['setup.py','Snob2_py.cpp','SnClasses_py.cpp','SnFunctions_py.cpp','SnFFT_py.cpp'])], 
      cmdclass={'build_ext': BuildExtension}
      )

