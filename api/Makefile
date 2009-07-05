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

SOURCES       = $(SOURCE)/main.cpp \
                $(SOURCE)/TSApplication.cpp \
                $(SOURCE)/TSListener.cpp \
                $(SOURCE)/TSEvent.cpp

OBJECTS       = $(RELEASE)/main.o \
                $(RELEASE)/TSApplication.o \
                $(RELEASE)/TSListener.o \
                $(RELEASE)/TSEvent.o
                
TARGET        = $(RELEASE)/api

####### Compile
all: $(TARGET)

$(TARGET): dirrelease $(OBJECTS)
	$(LINK) $(INCPATH) $(LIBS) -ltskernel -o $(TARGET) $(OBJECTS)
	@echo Build finalizado!

dirrelease: 
	@$(MKDIR) $(RELEASE)

$(RELEASE)/main.o: $(SOURCE)/main.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/main.o $(SOURCE)/main.cpp

$(RELEASE)/TSApplication.o: $(SOURCE)/TSApplication.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/TSApplication.o $(SOURCE)/TSApplication.cpp
	
$(RELEASE)/TSListener.o: $(SOURCE)/TSListener.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/TSListener.o $(SOURCE)/TSListener.cpp

$(RELEASE)/TSEvent.o: $(SOURCE)/TSEvent.cpp
	$(CXX) -c $(INCPATH) $(LIBS) -o $(RELEASE)/TSEvent.o $(SOURCE)/TSEvent.cpp


####### Clean
.PHONY : clean

clean: 
	@$(DEL) $(RELEASE)
	@$(DEL) $(DOC)
	@echo Todos os aquivos foram removidos!
