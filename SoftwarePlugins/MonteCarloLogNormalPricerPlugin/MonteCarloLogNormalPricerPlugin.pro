# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = MonteCarloLogNormalPricerPlugin
DESTDIR = ../../../LabExe/plugins/MonteCarloLogNormalPricerPlugin
QT += core gui script
CONFIG += release
DEFINES += MonteCarloLogNormalPricerPlugin_LIB QT_SCRIPT_LIB
INCLUDEPATH += $(ProjectDir)../../../LabExe/src \
    ./../../../LabExe/include \
    ./GeneratedFiles \
    ./GeneratedFiles/Release \
    .
LIBS += -L"./../../../LabExe/lib" \
    -L"./../../../LabExe/bin" \
    -L"." \
    -llabexe
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(MonteCarloLogNormalPricerPlugin.pri)