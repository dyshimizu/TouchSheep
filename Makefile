
####### Compiler, tools and options
CC            = gcc
CXX           = g++
LINK          = g++
DEL           = rm -R -f
MKDIR         = mkdir -p
INCPATH       = -I/usr/include/qt4/QtCore \
                -I/usr/include/qt4/QtGui \
                -I/usr/include/qt4
LIBS          = -L/usr/lib \
                -lpthread
DOC           = doc

####### Files
SOURCES       = $(SOURCE)/main.c \
                $(SOURCE)ConnectedComponent.c 

OBJECTS       = $(RELEASE)/main.o \
                $(RELEASE)/ConnectedComponent.o 
                
TARGET        = $(RELEASE)/projeto

SOURCES       = $(TEST)/testRunner.cpp \
                $(TEST)/mainTest.cpp 

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	$(LINK) $(INCPATH) $(LIBS) -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/ConnectedComponent.o: $(SOURCE)/ConnectedComponent.c
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/ConnectedComponent.o $(SOURCE)/ConnectedComponent.c

$(RELEASE)/main.o: $(SOURCE)/main.c
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/main.o $(SOURCE)/main.c


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

