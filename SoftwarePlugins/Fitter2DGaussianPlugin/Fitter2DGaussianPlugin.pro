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
    LIBS += -lLabExeImaging_D
} else {
    LIBS += -llabexe
    LIBS += -lLabExeImaging
}

DEFINES += FITTER2DGAUSSIANPLUGIN_LIB
include(Fitter2DGaussianPlugin.pri)
