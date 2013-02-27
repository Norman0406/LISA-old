include(../config.pri)

TEMPLATE = lib

CONFIG += staticlib qt
QT += gui

# os specific stuff (dependencies)
win32 {
    CONFIG(debug, debug|release) {
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Widgetsd.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Guid.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Cored.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\libGLESv2d.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\libEGLd.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\icudt49.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\icuin49.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\icuuc49.dll
    }
    else: CONFIG(release, debug|release) {
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Widgets.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Gui.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Core.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\libGLESv2.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\libEGL.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\icudt49.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\icuin49.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\icuuc49.dll
    }

    # copy dependencies to bin directory
    for (file, FILES_TO_COPY) {
        QMAKE_POST_LINK += $${QMAKE_COPY} $$quote($${file}) $$quote($${BIN_DIR}) $$escape_expand(\\n\\t)
    }
}

PRECOMPILED_HEADER = ../../src/core/main/precompiled.h

SOURCES += \
    ../../src/core/common/Logging.cpp \
    ../../src/core/common/FileUtils.cpp \
    ../../src/core/common/Exception.cpp \
    ../../src/core/main/PropertyList.cpp \
    ../../src/core/main/PropertyBase.cpp \
    ../../src/core/main/OptionsBase.cpp \
    ../../src/core/main/Module.cpp

HEADERS += \
    ../../src/core/common/Logging.h \
    ../../src/core/common/FileUtils.h \
    ../../src/core/common/Factory.h \
    ../../src/core/common/Exception.h \
    ../../src/core/main/PropertyTraits.h \
    ../../src/core/main/PropertyList.h \
    ../../src/core/main/PropertyBase.h \
    ../../src/core/main/Property.h \
    ../../src/core/main/OptionsBase.h \
    ../../src/core/main/ModuleBase.h \
    ../../src/core/main/Module.h
