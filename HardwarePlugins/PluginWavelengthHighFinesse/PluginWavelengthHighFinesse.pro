TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
 = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets


LIBS += \
	-L"$$PWD/../../lib/wlm" -lwlmData

CONFIG(debug, debug|release) {
	LIBS += -llabexe_D
} else {
	LIBS += -llabexe
}

DEFINES += PLUGINWAVELENGTHHIGHFINESSE_LIB
include(PluginWavelengthHighFinesse.pri)
