TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
 = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets

INCLUDEPATH += \
        $$PWD/../../../LabExe/src \
        $$PWD/../../include \
        ./GeneratedFiles \
        .

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += MonteCarloLogNormalPricerPlugin_LIB
include(MonteCarloLogNormalPricerPlugin.pri)
