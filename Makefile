
####### Compiler, tools and options
CC            = gcc
CXX           = g++
LINK          = g++
DEL           = rm -R -f
MKDIR         = mkdir -p
INCPATH       = `pkg-config --cflags opencv`
LIBS          = `pkg-config --libs opencv`
DOC           = doc
SOURCE        = src
RELEASE       = release
####### Files
SOURCES       = $(SOURCE)/main.c

OBJECTS       = $(RELEASE)/main.o
                
TARGET        = $(RELEASE)/projeto

KERNELSOURCES       = $(SOURCE)/driver/ConnectedComponent.c  \
                      $(SOURCE)/driver/Camshift.c \
                      $(SOURCE)/driver/Kernel.c 

KERNELOBJECTS       = $(RELEASE)/ConnectedComponent.o \
                      $(RELEASE)/Camshift.o \
                      $(RELEASE)/Kernel.o 
                
KERNELTARGET        = $(RELEASE)/libtskernel.so

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	export LD_LIBRARY_PATH=release
	$(LINK) $(INCPATH) $(LIBS) -Lrelease -ltskernel -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/main.o: $(SOURCE)/main.c
	$(CXX) -c $(INCPATH) $(LIBS) -ltskernel -o $(RELEASE)/main.o $(SOURCE)/main.c

####### TSKernel
.PHONY : tskernel

tskernel: $(KERNELTARGET)

$(KERNELTARGET): dirkernelrelease $(KERNELOBJECTS)
	$(LINK) -shared -Wl,-soname,libtskernel.so $(INCPATH) $(LIBS) -o $(KERNELTARGET) $(KERNELOBJECTS)
	@echo Build finalizado!

dirkernelrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/ConnectedComponent.o: $(SOURCE)/driver/ConnectedComponent.c
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/ConnectedComponent.o $(SOURCE)/driver/ConnectedComponent.c

$(RELEASE)/Camshift.o: $(SOURCE)/driver/Camshift.c
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/Camshift.o $(SOURCE)/driver/Camshift.c

$(RELEASE)/Kernel.o: $(SOURCE)/driver/Kernel.c
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/Kernel.o $(SOURCE)/driver/Kernel.c



####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!

####### Doc
.PHONY : doc

doc:
	doxygen doc.config

