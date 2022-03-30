CC = gcc
LD = gcc

CFLAGS = -pedantic-errors -Wall -Wextra -g

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = executable

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

obj_clean:
	rm -rf *.o

rebuild: clean all obj_clean

.PHONY : clean obj_clean
