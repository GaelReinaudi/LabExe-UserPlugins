TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)

QT += core gui widgets


LIBS += \
    -L"$$PWD/../../lib/phidgets/x64" -lphidget22

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe
}

DEFINES += PLUGINPHIDGETS_LIB
include(PluginPhidgets.pri)
