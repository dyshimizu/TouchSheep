####### Compiler, tools and options
CC            = gcc
CXX           = g++
LINK          = g++
DEL           = rm -R -f
MKDIR         = mkdir -p
INCPATH       = `pkg-config --cflags opencv` -I/usr/local/include/TouchSheep
LIBS          = `pkg-config --libs opencv` -ltskernel
DOC           = doc
SOURCE        = src
RELEASE       = release
####### Files

SOURCES       = $(SOURCE)/algo.cpp

OBJECTS       = $(RELEASE)/algo.o
                
TARGET        = $(RELEASE)/libtsgui.so

INSTALLDIR    = /usr/local/lib
INCLUDEDIR	  = /usr/local/include/TouchSheep/TSGui

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	$(LINK) -shared -Wl,-soname,libtsgui.so $(INCPATH) $(LIBS) -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/algo.o: $(SOURCE)/algo.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/algo.o $(SOURCE)/algo.cpp

####### Install
.PHONY : install

install:
	cp $(TARGET) $(INSTALLDIR)/libtsgui.so
	@$(MKDIR) $(INCLUDEDIR)
	cp $(SOURCE)/algo.h $(INCLUDEDIR)/algo.h
	ldconfig
	@echo Instalado com sucesso!

####### Uninstall
.PHONY : uninstall

uninstall:
	rm $(INSTALLDIR)/libtsgui.so
	rm $(INCLUDEDIR)/algo.h
	@echo Removido com sucesso!

####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
