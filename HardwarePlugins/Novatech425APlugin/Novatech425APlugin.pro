TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET

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

DEFINES += QT_LARGEFILE_SUPPORT Novatech425APLUGIN_LIB

include(Novatech425APlugin.pri)
RC_FILE = Novatech425APlugin.rc
