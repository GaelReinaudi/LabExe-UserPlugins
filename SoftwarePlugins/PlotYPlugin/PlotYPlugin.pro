TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../../../LabExe/plugins/$$TARGET

QT += core gui widgets printsupport

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
	LIBS += -llabexe
}

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

DEFINES += PlotYPlugin_LIB
include(PlotYPlugin.pri)

HEADERS += \
	../../include/QCustomPlot/qcustomplot.h

SOURCES += \
	../../include/QCustomPlot/qcustomplot.cpp
