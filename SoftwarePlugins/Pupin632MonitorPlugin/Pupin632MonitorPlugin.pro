TEMPLATE = lib
CONFIG += plugin
include($$PWD/../../common.pri)
DESTDIR = $${BUILD_ROOT}/plugins/$$TARGET

QT += core gui widgets webenginewidgets

# Handle WebEngine differences between Qt5 and Qt6
greaterThan(QT_MAJOR_VERSION, 5) {
    DEFINES += USING_QT6_WEBENGINE
} else {
    # Qt5's WebEngine has different classes/methods
    DEFINES += USING_QT5_WEBENGINE
}

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

DEFINES += Pupin632MonitorPlugin_LIB
include(Pupin632MonitorPlugin.pri)
