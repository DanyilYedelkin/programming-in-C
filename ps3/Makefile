CFLAGS=-std=c11 -Werror -Wall -Wconversion
OUTPUT=ps3

all: $(OUTPUT)

ps3: hof.o k.o ui.o main.o
		gcc $(CFLAGS) -lm hof.o k.o ui.o main.o -o ps3

main.o: main.c
		gcc $(CFLAGS) -lm -c main.c -o main.o	

hof.o: hof.c hof.h
		gcc $(CFLAGS) -lm -c hof.c -o hof.o	

k.o: k.c k.h
		gcc $(CFLAGS) -lm -c k.c -o k.o

ui.o: ui.c ui.h
		gcc $(CFLAGS) -lm -c ui.c -o ui.o		

clean:
		rm -rf $(OUTPUT) *.o
