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

SOURCES       = $(SOURCE)/ConnectedComponent.c  \
                $(SOURCE)/Camshift.c \
                $(SOURCE)/Kernel.c 

OBJECTS       = $(RELEASE)/ConnectedComponent.o \
                $(RELEASE)/Camshift.o \
                $(RELEASE)/Kernel.o 
                
TARGET        = $(RELEASE)/libtskernel.so

INSTALLDIR    = /usr/local/lib/libtskernel.so
INCLUDE       = $(SOURCE)/TSKernel.h
INCLUDEDIR	  = /usr/local/include/TSKernel.h

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	$(LINK) -shared -Wl,-soname,libtskernel.so $(INCPATH) $(LIBS) -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/ConnectedComponent.o: $(SOURCE)/ConnectedComponent.c
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/ConnectedComponent.o $(SOURCE)/ConnectedComponent.c

$(RELEASE)/Camshift.o: $(SOURCE)/Camshift.c
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/Camshift.o $(SOURCE)/Camshift.c

$(RELEASE)/Kernel.o: $(SOURCE)/Kernel.c
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/Kernel.o $(SOURCE)/Kernel.c

####### Install
.PHONY : install

install:
	cp $(TARGET) $(INSTALLDIR)
	cp $(INCLUDE) $(INCLUDEDIR)
	ldconfig
	@echo Instalado com sucesso!

####### Uninstall
.PHONY : uninstall

uninstall:
	rm $(INSTALLDIR)
	rm $(INCLUDEDIR)
	@echo Removido com sucesso!



####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
