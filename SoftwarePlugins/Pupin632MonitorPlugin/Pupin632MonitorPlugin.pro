TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets webenginewidgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \
        ./GeneratedFiles \
        .

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += Pupin632MonitorPlugin_LIB
include(Pupin632MonitorPlugin.pri)
