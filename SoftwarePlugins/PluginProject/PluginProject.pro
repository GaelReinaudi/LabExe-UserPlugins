# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = PluginProject
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET
QT += core gui
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT PLUGINPROJECT_LIB
INCLUDEPATH += ./../../src \
    ./../../include \
    ./GeneratedFiles \
    ./GeneratedFiles/Release \
    .
LIBS += -L"./../../lib" \
    -L"./../../bin" \
    -llabexe
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(PluginProject.pri)
