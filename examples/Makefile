SRC = snake.c
OBJ = $(SRC:.c=.o)
PATH_BUILD = ../build
TARGET = snake

CFLAGS = -I. -I../src
CFLAGS += -std=c99 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lc -L../lib/ -lsconio

$(PATH_BUILD)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean run

all: $(TARGET)

lib:
	$(MAKE) -C ../  lib/libsconio.a

run:
	$(PATH_BUILD)/$(TARGET)

clean:
	$(MAKE) -C ../  clean
	rm -f $(OBJ) $(PATH_BUILD)/$(TARGET)
