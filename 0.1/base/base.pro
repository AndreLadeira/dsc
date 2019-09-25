QMAKE_MACOSX_DEPLOYMENT_TARGET = "10.9"

TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

SOURCES += \
    random.cpp \
    histogram.cpp

HEADERS += \
    random.h \
    histogram.h

DESTDIR = "../ATSP/_libs"

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    TARGET = "based"

}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   TARGET = "base"
   QMAKE_CXXFLAGS += -O3
}
