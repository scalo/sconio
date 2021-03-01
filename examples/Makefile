src = snake.c
obj = $(src:.c=.o)

CFLAGS = -I. -I../src
CFLAGS += -std=c99 -pedantic -Wall -Wextra -Werror
LDFLAGS = -lc -L../lib/ -lsconio

snake: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) snake