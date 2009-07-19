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

SOURCES       = $(SOURCE)/TSApplication.cpp \
                $(SOURCE)/TSListener.cpp \
                $(SOURCE)/TSEvent.cpp \
                $(SOURCE)/TSTouchMarkerListener.cpp \
                $(SOURCE)/TSTouchMarkerEvent.cpp

OBJECTS       = $(RELEASE)/TSApplication.o \
                $(RELEASE)/TSListener.o \
                $(RELEASE)/TSEvent.o \
                $(RELEASE)/TSTouchMarkerListener.o \
                $(RELEASE)/TSTouchMarkerEvent.o
                
TARGET        = $(RELEASE)/libtscore.so

INSTALLDIR    = /usr/local/lib
INCLUDEDIR	  = /usr/local/include/TouchSheep/TSCore

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	$(LINK) -shared -Wl,-soname,libtscore.so $(INCPATH) $(LIBS) -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/TSApplication.o: $(SOURCE)/TSApplication.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSApplication.o $(SOURCE)/TSApplication.cpp
	
$(RELEASE)/TSListener.o: $(SOURCE)/TSListener.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSListener.o $(SOURCE)/TSListener.cpp

$(RELEASE)/TSEvent.o: $(SOURCE)/TSEvent.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSEvent.o $(SOURCE)/TSEvent.cpp

$(RELEASE)/TSTouchMarkerListener.o: $(SOURCE)/TSTouchMarkerListener.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSTouchMarkerListener.o $(SOURCE)/TSTouchMarkerListener.cpp

$(RELEASE)/TSTouchMarkerEvent.o: $(SOURCE)/TSTouchMarkerEvent.cpp
	$(CXX) -c -fPIC $(INCPATH) $(LIBS) -o $(RELEASE)/TSTouchMarkerEvent.o $(SOURCE)/TSTouchMarkerEvent.cpp

####### Install
.PHONY : install

install:
	cp $(TARGET) $(INSTALLDIR)/libtscore.so
	@$(MKDIR) $(INCLUDEDIR)
	cp $(SOURCE)/TSApplication.h $(INCLUDEDIR)/TSApplication.h
	cp $(SOURCE)/TSListener.h $(INCLUDEDIR)/TSListener.h
	cp $(SOURCE)/TSEvent.h $(INCLUDEDIR)/TSEvent.h
	cp $(SOURCE)/TSTouchMarkerListener.h $(INCLUDEDIR)/TSTouchMarkerListener.h
	cp $(SOURCE)/TSTouchMarkerEvent.h $(INCLUDEDIR)/TSTouchMarkerEvent.h
	ldconfig
	@echo Instalado com sucesso!

####### Uninstall
.PHONY : uninstall

uninstall:
	rm $(INSTALLDIR)/libtscore.so
	rm $(INCLUDEDIR)/TSApplication.h
	rm $(INCLUDEDIR)/TSListener.h
	rm $(INCLUDEDIR)/TSEvent.h
	@echo Removido com sucesso!

####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!