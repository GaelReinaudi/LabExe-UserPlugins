TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
 = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        $$PWD/../../../LabExe/src \
        $$PWD/../../include \
        "C:/Program Files/IVI Foundation/VISA/Win64\Include" \

LIBS += -L"$$PWD/../../lib/thorlabs" -lvisa64

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += QT_LARGEFILE_SUPPORT ThorlabsTSP01Plugin_LIB

include(ThorlabsTSP01Plugin.pri)
