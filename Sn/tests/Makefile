ROOTDIR=../..
include $(ROOTDIR)/common.txt

INCLUDE= $(CNINE_INCLUDES) -I$(SNOB2_INCLUDEDIR) -I$(COMBINATORIALDIR) -I$(SNDIR) 

TESTS= testSn testSnFunction testSnOverSm testSnOverSmFunction testSnIrrep testSnType testSnRepresentation \
testSnPart testSnVec testClausenFFT testClausenFFT2 testSnClassFunction testSnCharacter testSnCG #testSnMultiVec testFourierTransform

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


testSnOverSmFunction: testSnOverSmFunction.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnOverSmFunction testSnOverSmFunction.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnOverSmFunction testSnOverSmFunction.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
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


testSnModule: testSnModule.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnModule testSnModule.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnModule testSnModule.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnRepresentation: testSnRepresentation.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnRepresentation testSnRepresentation.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnRepresentation testSnRepresentation.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnVec: testSnVec.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnVec testSnVec.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnVec testSnVec.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnMultiVec: testSnMultiVec.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnMultiVec testSnMultiVec.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnMultiVec testSnMultiVec.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testFourierTransform: testFourierTransform.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testFourierTransform testFourierTransform.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testFourierTransform testFourierTransform.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testClausenFFT: testClausenFFT.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testClausenFFT testClausenFFT.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testClausenFFT testClausenFFT.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testClausenFFT2: testClausenFFT2.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testClausenFFT2 testClausenFFT2.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testClausenFFT2 testClausenFFT2.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnCG: testSnCG.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnCG testSnCG.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnCG testSnCG.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnClassFunction: testSnClassFunction.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnClassFunction testSnClassFunction.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnClassFunction testSnClassFunction.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
endif


testSnCharacter: testSnCharacter.cpp $(DEPS) 
ifdef WITH_CUDA
	$(NVCC) $(NVCCFLAGS) -o testSnCharacter testSnCharacter.cpp $(CUDA_EXTERNS) $(CUDA_OBJECTS) $(CFLAGS) $(MACROS) $(INCLUDE) $(LIBS) 
else
	$(CC) -o testSnCharacter testSnCharacter.cpp $(CFLAGS) $(INCLUDE) $(LIBS) 
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





