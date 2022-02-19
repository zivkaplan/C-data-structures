CC = gcc

CFLAGS = -pedantic-errors -Wall -Wextra -g
HPATH = -iquote ../singly_linked_list/

SINGLY_LIST = ../singly_linked_list/singly_linked_list.c

SOURCES = $(wildcard *.c) $(SINGLY_LIST)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test

.PHONY: all clean obj_clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $^ $(CFLAGS) $(HPATH) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(HPATH) -c $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

obj_clean:
	rm -rf $(OBJECTS)

rebuild: clean all

