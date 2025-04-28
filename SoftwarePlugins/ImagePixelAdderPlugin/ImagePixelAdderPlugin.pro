TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)


QT += core gui widgets


CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
    LIBS += -lLabExeImaging_D
} else {
    LIBS += -llabexe
    LIBS += -lLabExeImaging
}

DEFINES +=  IMAGEPIXELADDERPLUGIN_LIB
include(ImagePixelAdderPlugin.pri)
