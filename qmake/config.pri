# important directories relative to the .pro file from which it is being included
BIN_DIR = $$_PRO_FILE_PWD_/../../bin/
LIB_DIR = $$_PRO_FILE_PWD_/../../lib/
SRC_DIR = $$_PRO_FILE_PWD_/../../src/

INCLUDEPATH += $$LIB_DIR/include/
DEPENDPATH += $$LIB_DIR/include/

# set build directory
CONFIG(debug, debug|release) {
    BUILD_DIR = $$_PRO_FILE_PWD_/../../build/debug/
}
else {
    BUILD_DIR = $$_PRO_FILE_PWD_/../../build/release/
}

# assign build directory
DESTDIR = $$BUILD_DIR

# set additional include directory
INCLUDEPATH *= $${SRC_DIR}

# replace directory separators for windows
win32 {
    BIN_DIR ~= s,/,\\,g
    LIB_DIR ~= s,/,\\,g
    BUILD_DIR ~= s,/,\\,g
}
