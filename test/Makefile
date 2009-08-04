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
				$(SOURCE)/MyThread.cpp

OBJECTS       = $(RELEASE)/main.o \
				$(RELEASE)/MyThread.o
                
TARGET        = $(RELEASE)/test

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	$(LINK) $(INCPATH) $(LIBS) -ltskernel -ltscore -ltsgui -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/main.o: $(SOURCE)/main.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/main.o $(SOURCE)/main.cpp

$(RELEASE)/MyThread.o: $(SOURCE)/MyThread.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/MyThread.o $(SOURCE)/MyThread.cpp


####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
