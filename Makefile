##
# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -pedantic -L/usr/local/lib/ -I/usr/local/include/ -lcurl

##
# Directories
PREFIX = /usr/local
BUILD_DIR = ${.CURDIR}/build
SRC_DIR = src
INC_DIR = include
BIN_DIR = $(BUILD_DIR)/bin
VENDOR_DIR = vendor

##
# Files
SRC_FILES = $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c $(VENDOR_DIR)/*/src/*.c
BIN_FILE = $(BIN_DIR)/blocks

##
# Targets
build: clean $(BIN_FILE)

install: build
	@if [ -e "$(BIN_FILE)" ]; then \
		set -x; \
		install -s $(BIN_FILE) $(PREFIX)/bin/blocks; \
		install man/man8/blocks.8 $(PREFIX)/man/man8/blocks.8; \
	fi

deinstall:
	@set -x; \
	rm $(PREFIX)/bin/blocks; \
	rm $(PREFIX)/man/man8/blocks.8; \

clean:
	rm -rf $(BIN_DIR)

$(BIN_FILE):
	mkdir -p $(BIN_DIR)
	$(CC) -I$(INC_DIR) -Ivendor/isinetaddr/include $(CFLAGS) $(SRC_FILES) -o $@ $^

format:
	clang-format -style=file:.clang-format -i src/*.c src/command/*.c

.PHONY: build install clean format
