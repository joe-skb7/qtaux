QT *= core

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

HEADERS += \
    $$PWD/sys/lagmeter.h \
    $$PWD/sys/lagmeterbase.h
SOURCES += \
    $$PWD/sys/lagmeterbase.cpp

unix:!mac {
    SOURCES += \
        $$PWD/sys/lagmeter_unix.cpp
}
mac {
    SOURCES += \
        $$PWD/sys/lagmeter_mac.cpp
}
win32 {
    SOURCES += \
        $$PWD/sys/lagmeter_win.cpp
}
