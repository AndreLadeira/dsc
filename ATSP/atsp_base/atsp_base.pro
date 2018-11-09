TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    path.cpp \
    atsp_data.cpp

INCLUDEPATH += "/Users/ladeira/Documents/src/boost_1_65_1/"

HEADERS += \
    path.h \
    atsp_data.h
