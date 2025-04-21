TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)

QT += core gui widgets

LIBS += \
    -lsetupapi \
    -ladvapi32 \
    -luser32

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

#DEF_FILE = qaxserver.def
#RC_FILE  = qaxserver.rc

DEFINES += QT_LARGEFILE_SUPPORT MenloDDS120PLUGIN_LIB

include(MenloDDS120Plugin.pri)
RC_FILE = MenloDDS120Plugin.rc

HEADERS += \
    strgchar.h
