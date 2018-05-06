include(../qxgui.pri)
include(../qxsys.pri)
include(../qxutil.pri)

QT += core gui
CONFIG += silent
TEMPLATE = app
TARGET = qtaux

SOURCES += \
    main.cpp \
    test.cpp
HEADERS += \
    test.h

# Output
MOC_DIR = out/mocs
OBJECTS_DIR = out/obj
RCC_DIR = out/rcc
UI_DIR = out/ui
