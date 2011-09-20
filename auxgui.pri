QT *= core gui

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

HEADERS += \
    $$PWD/gui/closedialog.h \
    $$PWD/gui/graphicsutil.h \
    $$PWD/gui/splashscreen.h
SOURCES += \
    $$PWD/gui/closedialog.cpp \
    $$PWD/gui/graphicsutil.cpp \
    $$PWD/gui/splashscreen.cpp
FORMS += \
    $$PWD/gui/closedialog.ui

win32 {
    RESOURCES += \
        $$PWD/gui/resources/qss/qss.qrc
}
