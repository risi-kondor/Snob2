import sys,os
import torch 
from setuptools import setup
from setuptools import find_packages
from torch.utils.cpp_extension import CppExtension, BuildExtension, CUDAExtension
from glob import glob

#os.environ['CUDA_HOME']='/usr/local/cuda'
#os.environ["CC"] = "clang"

#CUDA_HOME='/usr/local/cuda'
#print(torch.cuda.is_available())


# --- User settings ------------------------------------------------------------------------------------------


cnine_root = os.getcwd()+"/../../cnine"


# ------------------------------------------------------------------------------------------------------------


cwd = os.getcwd()

_cxx_compile_args = ['-std=c++14',
		     '-Wno-sign-compare',
		     '-Wno-deprecated-declarations',
		     '-Wno-unused-variable',
		     '-Wno-reorder',
		     '-Wno-reorder-ctor',
		     '-Wno-overloaded-virtual',
		     '-D_WITH_ATEN',
		     '-DCNINE_RANGE_CHECKING',
		     '-DCNINE_SIZE_CHECKING',
		     '-DCNINE_DEVICE_CHECKING',
		     '-DWITH_FAKE_GRAD'
		     ]

ext_modules=[CppExtension('snob_base', ['bindings/Snob2_bindings.cpp'],
			  include_dirs=[cnine_root+'/include',
					cnine_root + '/combinatorial',
					cnine_root + '/containers',
					cnine_root + '/math',
					cnine_root + '/wrappers',
					cnine_root+'/objects/backendA',
					cnine_root+'/objects/backendB',
					cnine_root+'/objects/scalar',
					cnine_root+'/objects/tensor',
					cnine_root+'/objects/tensor_views',
					cnine_root+'/objects/tensor_views/functions',
					cwd+'/../include',
					cwd+'/../combinatorial',
					cwd+'/../Sn'],
			  extra_compile_args = {'cxx': _cxx_compile_args},
			  depends=['setup.py',
				   'bindings/Snob2_bindings.cpp',
				   'bindings/SnClasses_py.cpp',
				   'bindings/SnFunctions_py.cpp',
				   'bindings/SnFFT_py.cpp'])] 


setup(name='snob',
      ext_modules=ext_modules,
      packages=find_packages('src'),
      package_dir={'': 'src'},
      py_modules=[splitext(basename(path))[0] for path in glob('src/*.py')],
      include_package_data=True,
      zip_safe=False,
      cmdclass={'build_ext': BuildExtension}
      )

