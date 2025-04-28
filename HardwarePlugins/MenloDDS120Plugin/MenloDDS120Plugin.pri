
HEADERS += ./GMenloDDS120.h \
    ./GMenloDDS120Widget.h \
    ./hled.h \
    ./PortSettingsWidget.h \
    ../../include/qextserialport/src/qextserialenumerator.h \
    ../../include/qextserialport/src/qextserialenumerator_p.h \
    ../../include/qextserialport/src/qextserialport.h \
    ../../include/qextserialport/src/qextserialport_global.h \
    ../../include/qextserialport/src/qextserialport_p.h \
    ./MenloDDS120plugin.h \
    ./MenloDDS120plugin_global.h
SOURCES += ./GMenloDDS120.cpp \
    ./GMenloDDS120Widget.cpp \
    ./hled.cpp \
    ./PortSettingsWidget.cpp \
    ../../include/qExtSerialPort/src/qextserialenumerator.cpp \
    ../../include/qExtSerialPort/src/qextserialport.cpp \

win32 {
    SOURCES += \
        ../../include/qExtSerialPort/src/qextserialenumerator_win.cpp \
        ../../include/qExtSerialPort/src/qextserialport_win.cpp
}

unix {
    SOURCES += \
        ../../include/qExtSerialPort/src/qextserialenumerator_linux.cpp \
        ../../include/qExtSerialPort/src/qextserialport_unix.cpp
}

SOURCES += ./MenloDDS120plugin.cpp

FORMS += ./GMenloDDS120Widget.ui \
    ./PortSettingsWidget.ui
