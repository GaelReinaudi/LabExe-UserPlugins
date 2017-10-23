TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BINDIR}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += PXILABEXE_LIB
include(PluginPxiSystem.pri)
