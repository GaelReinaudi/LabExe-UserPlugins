TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)


QT += core gui widgets qml

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

DEFINES += PLAINTEXTLOGGERPLUGIN_LIB QT_SCRIPT_LIB
include(PlainTextLoggerPlugin.pri)
