# Makefile
CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c
OUT = shell

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
