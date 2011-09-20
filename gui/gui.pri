QT *= core gui

HEADERS += \
    $$PWD/closedialog.h \
    $$PWD/graphicsutil.h \
    $$PWD/splashscreen.h
SOURCES += \
    $$PWD/closedialog.cpp \
    $$PWD/graphicsutil.cpp \
    $$PWD/splashscreen.cpp
FORMS += \
    $$PWD/closedialog.ui

win32 {
    RESOURCES += \
        $$PWD/resources/qss/qss.qrc
}
