##Penser a changer un peu le makefile c'est celui de lecture_fichier

CC = clang
LDFLAGS = -lm
CFLAGS = -std=c99 -Wall -Wextra -g

all: frechet

frechet: frechet.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o *~ frechet
