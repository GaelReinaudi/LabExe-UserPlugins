include($$PWD/../LabExe/common.pri)

INCLUDEPATH += \
    $$PWD/../LabExe/src \
    $$PWD/include \
    ./GeneratedFiles \
    .

LIBS += \
-L$$PWD/lib \
#-L$$PWD/bin

DESTDIR = $${BUILD_ROOT}/bin/plugins/$$TARGET
