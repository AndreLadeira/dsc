TEMPLATE = subdirs

SUBDIRS = \
       ../ATSP/atsp/atsp_base_lib.pro \
       ../ATSP/TSPLibLoader/TSPLibLoader_app.pro

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
