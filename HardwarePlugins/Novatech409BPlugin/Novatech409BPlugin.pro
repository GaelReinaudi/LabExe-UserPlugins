TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)

QT += core gui widgets
# Disable ActiveX support temporarily to fix build issues
# QT += axserver axcontainer

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

DEFINES += QT_LARGEFILE_SUPPORT Novatech409BPLUGIN_LIB

include(Novatech409BPlugin.pri)
win32:RC_FILE = Novatech409BPlugin.rc
