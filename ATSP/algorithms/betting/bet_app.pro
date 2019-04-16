QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = bet_app
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += "../../../QCustomPlot/include"
INCLUDEPATH += "../../"
INCLUDEPATH += "../../../"
INCLUDEPATH += "../"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        workerthread.cpp

HEADERS += \
        mainwindow.h \
        workerthread.h

FORMS += \
        mainwindow.ui

# Tell the qcustomplot header that it will be used as library:
DEFINES += QCUSTOMPLOT_USE_LIBRARY

CONFIG(debug, debug|release) {
    LIBS += ../../../QCustomPlot/lib/libqcustommmplotd.a
    LIBS += ../../_libs/libatsp_based.a
    LIBS += ../../_libs/libbased.a
    LIBS += ../../_libs/libTSPLibLoaderd.a
    LIBS += ../../_libs/libGreedyAlgod.a
    LIBS += ../../_libs/libBetAlgod.a

    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
    LIBS += ../../../QCustomPlot/lib/libqcustomplot.a
    LIBS += ../../_libs/libatsp_base.a
    LIBS += ../../_libs/libbase.a
    LIBS += ../../_libs/libTSPLibLoader.a
    LIBS += ../../_libs/libGreedyAlgo.a
    LIBS += ../../_libs/libBetAlgo.a
    macx | linux: QMAKE_CXXFLAGS += -O3
}
