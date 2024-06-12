INCLUDEPATH += $$PWD/source
SRC_DIR = $$PWD

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += kLittleEndian=1
DEFINES += kGNU=1
DEFINES += kBAR0Only=1
DEFINES += SOURCE_LIBRARY

#Check os architect: 32 bit or 64 bit, uncheck shadow build in build setting to use this feature
# linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
# linux-g++-32:QMAKE_TARGET.arch = x86
# linux-g++-64:QMAKE_TARGET.arch = x86_64

# #//Check memory by sanitize
# QMAKE_CXXFLAGS+=-fsanitize=address -fno-omit-frame-pointer
# QMAKE_CFLAGS+=-fsanitize=address -fno-omit-frame-pointer
# QMAKE_LFLAGS+=-fsanitize=address

# Architect lib
contains(QMAKE_TARGET.arch, x86) {
    unix:!macx: LIBS += -L$$PWD/../source/ -lsource
} else {
    unix:!macx: LIBS += -L$$PWD/../source/ -lsource
}
# INCLUDEPATH += $$PWD/../submodules/arch/sourcecode
# DEPENDPATH += $$PWD/../submodules/arch/sourcecode
