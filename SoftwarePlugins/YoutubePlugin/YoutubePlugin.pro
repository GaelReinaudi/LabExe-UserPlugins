# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = YoutubePlugin
DESTDIR = ../../plugins/YoutubePlugin
QT += core gui network webkit
CONFIG += release
DEFINES += QT_LARGEFILE_SUPPORT YoutubePlugin_LIB QT_NETWORK_LIB QT_WEBKIT_LIB
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
include(YoutubePlugin.pri)