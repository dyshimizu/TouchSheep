####### Compiler, tools and options
CC            = gcc
CXX           = g++
LINK          = g++
DEL           = rm -R -f
MKDIR         = mkdir -p
INCPATH       = `pkg-config --cflags opencv` -I/usr/local/include/TouchSheep -I/usr/include/qt4/QtCore \
 				-I/usr/include/qt4/QtGui -I/usr/include/qt4
LIBS          = `pkg-config --libs opencv` -lpthread
DOC           = doc
SOURCE        = src
RELEASE       = release
####### Files

SOURCES       = $(SOURCE)/main.cpp \
				$(SOURCE)/TSDisplayVideo.cpp \
				$(SOURCE)/TSListenerDisplayVideo.cpp \
				$(SOURCE)/TSTouchMarkerListenerPaint.cpp

OBJECTS       = $(RELEASE)/main.o \
				$(RELEASE)/TSDisplayVideo.o \
				$(RELEASE)/TSListenerDisplayVideo.o \
				$(RELEASE)/TSTouchMarkerListenerPaint.o
                
TARGET        = $(RELEASE)/tsPaint

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS) copyfundo
	$(LINK) $(INCPATH) $(LIBS) -ltskernel -ltscore -ltsgui -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

copyfundo:
	cp fundo.bmp $(RELEASE)/fundo.bmp

$(RELEASE)/main.o: $(SOURCE)/main.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/main.o $(SOURCE)/main.cpp

$(RELEASE)/TSDisplayVideo.o: $(SOURCE)/TSDisplayVideo.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/TSDisplayVideo.o $(SOURCE)/TSDisplayVideo.cpp

$(RELEASE)/TSListenerDisplayVideo.o: $(SOURCE)/TSListenerDisplayVideo.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/TSListenerDisplayVideo.o $(SOURCE)/TSListenerDisplayVideo.cpp

$(RELEASE)/TSTouchMarkerListenerPaint.o: $(SOURCE)/TSTouchMarkerListenerPaint.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/TSTouchMarkerListenerPaint.o $(SOURCE)/TSTouchMarkerListenerPaint.cpp


####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
