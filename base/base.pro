TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "/Users/ladeira/Documents/src/boost_1_65_1/"
LIBS += -L"/Users/ladeira/Documents/src/boost_1_65_1/stage/lib/"  -lboost_timer

SOURCES += \
        main.cpp \
    random.cpp

HEADERS += \
    random.h