QT *= core

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qxsys/qxlagmeter.h \
    $$PWD/qxsys/qxlagmeterbase.h
SOURCES += \
    $$PWD/qxsys/qxlagmeterbase.cpp

unix:!mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_unix.cpp
}
mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_mac.cpp
}
win32 {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_win.cpp
}
