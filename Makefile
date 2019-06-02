# Path
ROOT_DIR = $(shell pwd)
INC_DIR = $(ROOT_DIR)/include/
LIB_DIR = $(ROOT_DIR)/lib/
SRC_DIR = $(ROOT_DIR)/src/

export LD_LIBRARY_PATH = $(LIB_DIR)
# Command and tool
CC = gcc
RM = rm -f

# Options
BIN = sprintf strcpy_s strcat_s
CFLAGS = -I$(INC_DIR)
LDFLAGS = -L$(LIB_DIR) -lsafestring_shared

.PHONY: clean

all: $(BIN)

$(BIN):
	$(CC) $(SRC_DIR)$@.c -o $(SRC_DIR)/$@ $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(addprefix $(SRC_DIR), $(BIN))