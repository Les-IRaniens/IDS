DIRECTORY_GUARD = @mkdir -p $(@D)
BUILD_DIRECTORY = build

CC = gcc
CFLAGS = 			\
	-pedantic		\
	-Wpedantic		\
	-Wall			\
	-Wextra			\
	-Werror			\
	-g				\
	-fsanitize=undefined 	\
	-fsanitize=address  	\
	-Isrc/					\
	-Ilibeasy/				\
	-lpcap

LDFLAGS	=			\
	-fsanitize=undefined	\
	-fsanitize=address	\
	-lpcap

TARGET = ids

SRC = $(wildcard src/*.c)
OBJ = $(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(SRC))
EASYOBJ = $(wildcard libeasy/build/*/*.o)

all: $(TARGET)

$(BUILD_DIRECTORY)/%.o: %.c
	$(DIRECTORY_GUARD)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(DIRECTORY_GUARD)
	@echo [LD] $@
	@$(CC) $^ $(EASYOBJ) -o $@ $(LDFLAGS)

clean:
	rm $(TARGET)
	rm -r $(BUILD_DIRECTORY)

re: clean all

.PHONY: all clean re
