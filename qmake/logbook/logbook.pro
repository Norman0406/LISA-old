include(../config.pri)

TEMPLATE = lib

CONFIG += plugin qt
QT += core gui widgets
TARGET = lisa_$$TARGET

# add internal library
LIBS += -L$$BUILD_DIR -lcore

# os specific stuff (dependencies)
win32 {
    FILES_TO_COPY += $${BUILD_DIR}$${TARGET}.dll

    # copy dependencies to bin directory
    for (FILE, FILES_TO_COPY) {
        QMAKE_POST_LINK += $${QMAKE_COPY} $$quote($${FILE}) $$quote($${BIN_DIR}) $$escape_expand(\\n\\t)
    }
}

PRECOMPILED_HEADER = ../../src/logbook/main/precompiled.h

HEADERS += \
    ../../src/logbook/database/QSOLayout.h \
    ../../src/logbook/database/QSOFieldBase.h \
    ../../src/logbook/database/QSOField.h \
    ../../src/logbook/database/QSOEntry.h \
    ../../src/logbook/database/DatabaseXML.h \
    ../../src/logbook/database/DatabaseFactory.h \
    ../../src/logbook/database/Database.h \
    ../../src/logbook/gui/WdgToolbar.h \
    ../../src/logbook/gui/WdgOptions.h \
    ../../src/logbook/gui/WdgLogEntry.h \
    ../../src/logbook/gui/WdgLogbook.h \
    ../../src/logbook/main/LogbookModule.h

SOURCES += \
    ../../src/logbook/database/QSOLayout.cpp \
    ../../src/logbook/database/QSOFieldBase.cpp \
    ../../src/logbook/database/QSOEntry.cpp \
    ../../src/logbook/database/DatabaseXML.cpp \
    ../../src/logbook/database/Database.cpp \
    ../../src/logbook/gui/WdgToolbar.cpp \
    ../../src/logbook/gui/WdgOptions.cpp \
    ../../src/logbook/gui/WdgLogEntry.cpp \
    ../../src/logbook/gui/WdgLogbook.cpp \
    ../../src/logbook/main/LogbookModule.cpp

FORMS += \
    ../../src/logbook/ui/WdgToolbar.ui \
    ../../src/logbook/ui/WdgOptions.ui \
    ../../src/logbook/ui/WdgLogEntry.ui \
    ../../src/logbook/ui/WdgLogbook.ui

RESOURCES += \
    ../../src/logbook/res/logbook.qrc

