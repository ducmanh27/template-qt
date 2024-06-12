include(../defaults.pri)
include(gtest_dependency.pri)

QT += core
# QT += serialport
QT += network
TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle

CONFIG(debug, debug|release) {
    DEFINES += UNIT_TEST
}

DESTDIR = $$PWD/../../build/test/
LIBS += -L$$PWD/../../build/source -lsource

OBJECTS_DIR = $$DESTDIR/
MOC_DIR  = $$DESTDIR/
RCC_DIR = $$DESTDIR/
UI_DIR = $$DESTDIR/

#googletest
#gtest
unix:!macx: LIBS += -L$$PWD/../../submodules/googletest/lib_64/ -lgtest
unix:!macx: PRE_TARGETDEPS += $$PWD/../../submodules/googletest/lib_64/libgtest.a
#gmock
unix:!macx: LIBS += -L$$PWD/../../submodules/googletest/lib_64/ -lgmock
unix:!macx: PRE_TARGETDEPS += $$PWD/../../submodules/googletest/lib_64/libgmock.a


SOURCES += \
    main.cpp \
    tst_addnumber.cpp

HEADERS += \

