ROOTDIR=../..
include $(ROOTDIR)/common.txt

INCLUDE= $(CNINE_INCLUDES) -I$(SNOB2_INCLUDEDIR) -I$(COMBINATORIALDIR) -I$(SNDIR) 

TESTS=$(patsubst %.cpp,%,$(wildcard *.cpp))

ifdef WITH_CUDA
endif 

DEPS=$(SNDIR)/*.hpp $(COMBINATORIALDIR)/*.hpp  

EXECS= 

CNINE_OBJECTS=$(CNINE_CUDADIR)/EigenRoutines.o

CUDA_OBJECTS=  
CUDA_EXTERNS=

ifdef WITH_CUDA
INCLUDE+=-I$(CUDA_HOME)/include
CUDA_OBJECTS+=$(CNINE_ROOT)/cuda/CtensorA_add.o 
CUDA_EXTERNS+=$(CNINE_ROOT)/include/Cnine_base.cu 
endif 

$(TESTS): %: %.cpp
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o $@ $@.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o $@ $@.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif

objects: $(OBJECTS) $(CUDA_OBJECTS)
tests: $(TESTS)
execs: $(EXECS)
derived: $(DERIVED) 

all: objects execs derived tests 

clean: 
	rm -f $(TESTS) $(EXECS) $(OBJECTS) 

anew: clean all




# -------------------------------------------------------------------------------------------------------------





# -------------------------------------------------------------------------------------------------------------




