TEMPLATE = subdirs

SUBDIRS = \
        ../base \
        ../ATSP/TSPLibLoader/TSPLibLoader_lib.pro \
        ../ATSP/atsp/atsp_base_lib.pro \
        ../ATSP/algorithms/greedy/greedy_lib.pro \
        ../ATSP/algorithms/betting


# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
