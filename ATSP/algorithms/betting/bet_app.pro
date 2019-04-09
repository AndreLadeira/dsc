QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = bet_app
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += "../../../QCustomPlot/include"

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Tell the qcustomplot header that it will be used as library:
DEFINES += QCUSTOMPLOT_USE_LIBRARY

CONFIG(debug, debug|release) {
    LIBS += ../../../QCustomPlot/lib/libqcustomplotd.a
}
CONFIG(release, debug|release) {
    LIBS += ../../../QCustomPlot/lib/libqcustomplot.a
}
