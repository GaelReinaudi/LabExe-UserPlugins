TEMPLATE = lib
CONFIG += plugin

TARGET = Plot1DPlugin
DESTDIR = ../../../LabExe/plugins/Plot1DPlugin
QT += core gui widgets printsupport

DEFINES += Plot1DPlugin_LIB
INCLUDEPATH += \
	./../../../LabExe/src \
	./../../../LabExe/include \
	./GeneratedFiles \
	./GeneratedFiles/Release \
	.

LIBS += \
	-L"./../../../LabExe/lib" \
	-L"./../../../LabExe/bin" \
	-llabexe

DEPENDPATH += .
MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

include(Plot1DPlugin.pri)

OTHER_FILES +=

