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


#cnine_root = os.getcwd()+"/../../cnine"
cnine_root ="../../cnine"
snob2_root=".."

# ------------------------------------------------------------------------------------------------------------


cwd = os.getcwd()+"/"

_cxx_compile_args = ['-std=c++17',
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
			  include_dirs=[cwd+cnine_root,
					cwd+cnine_root+'/include',
					cwd+cnine_root+'/modules',
					cwd+cnine_root+'/combinatorial',
					cwd+cnine_root+'/math',
					cwd+cnine_root+'/objects/tensor_views',
					cwd+cnine_root+'/objects/tensor_views/functions',

					cwd+snob2_root+'/include',
					cwd+snob2_root+'/combinatorial',
					cwd+snob2_root+'/Sn'],
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

