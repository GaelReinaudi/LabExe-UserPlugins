TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../../LabExe/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
	./../../../LabExe/src \
	./../../../LabExe/include \
	./GeneratedFiles \
	.

LIBS += \
	-L"./../../../LabExe/lib" \
	-L"./../../../LabExe/bin"

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe
}

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

DEFINES += ParamSupplierPlugin_LIB
include(ParamSupplierPlugin.pri)
