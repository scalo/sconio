# Makefile v.1.0
PATH_SRC = src
PATH_LIB = lib
PATH_TEST = test
PATH_BUILD = build

SRC	= 	$(wildcard $(PATH_SRC)/*.c) \
		$(wildcard $(PATH_TEST)/*.c) \
		$(wildcard $(PATH_LIB)/unity/*.c)

OBJ = $(SRC:.c=.o)

TARGET = test_sconio

DEP = $(OBJ:.o=.d)

CFLAGS =  -I. -I./$(PATH_LIB)/unity -I./$(PATH_SRC)
CFLAGS += -std=c99 -pedantic -Wall -Wextra -Werror

LDFLAGS = -lc


$(PATH_BUILD)/$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY:	clean run lib

lib:
	$(AR) -rcs $(PATH_LIB)/libsconio.a $(PATH_SRC)/sconio.o

run: $(PATH_BUILD)/$(TARGET)
	./$(PATH_BUILD)/$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(PATH_LIB)/libsconio.a
