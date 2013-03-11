include(../config.pri)

TEMPLATE = app

CONFIG += qt
QT += core gui widgets
TARGET = LISA

LIBS += -L$$BUILD_DIR -lcore

# os specific stuff (dependencies)
win32 {
    FILES_TO_COPY += $${BUILD_DIR}$${TARGET}.exe

    # copy dependencies to bin directory
    for (FILE, FILES_TO_COPY) {
        QMAKE_POST_LINK += $${QMAKE_COPY} $$quote($${FILE}) $$quote($${BIN_DIR}) $$escape_expand(\\n\\t)
    }
}

PRECOMPILED_HEADER = ../../src/application/main/precompiled.h

FORMS += \
    ../../src/application/ui/WdgOptions.ui \
    ../../src/application/ui/WdgLogging.ui \
    ../../src/application/ui/MainWindow.ui \
    ../../src/application/ui/DlgOptions.ui \
    ../../src/application/ui/DlgAbout.ui

SOURCES += \
    ../../src/application/main/main.cpp \
    ../../src/application/gui/WdgOptions.cpp \
    ../../src/application/gui/WdgLogging.cpp \
    ../../src/application/gui/MainWindow.cpp \
    ../../src/application/gui/DlgOptions.cpp \
    ../../src/application/gui/DlgAbout.cpp

HEADERS += \
    ../../src/application/gui/WdgOptions.h \
    ../../src/application/gui/WdgLogging.h \
    ../../src/application/gui/MainWindow.h \
    ../../src/application/gui/DlgOptions.h \
    ../../src/application/gui/DlgAbout.h

RESOURCES += \
    ../../src/application/res/LISA.qrc
