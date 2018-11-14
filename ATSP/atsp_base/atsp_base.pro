TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    path.cpp \
    atsp_data.cpp \
    ../../base/random.cpp \
    ../tsplib_reader/tsplib_reader.cpp

INCLUDEPATH += "/Users/ladeira/Documents/src/boost_1_65_1/"
INCLUDEPATH += "../../"
INCLUDEPATH += "../"

HEADERS += \
    path.h \
    atsp_data.h \
    repository.h
