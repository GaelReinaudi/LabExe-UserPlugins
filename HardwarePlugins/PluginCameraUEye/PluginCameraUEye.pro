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
	-luEye_api

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
	LIBS += -lLabExeImaging_D
} else {
	LIBS += -llabexe
	LIBS += -lLabExeImaging
}

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

DEFINES += PLUGINCAMERAUEYE_LIB
include(PluginCameraUEye.pri)
