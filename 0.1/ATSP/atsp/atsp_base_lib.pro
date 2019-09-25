QMAKE_MACOSX_DEPLOYMENT_TARGET = "10.9"

TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

SOURCES += \
    path.cpp \
    algorithm.cpp \
    data.cpp

INCLUDEPATH += "../../"
INCLUDEPATH += "../"

HEADERS += \
    path.h \
    repository.h \
    data.h \
    base.h \
    algorithm.h

DESTDIR = "../_libs"

#debug levels
CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    TARGET = "atsp_based"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   TARGET = "atsp_base"
   QMAKE_CXXFLAGS += -O3
}
