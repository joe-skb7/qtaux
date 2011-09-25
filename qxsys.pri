QT *= core

INCLUDEPATH *= $$PWD
DEPENDPATH *= $$PWD

HEADERS += \
    $$PWD/qxsys/qxlagmeter.h \
    $$PWD/qxsys/qxlagmeterbase.h \
    $$PWD/qxsys/qxosprober.h \
    $$PWD/qxsys/qxpathprober.h \
    $$PWD/qxsys/qxprocessprober.h \
    $$PWD/qxsys/qxprocessproberbase.h
SOURCES += \
    $$PWD/qxsys/qxlagmeterbase.cpp \
    $$PWD/qxsys/qxprocessproberbase.cpp

unix|mac {
    SOURCES += \
        $$PWD/qxsys/qxprocessprober_unix_common.cpp
}
unix:!mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_unix.cpp \
        $$PWD/qxsys/qxosprober_unix.cpp \
        $$PWD/qxsys/qxpathprober_unix.cpp \
        $$PWD/qxsys/qxprocessprober_unix.cpp
}
mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_mac.cpp \
        $$PWD/qxsys/qxosprober_mac.cpp \
        $$PWD/qxsys/qxpathprober_mac.cpp \
        $$PWD/qxsys/qxprocessprober_mac.cpp
}
win32 {
    HEADERS += \
        $$PWD/qxsys/qxwindowsfirewallsettings.h
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_win.cpp \
        $$PWD/qxsys/qxosprober_win.cpp \
        $$PWD/qxsys/qxpathprober_win.cpp \
        $$PWD/qxsys/qxprocessprober_win.cpp \
        $$PWD/qxsys/qxwindowsfirewallsettings.cpp
}
