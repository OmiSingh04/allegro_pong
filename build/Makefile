CC = gcc
SRC = "../src/"

CFLAGS = -Wall -Wextra 

C_FILES = game.c sound.c run.c
OBJECT_FILES = game.o sound.o run.o

LIBRARIES = -lallegro -lallegro-primitives -lallegro-audio -lallegro-acodec

BINARY = pong

all: $(BINARY)

$(BINARY): $(OBJECT_FILES)
	$(CC) -o $@ $^ $(LIBRARIES)

%.o: %.c
	$(CC) $(CFLAGS) -c $(SRC)$^ -o $@

clean:
	rm $(BINARY) *.o
