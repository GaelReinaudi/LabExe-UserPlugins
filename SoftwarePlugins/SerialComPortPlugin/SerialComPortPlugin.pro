TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BINDIR}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \
        ./GeneratedFiles \
        .

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe \
        -llabexe -lsetupapi -ladvapi32 -luser32
}
win32:RC_FILE = SerialComPortPlugin.rc

DEFINES += SERIALCOMPORTPLUGIN_LIB
include(SerialComPortPlugin.pri)

