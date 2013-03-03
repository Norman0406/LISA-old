include(../config.pri)

TEMPLATE = lib

CONFIG += plugin qt
QT += core gui widgets multimedia
TARGET = lisa_$$TARGET

# add internal library
LIBS += -L$$BUILD_DIR -lcore

# os specific stuff (dependencies)
win32 {
    LIBS += -L$$LIB_DIR/lib/ -llibfftw3-3

    CONFIG(debug, debug|release) {
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Multimediad.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Networkd.dll
    }
    else: CONFIG(release, debug|release) {
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Multimedia.dll
        FILES_TO_COPY += $$[QT_INSTALL_BINS]\Qt5Network.dll
    }

    FILES_TO_COPY += $${BUILD_DIR}$${TARGET}.dll
    FILES_TO_COPY += $${LIB_DIR}bin\\libfftw3-3.dll

    # copy dependencies to bin directory
    for (FILE, FILES_TO_COPY) {
        QMAKE_POST_LINK += $${QMAKE_COPY} $$quote($${FILE}) $$quote($${BIN_DIR}) $$escape_expand(\\n\\t)
    }
}
linux {
    LIBS += -L/usr/lib/x86_64-linux-gnu -lfftw3
}

PRECOMPILED_HEADER = ../../src/digital/main/precompiled.h

SOURCES += \
    ../../src/digital/audio/AudioSpectrum.cpp \
    ../../src/digital/audio/AudioDeviceIn.cpp \
    ../../src/digital/audio/AudioDevice.cpp \
    ../../src/digital/gui/WdgWaterfall.cpp \
    ../../src/digital/gui/WdgToolbar.cpp \
    ../../src/digital/gui/WdgOptions.cpp \
    ../../src/digital/gui/WdgDigital.cpp \
    ../../src/digital/main/DigitalModule.cpp \
    ../../src/digital/main/Colormap.cpp \
    ../../src/digital/audio/AudioSpectrumWorker.cpp \
    ../../src/digital/audio/AudioBuffer.cpp \
    ../../src/digital/main/ColormapVisitor.cpp \
    ../../src/digital/gui/WdgSidebar.cpp

HEADERS += \
    ../../src/digital/audio/AudioSpectrum.h \
    ../../src/digital/audio/AudioDeviceIn.h \
    ../../src/digital/audio/AudioDevice.h \
    ../../src/digital/gui/WdgWaterfall.h \
    ../../src/digital/gui/WdgToolbar.h \
    ../../src/digital/gui/WdgOptions.h \
    ../../src/digital/gui/WdgDigital.h \
    ../../src/digital/main/DigitalModule.h \
    ../../src/digital/main/Colormap.h \
    ../../src/digital/audio/AudioSpectrumWorker.h \
    ../../src/digital/audio/AudioBuffer.h \
    ../../src/digital/main/ColormapVisitor.h \
    ../../src/digital/gui/WdgSidebar.h

FORMS += \
    ../../src/digital/ui/WdgToolbar.ui \
    ../../src/digital/ui/WdgOptions.ui \
    ../../src/digital/ui/WdgDigital.ui \
    ../../src/digital/ui/WdgSidebar.ui

RESOURCES += \
    ../../src/digital/res/digital.qrc

