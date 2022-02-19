CC = gcc

CFLAGS = -pedantic-errors -Wall -Wextra -g

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test

.PHONY: all clean obj_clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

obj_clean:
	rm -rf $(OBJECTS)

rebuild: clean all

