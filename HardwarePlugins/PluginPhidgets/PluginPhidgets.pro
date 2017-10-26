TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BINDIR}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \

LIBS += \
    -L"./../../lib/phidgets/x64" -lphidget22

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe
}

DEFINES += PLUGINPHIDGETS_LIB
include(PluginPhidgets.pri)
