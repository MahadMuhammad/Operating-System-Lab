# Muhammad Mahad 21L-6195
# Make file for q3

CC = g++
CFLAGS = -Wall -g

q3.out: q3.cpp
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.out

# creating 5 files
create_files:
	touch Unsorted.txt
	touch Unsorted_00.txt
	touch Unsorted_01.txt
	touch Unsorted_02.txt
	touch Unsorted_03.txt
	touch Unsorted_04.txt
	touch Sorted.txt
	touch merge.txt
	touch selection.txt
	touch insertion.txt
	touch quick.txt

clean_files:
	rm -f *.txt

ca:
	rm -f *.out
	rm -f *.txt
