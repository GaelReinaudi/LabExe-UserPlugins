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
    LIBS += -lLabExeImaging_D
} else {
    LIBS += -llabexe
    LIBS += -lLabExeImaging
}

DEFINES += IMAGESAVERPLUGIN_LIB
include(ImageSaverPlugin.pri)
