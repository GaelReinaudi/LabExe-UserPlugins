# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = ThorlabsTSP01Plugin
DESTDIR = ../../../LabExe/plugins/ThorlabsTSP01Plugin
QT += core gui
CONFIG += release
DEFINES += ThorlabsTSP01Plugin_LIB
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
include(ThorlabsTSP01Plugin.pri)