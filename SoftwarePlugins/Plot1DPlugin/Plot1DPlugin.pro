TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)


QT += core gui widgets printsupport

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

DEFINES += Plot1DPlugin_LIB
include(Plot1DPlugin.pri)

HEADERS += \
	../../include/QCustomPlot/qcustomplot.h

SOURCES += \
	../../include/QCustomPlot/qcustomplot.cpp
