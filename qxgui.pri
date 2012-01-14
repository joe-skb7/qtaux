QT *= core gui

INCLUDEPATH *= $$PWD
DEPENDPATH *= $$PWD

HEADERS += \
    $$PWD/qxgui/qxclosedialog.h \
    $$PWD/qxgui/qxgraphicsutil.h \
    $$PWD/qxgui/qxsplashscreen.h
SOURCES += \
    $$PWD/qxgui/qxclosedialog.cpp \
    $$PWD/qxgui/qxgraphicsutil.cpp \
    $$PWD/qxgui/qxsplashscreen.cpp
FORMS += \
    $$PWD/qxgui/qxclosedialog.ui

win32 {
    RESOURCES += \
        $$PWD/qxgui/resources/qss/qss.qrc
}
