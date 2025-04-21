TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
 = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets


CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += PXILABEXE_LIB
include(PluginPxiSystem.pri)
