TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BINDIR}/plugins/$$TARGET

QT += core gui axserver axcontainer

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \

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
