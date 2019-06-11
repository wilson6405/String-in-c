# Path
ROOT_DIR = $(shell pwd)
INC_DIR = $(ROOT_DIR)/include/
LIB_DIR = $(ROOT_DIR)/lib/
SRC_DIR = $(ROOT_DIR)/src/
TEST_DIR = $(ROOT_DIR)/unittests/

export LD_LIBRARY_PATH = $(LIB_DIR)
# Command and tool
CC = gcc
CXX = g++
RM = rm -f

# Options
BIN = strcpy_s strcmp_s strcat_s strstr_s
MAKEFLAGS = -j4
CFLAGS = -I$(INC_DIR)
LDFLAGS = -L$(LIB_DIR) -lsafestring_shared -lpthread -lgtest_main
Q = @
ifeq ($(V), 1)
	Q = 
endif

ifeq ($(D), 1)
	LDFLAGS += -g
endif


.PHONY: clean test

all: $(BIN)

$(BIN):
	@echo "[CXX] $@"
	$(Q) $(CXX) $(SRC_DIR)$@.c /usr/local/lib/libgtest.a -o $(TEST_DIR)$@ $(CFLAGS) $(LDFLAGS)
# TODO
test:
	$(shell .$(SRC_DIR)$(BIN))

clean:
	$(RM) $(addprefix $(TEST_DIR), $(BIN))