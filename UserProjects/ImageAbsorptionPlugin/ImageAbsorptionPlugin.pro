# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = ImageAbsorptionPlugin
DESTDIR = ../../plugins/ImageAbsorptionPlugin
QT += core gui
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT IMAGEABSORPTIONPLUGIN_LIB
INCLUDEPATH += ./../../src \
    ./../../include \
    ./GeneratedFiles \
    ./GeneratedFiles/Release \
    .
LIBS += -L"./../../../LabExe/lib" \
    -L"./../../../LabExe/bin" \
    -llabexe
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(ImageAbsorptionPlugin.pri)
