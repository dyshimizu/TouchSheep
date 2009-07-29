####### Compiler, tools and options
CC            = gcc
CXX           = g++
LINK          = g++
DEL           = rm -R -f
MKDIR         = mkdir -p
INCPATH       = -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I/usr/local/include/TouchSheep \
				`pkg-config --cflags opencv`
LIBS          = -lQtGui -lQtCore -lpthread -ltskernel -ltscore
DOC           = doc
SOURCE        = src
RELEASE       = release
####### Files

SOURCES       = $(SOURCE)/TSImageDisplay.cpp

OBJECTS       = $(RELEASE)/TSImageDisplay.o
                
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

$(RELEASE)/TSImageDisplay.o: $(SOURCE)/TSImageDisplay.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSImageDisplay.o $(SOURCE)/TSImageDisplay.cpp


####### Install
.PHONY : install

install:
	cp $(TARGET) $(INSTALLDIR)/libtsgui.so
	@$(MKDIR) $(INCLUDEDIR)
	cp $(SOURCE)/TSImageDisplay.h $(INCLUDEDIR)/TSImageDisplay.h
	ldconfig
	@echo Instalado com sucesso!

####### Uninstall
.PHONY : uninstall

uninstall:
	rm $(INSTALLDIR)/libtsgui.so
	rm $(INCLUDEDIR)/TSImageDisplay.h
	@echo Removido com sucesso!

####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
