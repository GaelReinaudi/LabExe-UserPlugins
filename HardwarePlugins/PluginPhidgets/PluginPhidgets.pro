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
	-L"./../../lib/phidgets/x64" -lphidget21

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe
}

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

DEFINES += PLUGINPHIDGETS_LIB
include(PluginPhidgets.pri)
