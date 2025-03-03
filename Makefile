# Makefile v.1.0
PATH_SRC = src
PATH_LIB = lib
PATH_TEST = test
PATH_BUILD = build

SRC	= 	$(wildcard $(PATH_SRC)/*.c) \
		$(wildcard $(PATH_TEST)/*.c) \
		$(wildcard $(PATH_LIB)/unity/*.c)

OBJ = $(SRC:.c=.o)

TARGET = libsconio.a

TEST = test_sconio

DEP = $(OBJ:.o=.d)

CFLAGS =  -I. -I./$(PATH_LIB)/unity -I./$(PATH_SRC)
CFLAGS += -std=c99 -pedantic -Wall -Wextra -Werror

LDFLAGS = -lc

$(PATH_BUILD)/$(TEST): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY:	clean test run

all: $(TARGET)

libsconio.a:  $(OBJ)
	$(AR) -rcs $(PATH_LIB)/libsconio.a $(PATH_SRC)/sconio.o

test: $(PATH_BUILD)/$(TEST)

run: test
	$(PATH_BUILD)/$(TEST)

clean:
	rm -f $(OBJ) $(PATH_BUILD)/$(TARGET) $(PATH_BUILD)/$(TEST) $(DEP) $(PATH_LIB)/libsconio.a
