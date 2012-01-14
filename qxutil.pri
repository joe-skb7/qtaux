QT *= core gui

INCLUDEPATH *= $$PWD
DEPENDPATH *= $$PWD

HEADERS += \
    $$PWD/qxutil/qxcommon.h \
    $$PWD/qxutil/qxfs.h \
    $$PWD/qxutil/qxtime.h \
    $$PWD/qxutil/qxstring.h
SOURCES += \
    $$PWD/qxutil/qxcommon.cpp \
    $$PWD/qxutil/qxfs.cpp \
    $$PWD/qxutil/qxtime.cpp \
    $$PWD/qxutil/qxstring.cpp
