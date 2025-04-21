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

DEFINES += QT_LARGEFILE_SUPPORT Novatech425APLUGIN_LIB

include(Novatech425APlugin.pri)
RC_FILE = Novatech425APlugin.rc
