#
#  Project to compile QCustomPlot as shared library (.so/.dll) from the amalgamated sources
#

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY
TEMPLATE = lib
CONFIG += debug_and_release build_all
#static {
#  CONFIG += static
#} else {
#  CONFIG += shared
#}

#VERSION = 2.0.1

CONFIG += staticlib
DESTDIR = "../QCustomPlot/lib"


CONFIG(debug, debug|release) {
  #TARGET = $$join(TARGET,,,d) # if compiling in debug mode, append a "d" to the library name
  TARGET = qcustomplotd
  QMAKE_TARGET_PRODUCT = "QCustomPlot (debug mode)"
  QMAKE_TARGET_DESCRIPTION = "Plotting library for Qt (debug mode)"
} else {
  TARGET = qcustomplot
  QMAKE_TARGET_PRODUCT = "QCustomPlot"
  QMAKE_TARGET_DESCRIPTION = "Plotting library for Qt"
}
QMAKE_TARGET_COMPANY = "www.qcustomplot.com"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) by Emanuel Eichhammer"

SOURCES += ./src/qcustomplot.cpp
HEADERS += ./src/qcustomplot.h
