# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = LabNotesLoggerPlugin
DESTDIR = ../../../LabExe/plugins/LabNotesLoggerPlugin
QT += core gui
CONFIG += debug
DEFINES += QT_LARGEFILE_SUPPORT LabNotesLoggerPlugin_LIB
INCLUDEPATH += ./../../../LabExe/src \
    ./../../../LabExe/include \
    ./GeneratedFiles \
    ./GeneratedFiles/Debug \
    .
LIBS += -L"./../../../LabExe/lib" \
    -L"./../../../LabExe/bin" \
    -llabexe_D
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles