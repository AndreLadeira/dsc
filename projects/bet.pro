#QMAKE_MACOSX_DEPLOYMENT_TARGET = "10.9"
greaterThan(QT_MAJOR_VERSION, 5)

TEMPLATE = subdirs

SUBDIRS = \
        ../base \
        ../ATSP/TSPLibLoader/TSPLibLoader_lib.pro \
        ../ATSP/atsp/atsp_base_lib.pro \
        ../ATSP/algorithms/greedy/greedy_lib.pro \
        ../ATSP/algorithms/betting/bet_lib.pro \
        ../QCustomPlot/sharedlib-compilation.pro \
        ../ATSP/algorithms/betting/bet_app.pro


# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
