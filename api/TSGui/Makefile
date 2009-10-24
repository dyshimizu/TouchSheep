####### Compiler, tools and options
CC            = gcc
CXX           = g++
LINK          = g++
DEL           = rm -R -f
MKDIR         = mkdir -p
INCPATH       = -I/usr/local/include/TouchSheep `pkg-config --cflags opencv`
LIBS          = -lpthread -ltskernel -ltscore
DOC           = doc
SOURCE        = src
RELEASE       = release
####### Files

SOURCES       = $(SOURCE)/TSDisplay.cpp \
				$(SOURCE)/TSListenerDisplay.cpp

OBJECTS       = $(RELEASE)/TSDisplay.o \
				$(RELEASE)/TSListenerDisplay.o
                
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

$(RELEASE)/TSDisplay.o: $(SOURCE)/TSDisplay.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSDisplay.o $(SOURCE)/TSDisplay.cpp

$(RELEASE)/TSListenerDisplay.o: $(SOURCE)/TSListenerDisplay.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSListenerDisplay.o $(SOURCE)/TSListenerDisplay.cpp


####### Install
.PHONY : install

install:
	cp $(TARGET) $(INSTALLDIR)/libtsgui.so
	@$(MKDIR) $(INCLUDEDIR)
	cp $(SOURCE)/TSDisplay.h $(INCLUDEDIR)/TSDisplay.h
	cp $(SOURCE)/TSListenerDisplay.h $(INCLUDEDIR)/TSListenerDisplay.h
	ldconfig
	@echo Instalado com sucesso!

####### Uninstall
.PHONY : uninstall

uninstall:
	rm $(INSTALLDIR)/libtsgui.so
	rm $(INCLUDEDIR)/TSDisplay.h
	rm $(INCLUDEDIR)/TSListenerDisplay.h
	@echo Removido com sucesso!

####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
