TEMPLATE = lib
#CONFIG += console c++11
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

SOURCES += \
        main.cpp \
    path.cpp \
    algorithm.cpp \
    data.cpp

INCLUDEPATH += "../../"
INCLUDEPATH += "../"
INCLUDEPATH += ../_libs

HEADERS += \
    path.h \
    repository.h \
    data.h \
    base.h \
    algorithm.h

#LIBS += -L../_libs/ -llibbase

#QMAKE_CXXFLAGS += -O3

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
