TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \

LIBS += \
	-L"./../../lib/wlm" -lwlmData

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe
}

DEFINES += PLUGINWAVELENGTHHIGHFINESSE_LIB
include(PluginWavelengthHighFinesse.pri)
