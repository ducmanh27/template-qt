include(../defaults.pri)

TEMPLATE = app
QT -= gui
CONFIG += c++14 console
CONFIG -= app_bundle
CONFIG+=resources_big

DESTDIR = $$PWD/../../build/app/
LIBS += -L$$OUT_PWD/../../build/source/ -lsource
OBJECTS_DIR = $$DESTDIR/
MOC_DIR  = $$DESTDIR/
RCC_DIR = $$DESTDIR/
UI_DIR = $$DESTDIR/

SOURCES += \
        main.cpp
