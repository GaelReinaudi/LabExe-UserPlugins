
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
	./../../include/qextserialport/src/qextserialenumerator.cpp \
	./../../include/qextserialport/src/qextserialenumerator_win.cpp \
	./../../include/qextserialport/src/qextserialport.cpp \
	./../../include/qextserialport/src/qextserialport_win.cpp \
	./../../include/qextserialport/src/qextwineventnotifier_p.cpp \
	./serialcomportplugin.cpp

FORMS += ./GSerialPortControllerWidget.ui \
    ./PortSettingsWidget.ui
