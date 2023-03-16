# compiler
CC = gcc
# compiler flags
CFLAGS = -Wall 

# the build target executable:
TARGET = main

all: $(TARGET)

$(TARGET): sender.out worker.out make_fifo.out

sender.out: sender.c
	$(CC)   -o sender.out sender.c

worker.out: worker.c
	$(CC)   -o worker.out worker.c

make_fifo.out: make_fifo.c
	$(CC)   -o make_fifo.out make_fifo.c

clean:
	rm -rf *.out myfifo