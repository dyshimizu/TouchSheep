TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += . /usr/local/include/TouchSheep /usr/include/qt4/QtCore /usr/include/qt4/QtGui /usr/include/qlude/qt4 /usr/include/opencv src
LIBS += -ltskernel -ltscore -ltsgui

# Input
HEADERS += src/TSVideoDisplay.h src/TSListenerGallery.h src/QWidgetStartup.h
SOURCES += src/main.cpp src/TSVideoDisplay.cpp src/TSListenerGallery.cpp src/QWidgetStartup.cpp
