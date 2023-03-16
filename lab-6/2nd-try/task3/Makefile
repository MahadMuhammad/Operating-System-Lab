
# Creating a Makefile

# Compiler

CC = gcc

# Compiler flags

# CFLAGS = -Wstringop-overflow

# Linker flags

# LDFLAGS = -lm


# creating sender.out from sender.c

main: sender.out reciever.out # make_fifo.out

sender.out: sender.c
	$(CC) $^ -o  $@ $(CFLAGS) $(LDFLAGS)

# creating reciever.out from reciever.c

reciever.out: reciever.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

# creating make_fifo.out from make_fifo.c

make_fifo.out: make_fifo.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.out

