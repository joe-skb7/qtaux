QT *= core

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qxsys/qxlagmeter.h \
    $$PWD/qxsys/qxlagmeterbase.h \
    $$PWD/qxsys/qxosprober.h
SOURCES += \
    $$PWD/qxsys/qxlagmeterbase.cpp

unix:!mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_unix.cpp \
        $$PWD/qxsys/qxosprober_unix.cpp
}
mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_mac.cpp \
        $$PWD/qxsys/qxosprober_mac.cpp
}
win32 {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_win.cpp \
        $$PWD/qxsys/qxosprober_win.cpp
}
