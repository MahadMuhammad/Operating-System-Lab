CC = gcc
CFALGS = # = -Wall
LDFLAGS = -lm

main: makepipe.out  receiver.out   sender.out

makepipe.out: makepipe.c
	$(CC) $^ -o $@ $(CFALGS)

receiver.out: receiver.c
	$(CC) $^ -o $@ $(CFALGS)

sender.out: sender.c
	$(CC) $^ -o $@ $(CFALGS)

clean:
	rm -rf *.out sender story_pipe
