TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../../LabExe/plugins/$$TARGET

QT += core gui widgets printsupport

INCLUDEPATH += \
	./../../../LabExe/src \
	./../../../LabExe/include \
	./GeneratedFiles \
	.

LIBS += \
	-L"./../../../LabExe/lib" \
	-L"./../../../LabExe/bin" \
	-llabexe \
	-lLabExeImaging

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

DEFINES +=  IMAGEPIXELADDERPLUGIN_LIB
include(ImagePixelAdderPlugin.pri)
