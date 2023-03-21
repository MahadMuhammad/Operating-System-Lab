CC = gcc
CFALGS = # = -Wall
LDFLAGS = -lm

main: pipesquestion.out

pipesquestion.out: pipesquestion.c
	$(CC) $^ -o $@ $(CFALGS)




clean:
	rm -rf *.out myfifo1 myfifo2 myfifo 