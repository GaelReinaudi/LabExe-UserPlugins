TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)


QT += core gui widgets

INCLUDEPATH += \
        $$PWD/../../../LabExe/src \
        $$PWD/../../include \
        ./GeneratedFiles \
        .

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += LabNotesLoggerPlugin_LIB
include(LabNotesLoggerPlugin.pri)
