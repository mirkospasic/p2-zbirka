CC=gcc
CFLAGS=-Wall -ansi

all: 2_01.out 2_02.out 2_03.out 2_04.out 2_05.out 2_06.out 2_07.out 2_08.out 2_09.out 2_10.out 2_11.out 2_12.out 2_13.out 2_15.out 2_16.out 2_17.out 2_18.out 2_19_a.out 2_19_b.out 2_20.out 2_22.out 2_27.out 
2_01.out: 2_01.c
	$(CC) $(CFLAGS) -o $@ $< 
2_02.out: 2_02.c
	$(CC) $(CFLAGS) -o $@ $<
2_03.out: 2_03.c
	$(CC) $(CFLAGS) -o $@ $<
2_04.out: 2_04.c
	$(CC) $(CFLAGS) -o $@ $<
2_05.out: 2_05.c
	$(CC) $(CFLAGS) -o $@ $<
2_06.out: 2_06.c
	$(CC) $(CFLAGS) -o $@ $<
2_07.out: 2_07.c
	$(CC) $(CFLAGS) -o $@ $<
2_08.out: 2_08.c
	$(CC) $(CFLAGS) -o $@ $< -lm
2_09.out: 2_09.c
	$(CC) $(CFLAGS) -o $@ $<
2_10.out: 2_10.c
	$(CC) $(CFLAGS) -o $@ $<
2_11.out: 2_11.c
	$(CC) $(CFLAGS) -o $@ $<
2_12.out: 2_12.c
	$(CC) $(CFLAGS) -o $@ $< 
2_13.out: 2_13.c
	$(CC) $(CFLAGS) -o $@ $<
2_15.out: 2_15.c
	$(CC) $(CFLAGS) -o $@ $< 
2_16.out: 2_16.c
	$(CC) $(CFLAGS) -o $@ $< 
2_17.out: 2_17.c
	$(CC) $(CFLAGS) -o $@ $<
2_18.out: 2_18.c
	$(CC) $(CFLAGS) -o $@ $< -lm
2_19_a.out: 2_19/main_a.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/matrica/matrica.c -I ../biblioteke/matrica 
2_19_b.out: 2_19/main_b.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/matrica/matrica.c -I ../biblioteke/matrica
2_20.out: 2_20.c
	$(CC) $(CFLAGS) -o $@ $< -lm ../biblioteke/matrica/matrica.c -I ../biblioteke/matrica 
2_22.out: 2_22.c
	$(CC) $(CFLAGS) -o $@ $< -lm
2_27.out: 2_27.c
	$(CC) $(CFLAGS) -o $@ $< -lm

.PHONY: clean beauty

clean:
	rm -rf *~ *.out

beauty:
	indent -fc1 -fca -kr --no-tabs --line-length69 -i2 *.c ../biblioteke/matrica/*.[ch]

