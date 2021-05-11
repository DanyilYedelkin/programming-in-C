CC=gcc
CFLAGS=-std=c11 -Wall
LDLIBS=-lm
OUTPUT=game

all: $(OUTPUT)

$(OUTPUT): backpack.o command.o container.o item.o parser.o room.o world.o game.o main.o
	$(CC) $(CFLAGS) backpack.o command.o container.o item.o parser.o room.o world.o game.o main.o $(LDLIBS) -o $(OUTPUT)

backpack.o: backpack.c backpack.h
	$(CC) $(CFLAGS) -c backpack.c $(LDLIBS) -o backpack.o

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c $(LDLIBS) -o command.o

container.o: container.c container.h
	$(CC) $(CFLAGS) -c container.c $(LDLIBS) -o container.o

item.o: item.c item.h
	$(CC) $(CFLAGS) -c item.c $(LDLIBS) -o item.o

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c $(LDLIBS) -o parser.o

room.o: room.c room.h
	$(CC) $(CFLAGS) -c room.c $(LDLIBS) -o room.o

world.o: world.c world.h
	$(CC) $(CFLAGS) -c world.c $(LDLIBS) -o world.o

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c $(LDLIBS) -o game.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

clean:
	rm -rf $(OUTPUT) *.o
