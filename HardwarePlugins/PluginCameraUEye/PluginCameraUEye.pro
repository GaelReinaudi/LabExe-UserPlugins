TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)

QT += core gui widgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \

LIBS += -L$$PWD/../../lib/uEye -luEye_api_64

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
	LIBS += -lLabExeImaging_D
} else {
	LIBS += -llabexe
	LIBS += -lLabExeImaging
}

DEFINES += PLUGINCAMERAUEYE_LIB
include(PluginCameraUEye.pri)
