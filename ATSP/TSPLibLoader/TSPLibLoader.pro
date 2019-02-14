#TEMPLATE = app
TEMPLATE = lib
#CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

INCLUDEPATH += "../"
#LIBS += ../../_libs/libatsp_base.a

SOURCES += \
        main.cpp \
    TSPLibLoader.cpp

HEADERS += \
    TSPLibLoader.h

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    TARGET = "TSPLibLoaderd"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   TARGET = "TSPLibLoader"
   QMAKE_CXXFLAGS += -O3
}
