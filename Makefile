CC = gcc
CFLAGS = -Wall -Iinclude

MYSQL_FLAGS := $(shell mysql_config --cflags --libs)
GTK_FLAGS := $(shell pkg-config --cflags --libs gtk+-3.0)

SRC = src/main.c src/ui.c src/auth.c src/config.c
OUT = gtk_login

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS) $(MYSQL_FLAGS) $(GTK_FLAGS)

clean:
	rm -f $(OUT)
