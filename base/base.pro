TEMPLATE = lib
#CONFIG += console c++11
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

#INCLUDEPATH += "/Users/ladeira/Documents/src/boost_1_65_1/"
#LIBS += -L"/Users/ladeira/Documents/src/boost_1_65_1/stage/lib/"  -lboost_timer

SOURCES += \
        main.cpp \
    random.cpp \
    histogram.cpp

HEADERS += \
    random.h \
    histogram.h

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    TARGET = "based"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   TARGET = "base"
   QMAKE_CXXFLAGS += -O3
}
