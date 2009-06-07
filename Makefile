
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
SOURCES       = $(SOURCE)/main.c \
                $(SOURCE)/driver/ConnectedComponent.c  \
                $(SOURCE)/driver/Camshift.c 

OBJECTS       = $(RELEASE)/main.o \
                $(RELEASE)/ConnectedComponent.o \
                $(RELEASE)/Camshift.o 
                
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

$(RELEASE)/ConnectedComponent.o: $(SOURCE)/driver/ConnectedComponent.c
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/ConnectedComponent.o $(SOURCE)/driver/ConnectedComponent.c

$(RELEASE)/main.o: $(SOURCE)/main.c
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/main.o $(SOURCE)/main.c

$(RELEASE)/Camshift.o: $(SOURCE)/driver/Camshift.c
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/Camshift.o $(SOURCE)/driver/Camshift.c


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

