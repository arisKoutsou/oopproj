CC=g++
CFLAGS= -std=c++98 -ggdb
SOURCES = $(shell find -name "*.cpp")
HEADERS = $(shell find -name "*.h")

game : $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o game

.PHONY: clean

clean:
	rm -f game
