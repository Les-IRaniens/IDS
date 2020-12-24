DIRECTORY_GUARD = @mkdir -p $(@D)
BUILD_DIRECTORY = build

CC = gcc
CFLAGS = 						\
	-pedantic					\
	-Wpedantic					\
	-Wall						\
	-Wextra						\
	-Werror						\
	-g							\
	-Isrc/						\
	-lpcap						\
	-fsanitize=undefined \
	-fsanitize=address  \


LDFLAGS	=						\
	-lpcap						\
	-fsanitize=undefined \
	-fsanitize=address  \


TARGET = ids

SRC =  							\
	$(wildcard src/*.c) 		\
	$(wildcard src/utils/*.c)

OBJ = $(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(SRC))

all: $(TARGET)

$(BUILD_DIRECTORY)/%.o: %.c
	$(DIRECTORY_GUARD)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(DIRECTORY_GUARD)
	@echo [LD] $@
	@$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -r $(BUILD_DIRECTORY)
	rm $(TARGET)

re: clean all

.PHONY: all clean re
