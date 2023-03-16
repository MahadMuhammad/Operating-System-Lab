
# Creating a Makefile

# Compiler

CC = gcc

# Compiler flags

# CFLAGS = -Wall

# Linker flags

# LDFLAGS = -lm


# creating handler.out from handler.c

main: handler.out calculator.out # make_fifo.out

handler.out: handler.c
	$(CC) $^ -o  $@ $(CFLAGS) $(LDFLAGS)

# creating calculator.out from calculator.c

calculator.out: calculator.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

# creating make_fifo.out from make_fifo.c

make_fifo.out: make_fifo.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.out

