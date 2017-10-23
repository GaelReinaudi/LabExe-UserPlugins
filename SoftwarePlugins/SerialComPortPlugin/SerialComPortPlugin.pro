TEMPLATE = lib
CONFIG += plugin

QT += core gui widgets
include($$PWD/../common.pri)
DESTDIR = $${BINDIR}/LabExe/plugins/$$TARGET

INCLUDEPATH += \
	./../../../LabExe/src \
	./../../include \
	./GeneratedFiles \
	.

LIBS += \
	-L"./../../../LabExe/lib" \
	-L"./../../../LabExe/bin"

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe \
	-llabexe -lsetupapi -ladvapi32 -luser32
}

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
win32:RC_FILE = SerialComPortPlugin.rc

DEFINES += SERIALCOMPORTPLUGIN_LIB
include(SerialComPortPlugin.pri)

