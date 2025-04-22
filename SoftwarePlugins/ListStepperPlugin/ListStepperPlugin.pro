QT       += core gui widgets
CONFIG  += plugin
TEMPLATE = lib

include($$PWD/../../common.pri)

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

DEFINES += ListStepperPlugin_LIB LISTSTEPPERPLUGIN_LIBRARY

# Including sources and headers from the pri file
include(ListStepperPlugin.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
} 