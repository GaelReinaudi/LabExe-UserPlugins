include($$PWD/../LabExe/common.pri)

INCLUDEPATH += ./include

LIBS += \
-L$$PWD/lib \
-L$$PWD/bin

DESTDIR = $${BUILD_ROOT}/bin/plugins/$$TARGET
