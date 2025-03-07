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

DEFINES += PlotYPlugin_LIB
include(PlotYPlugin.pri)

HEADERS += \
	../../include/QCustomPlot/qcustomplot.h

SOURCES += \
	../../include/QCustomPlot/qcustomplot.cpp
