# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = StepperPlugin
DESTDIR = ../../../LabExe/plugins/StepperPlugin
QT += core gui
CONFIG += release
DEFINES += StepperPlugin_LIB
INCLUDEPATH += ./../../../LabExe/src \
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
include(StepperPlugin.pri)
