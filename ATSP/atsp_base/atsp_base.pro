TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    path.cpp \
    ../../base/random.cpp \
    ../tsplib_reader/tsplib_reader.cpp \
    algorithm.cpp \
    data.cpp

INCLUDEPATH += "/Users/ladeira/Documents/src/boost_1_65_1/"
INCLUDEPATH += "../../"
INCLUDEPATH += "../"

HEADERS += \
    path.h \
    repository.h \
    data.h \
    base.h \
    algorithm.h \
    mask.h

#LIBS += -L"/Users/ladeira/Documents/src/boost_1_65_1/stage/lib/"  -lboost_timer
#QMAKE_CXXFLAGS += -O3

#debug levels
CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
    QMAKE_CXXFLAGS += -O3
}
