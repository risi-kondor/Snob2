ROOTDIR=../..
include $(ROOTDIR)/common.txt

INCLUDE= $(CNINE_INCLUDES) -I$(SNOB2_INCLUDEDIR) -I$(COMBINATORIALDIR) -I$(SNDIR) 

TESTS= testSn testSnFunction testSnOverSm testSnIrrep testSnPart testSnType

ifdef WITH_CUDA
endif 

DEPS=$(SNDIR)/*.hpp $(COMBINATORIALDIR)/*.hpp  

EXECS= 

CUDA_OBJECTS=  
CUDA_EXTERNS=

ifdef WITH_CUDA
INCLUDE+=-I$(CUDA_HOME)/include
CUDA_OBJECTS+=$(CNINE_ROOT)/cuda/CtensorA_add.o 
CUDA_EXTERNS+=$(CNINE_ROOT)/include/Cnine_base.cu 
endif 



# -------------------------------------------------------------------------------------------------------------


testSn: testSn.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSn testSn.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSn testSn.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnFunction: testSnFunction.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnFunction testSnFunction.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnFunction testSnFunction.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnOverSm: testSnOverSm.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnOverSm testSnOverSm.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnOverSm testSnOverSm.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnIrrep: testSnIrrep.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnIrrep testSnIrrep.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnIrrep testSnIrrep.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnPart: testSnPart.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnPart testSnPart.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnPart testSnPart.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnType: testSnType.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnType testSnType.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnType testSnType.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif



# -------------------------------------------------------------------------------------------------------------


objects: $(OBJECTS) $(CUDA_OBJECTS)
tests: $(TESTS)
execs: $(EXECS)
derived: $(DERIVED) 

all: objects execs derived tests 

clean: 
	rm -f $(TESTS) $(EXECS) $(OBJECTS) 

anew: clean all





