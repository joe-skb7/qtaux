QT *= core

INCLUDEPATH *= $$PWD
DEPENDPATH *= $$PWD

HEADERS += \
    $$PWD/qxsys/qxlagmeter.h \
    $$PWD/qxsys/qxlagmeterbase.h \
    $$PWD/qxsys/qxosprober.h \
    $$PWD/qxsys/qxpathprober.h
SOURCES += \
    $$PWD/qxsys/qxlagmeterbase.cpp

unix:!mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_unix.cpp \
        $$PWD/qxsys/qxosprober_unix.cpp \
        $$PWD/qxsys/qxpathprober_unix.cpp
}
mac {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_mac.cpp \
        $$PWD/qxsys/qxosprober_mac.cpp \
        $$PWD/qxsys/qxpathprober_mac.cpp
}
win32 {
    SOURCES += \
        $$PWD/qxsys/qxlagmeter_win.cpp \
        $$PWD/qxsys/qxosprober_win.cpp \
        $$PWD/qxsys/qxpathprober_win.cpp
}
