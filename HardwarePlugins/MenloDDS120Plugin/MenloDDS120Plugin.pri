
HEADERS += ./GSerialPortController.h \
    ./GSerialPortControllerWidget.h \
    ./hled.h \
    ./PortSettingsWidget.h \
    ./qextserialport/src/qextserialenumerator.h \
    ./qextserialport/src/qextserialenumerator_p.h \
    ./qextserialport/src/qextserialport.h \
    ./qextserialport/src/qextserialport_global.h \
    ./qextserialport/src/qextserialport_p.h \
    ./serialcomportplugin.h \
    ./serialcomportplugin_global.h
SOURCES += ./GSerialPortController.cpp \
    ./GSerialPortControllerWidget.cpp \
    ./hled.cpp \
    ./PortSettingsWidget.cpp \
    ./qextserialport/src/qextserialenumerator.cpp \
    ./qextserialport/src/qextserialenumerator_win.cpp \
    ./qextserialport/src/qextserialport.cpp \
    ./qextserialport/src/qextserialport_win.cpp \
    ./serialcomportplugin.cpp
FORMS += ./GSerialPortControllerWidget.ui \
    ./PortSettingsWidget.ui
