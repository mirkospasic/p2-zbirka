CC=gcc
CFLAGS=-Wall -ansi

all: A_01.out A_02.out A_03.out A_04.out A_05.out A_06.out A_07.out A_08.out A_09.out A_10.out A_11.out A_12.out 
A_01.out: A_01.c
	$(CC) -Wall -o $@ $< 
A_02.out: A_02.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
A_03.out: A_03.c
	$(CC) $(CFLAGS) -o $@ $< 
A_04.out: A_04.c
	$(CC) $(CFLAGS) -o $@ $< 
A_05.out: A_05.c
	$(CC) $(CFLAGS) -o $@ $< -lm
A_06.out: A_06.c
	$(CC) $(CFLAGS) -o $@ $<  ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
A_07.out: A_07.c
	$(CC) $(CFLAGS) -o $@ $< 
A_08.out: A_08/main.c
	$(CC) $(CFLAGS) -o $@ $< A_08/liste.c -I A_08
A_09.out: A_09.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/matrica/matrica.c -I ../biblioteke/matrica
A_10.out: A_10.c
	$(CC) $(CFLAGS) -o $@ $< 
A_11.out: A_11.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
A_12.out: A_12.c
	$(CC) $(CFLAGS) -o $@ $< 


.PHONY: clean beauty

clean:
	rm -rf *~ *.out ../biblioteke/stabla/*~ A_08/*~ ../biblioteke/matrica/*~ 

beauty:
	indent -fc1 -fca -kr --no-tabs --line-length68 -i2 *.c ../biblioteke/stabla/*.[ch] A_08/*.[ch] ../biblioteke/matrica/*.[ch] 
