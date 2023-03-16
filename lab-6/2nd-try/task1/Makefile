
# Creating a Makefile

# Compiler

CC = gcc

# Compiler flags

# CFLAGS = -Wall

# Linker flags

# LDFLAGS = -lm


# creating handler.out from handler.c

main: handler.out case_changer.out # make_fifo.out

handler.out: handler.c
	$(CC) $^ -o  $@ $(CFLAGS) $(LDFLAGS)

# creating case_changer.out from case_changer.c

case_changer.out: case_changer.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

# creating make_fifo.out from make_fifo.c

make_fifo.out: make_fifo.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.out

