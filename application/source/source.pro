QT       -= gui
# QT += serialport
QT += core network

CONFIG += c++14 console
CONFIG+=resources_big

TARGET = source
TEMPLATE = lib

@QMAKE_LFLAGS+= -static-libstdc++@

# --coverage option is synonym for: -fprofile-arcs -ftest-coverage -lgcov
CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += --coverage
    QMAKE_LFLAGS += --coverage
    # QMAKE_POST_LINK = rm -f "*.gcda"
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#This script part is to execute your shell script before build project
CONFIG(release, debug|release) {
#    extralib.target = extra
#    extralib.commands = bash $$PWD/create_version.sh; # Run your programs here
#    extralib.depends =
#    QMAKE_EXTRA_TARGETS += extralib
#    PRE_TARGETDEPS = extra
}

DESTDIR = $$PWD/../../build/source/
OBJECTS_DIR = $$DESTDIR/
MOC_DIR  = $$DESTDIR/
RCC_DIR = $$DESTDIR/
UI_DIR = $$DESTDIR/

include(../defaults.pri)

HEADERS += \
    manager/AppManager.h \


SOURCES += \
    manager/AppManager.cpp \

