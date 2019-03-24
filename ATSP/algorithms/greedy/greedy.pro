#TEMPLATE = app
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

TEMPLATE = lib
#CONFIG += console c++11
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

INCLUDEPATH += "../../"
INCLUDEPATH += "../../../"

SOURCES += \
       # main.cpp \
    greedy_algorithm.cpp

HEADERS += \
    greedy_algorithm.h

DESTDIR = "../../_libs"

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    LIBS += ../../_libs/libatsp_based.a
    LIBS += ../../_libs/libbased.a
    LIBS += ../../_libs/libTSPLibLoaderd.a
    TARGET = "GreedyAlgod"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   QMAKE_CXXFLAGS += -O3
   LIBS += ../../_libs/libatsp_base.a
   LIBS += ../../_libs/libbase.a
   LIBS += ../../_libs/libTSPLibLoader.a
   TARGET = "GreedyAlgo"
}


