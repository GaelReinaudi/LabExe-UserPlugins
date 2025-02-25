TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \
        "C:/Program Files/IVI Foundation/VISA/Win64\Include" \

LIBS += -L"./../../lib/thorlabs" -lvisa64

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += QT_LARGEFILE_SUPPORT ThorlabsTSP01Plugin_LIB

include(ThorlabsTSP01Plugin.pri)
