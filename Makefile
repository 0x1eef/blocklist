##
# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -pedantic -lfetch

##
# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

##
# Files
SRC_FILES = $(SRC_DIR)/*.c
BIN_FILE = $(BIN_DIR)/blocklist.pf

##
# Targets
build: $(BIN_FILE)

clean:
	rm -rf $(BIN_DIR)

cat: build
	$(BIN_FILE) cat

$(BIN_FILE):
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_FILES) -I$(INC_DIR) -o $@ $^

style:
	uncrustify -c .styleguide.cfg --no-backup src/*.c

.PHONY: build clean
