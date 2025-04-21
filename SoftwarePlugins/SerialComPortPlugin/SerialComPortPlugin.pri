
HEADERS += ./GSerialPortController.h \
    ./GSerialPortControllerWidget.h \
    ./hled.h \
    ./PortSettingsWidget.h \
	./../../include/qextserialport/src/qextserialenumerator.h \
	./../../include/qextserialport/src/qextserialenumerator_p.h \
	./../../include/qextserialport/src/qextserialport.h \
	./../../include/qextserialport/src/qextserialport_global.h \
	./../../include/qextserialport/src/qextserialport_p.h \
    ./serialcomportplugin.h \
    ./serialcomportplugin_global.h

SOURCES += ./GSerialPortController.cpp \
    ./GSerialPortControllerWidget.cpp \
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

SOURCES += ./serialcomportplugin.cpp

FORMS += ./GSerialPortControllerWidget.ui \
    ./PortSettingsWidget.ui
