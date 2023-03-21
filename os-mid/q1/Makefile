CC = gcc
CFALGS = # = -Wall
LDFLAGS = -lm

main: start.out freqvowel.out   findsize.out reverse.out 

start.out: q1.c
	$(CC) $^ -o $@ $(CFALGS)

freqvowel.out: freqvowel.c
	$(CC) $^ -o $@ $(CFALGS)

findsize.out: findsize.c
	$(CC) $^ -o $@ $(CFALGS)

reverse.out: reverse.c
	$(CC) $^ -o $@ $(CFALGS)



clean:
	rm -rf *.out