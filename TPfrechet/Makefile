all:
	clang bin/frechet.c -lm -Wall -Wextra -std=c99 -g -o bin/frechet
clean:
	rm -f *.o *~ frechet *.out

# CC = clang
# LDFLAGS = -lm
# CFLAGS = -std=c99 -Wall -Wextra -g
#
# all: frechet
#
# frechet: frechet.o
# 	$(CC) $(LDFLAGS) -o $@ $^
#
# %.o: %.c
# 	$(CC) $(CFLAGS) -c -o $@ $<
#
# clean:
# 	rm -f *.o *~ frechet
