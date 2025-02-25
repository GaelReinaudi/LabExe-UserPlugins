TEMPLATE = lib
CONFIG += plugin
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets printsupport

INCLUDEPATH += \
	./../../../LabExe/src \
	./../../../LabExe/include \
	./GeneratedFiles \
	.

LIBS += \
	-L"./../../../LabExe/lib" \
	-L"./../../../LabExe/bin"

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D \
	-lqwt5_D \
	-lQtSolutions_ColorPicker-2.6d
} else {
	LIBS += -llabexe \
	-lqwt5 \
	-lQtSolutions_ColorPicker-2.6
}

MOC_DIR += ./GeneratedFiles
OBJECTS_DIR += ./GeneratedFiles/Obj
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

DEFINES += PARAMPLOTTERPLUGIN_LIB
include(ParamPlotterPlugin.pri)
