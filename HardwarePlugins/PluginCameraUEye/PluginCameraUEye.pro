TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../../LabExe/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
	./../../../LabExe/src \
	./../../include \
	./GeneratedFiles \
	.

LIBS += \
	-L"./../../lib" \
	-L"./../../../LabExe/bin" \
	-L"./../../lib/uEye" -luEye_api_64

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
