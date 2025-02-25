TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)


QT += core gui widgets qml

INCLUDEPATH += \
        ./../../../LabExe/src \
        ./../../include \
        ./GeneratedFiles \
        .

CONFIG(debug, debug|release) {
    LIBS += -llabexe_D
} else {
    LIBS += -llabexe
}

DEFINES += NUMERICALEXPRESSIONPLUGIN_LIB
include(NumericalExpressionPlugin.pri)
