TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../../LabExe/plugins/$$TARGET

QT += core gui widgets

DEFINES += RandomNumberGeneratorPlugin_LIB
INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../../LabExe/include \
        ./GeneratedFiles \
        .

LIBS += \
        -L"./../../../LabExe/lib" \
        -L"./../../../LabExe/bin" \
        -llabexe

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

include(RandomNumberPlugin.pri)