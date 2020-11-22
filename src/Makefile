DIRECTORY_GUARD = @mkdir -p $(@D)
BUILD_DIRECTORY = build

CC = gcc
CFLAGS = 			\
	-ansi			\
	-pedantic		\
	-Wpedantic		\
	-Wall			\
	-Wextra			\
	-Werror			\
	-g			\	# Debug flags
	-fsanitize=undefined 	\
	-fsanitize=address  	\
	-lpcap

LDFLAGS	=			\
	-fsanitize=undefined	\
	-fsanitize=address	\
	-lpcap

TARGET = ids

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(SRC))

all: TARGET

$(BUILD_DIRECTORY)/%.o: %.c
	$(DIRECTORY_GUARD)
	@echo [CC] $<
	@(CC) $(CFLAGS) -c -o $@ $<

TARGET: $(OBJ)
	$(DIRECTORY_GUARD)
	@echo [LD] $@
	@$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm $(TARGET)
	rm -r $(BUILD_DIRECTORY)

re: clean all

.PHONY: all clean re
