
HEADERS += ./GNovatech409B.h \
    ./GNovatech409BWidget.h \
    ./hled.h \
    ./PortSettingsWidget.h \
    ../../include/qextserialport/src/qextserialenumerator.h \
    ../../include/qextserialport/src/qextserialenumerator_p.h \
    ../../include/qextserialport/src/qextserialport.h \
    ../../include/qextserialport/src/qextserialport_global.h \
    ../../include/qextserialport/src/qextserialport_p.h \
    ./Novatech409Bplugin.h \
    ./Novatech409Bplugin_global.h
SOURCES += ./GNovatech409B.cpp \
    ./GNovatech409BWidget.cpp \
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

SOURCES += ./Novatech409Bplugin.cpp

FORMS += ./GNovatech409BWidget.ui \
    ./PortSettingsWidget.ui
