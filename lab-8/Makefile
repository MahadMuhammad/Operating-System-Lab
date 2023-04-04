CC = gcc
# CFLAGS = -Wall
# LDFLAGS = -lm

all: main

main: q1.out q2.out

tutorial: dupone.out duptwo.out dupthree.out dupfour.out dupfive.out

dupone.out: dupone.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

duptwo.out: duptwo.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

dupthree.out: dupthree.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

dupfour.out: dupfour.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

dupfive.out: dupfive.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

q1.out: q1.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

q2.out: q2.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

q3.out: q3.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


clean:
	rm -f *.out
