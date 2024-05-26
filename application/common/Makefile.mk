CFLAGS += -I./common
CPPFLAGS += -I./common

VPATH += ./common

# C source files
SOURCES += ./common/xprintf.c
SOURCES += ./common/utils.c
SOURCES += ./common/screen_manager.c