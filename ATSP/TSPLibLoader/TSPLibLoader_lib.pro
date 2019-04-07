TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

INCLUDEPATH += "../"

SOURCES += \
    #    main.cpp \
    TSPLibLoader.cpp

HEADERS += \
    TSPLibLoader.h

DESTDIR = "../_libs"

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    TARGET = "TSPLibLoaderd"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   TARGET = "TSPLibLoader"
   QMAKE_CXXFLAGS += -O3
}
