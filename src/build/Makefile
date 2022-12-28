CC = gcc
LIBS = -lallegro -lallegro_font -lallegro_primitives -lallegro_image -lallegro_acodec -lallegro_audio -lallegro_font -lallegro_ttf

C_FILES  = ../game.c ../sound.c ../font.c ../run.c
OBJ_FILES  = game.o sound.o font.o run.o

BIN = game.out

all: $(BIN)
	./game.out

$(BIN): $(OBJ_FILES)
	$(CC) -o $(BIN) $(OBJ_FILES) $(LIBS)

$(OBJ_FILES): $(C_FILES)
	$(CC) -c $^ 

clean:
	rm *.o game.out
