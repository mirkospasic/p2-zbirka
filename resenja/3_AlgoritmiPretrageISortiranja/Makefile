CC=gcc
CFLAGS=-Wall -ansi

all: 3_01.out 3_02.out 3_03.out 3_04.out 3_05.out 3_06.out 3_07.out 3_08.out 3_09.out 3_10.out 3_12.out 3_13.out 3_14.out 3_15.out 3_16.out 3_17.out 3_18.out 3_19.out 3_20.out 3_22.out 3_23.out 3_24.out 3_25.out 3_28.out 3_31.out 3_32.out 3_33.out 3_34.out 3_35.out 3_36.out 3_37.out 3_38.out
3_01.out: 3_01.c
	$(CC) -Wall -o $@ $< -lrt
3_02.out: 3_02.c
	$(CC) $(CFLAGS) -o $@ $<
3_03.out: 3_03.c
	$(CC) $(CFLAGS) -o $@ $<
3_04.out: 3_04.c
	$(CC) $(CFLAGS) -o $@ $<
3_05.out: 3_05.c
	$(CC) $(CFLAGS) -o $@ $< -lm
3_06.out: 3_06.c
	$(CC) $(CFLAGS) -o $@ $< -lm
3_07.out: 3_07.c
	$(CC) $(CFLAGS) -o $@ $< -lm
3_08.out: 3_08.c
	$(CC) $(CFLAGS) -o $@ $<
3_09.out: 3_09.c
	$(CC) $(CFLAGS) -o $@ $<
3_10.out: 3_10.c
	$(CC) $(CFLAGS) -o $@ $<
3_12.out: 3_12.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/sortiranje/sort.c -I ../biblioteke/sortiranje
3_13.out: 3_13.c
	$(CC) $(CFLAGS) -o $@ $<
3_14.out: 3_14.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/sortiranje/sort.c -I ../biblioteke/sortiranje
3_15.out: 3_15.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/sortiranje/sort.c -I ../biblioteke/sortiranje
3_16.out: 3_16.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/sortiranje/sort.c -I ../biblioteke/sortiranje
3_17.out: 3_17.c
	$(CC) $(CFLAGS) -o $@ $<
3_18.out: 3_18.c
	$(CC) $(CFLAGS) -o $@ $<
3_19.out: 3_19.c
	$(CC) $(CFLAGS) -o $@ $< -lm
3_20.out: 3_20.c
	$(CC) $(CFLAGS) -o $@ $<
3_22.out: 3_22.c
	$(CC) $(CFLAGS) -o $@ $<
3_23.out: 3_23.c
	$(CC) $(CFLAGS) -o $@ $<
3_24.out: 3_24.c
	$(CC) $(CFLAGS) -o $@ $<
3_25.out: 3_25.c
	$(CC) $(CFLAGS) -o $@ $<
3_28.out: 3_28.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/matrica/matrica.c -I ../biblioteke/matrica
3_31.out: 3_31.c
	$(CC) $(CFLAGS) -o $@ $<
3_32.out: 3_32.c
	$(CC) $(CFLAGS) -o $@ $< -lm
3_33.out: 3_33.c
	$(CC) $(CFLAGS) -o $@ $<
3_34.out: 3_34.c
	$(CC) $(CFLAGS) -o $@ $<
3_35.out: 3_35.c
	$(CC) $(CFLAGS) -o $@ $<
3_36.out: 3_36.c
	$(CC) $(CFLAGS) -o $@ $<
3_37.out: 3_37.c
	$(CC) $(CFLAGS) -o $@ $<
3_38.out: 3_38.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean beauty

clean:
	rm -rf *~ *.out ../biblioteke/sortiranje/*~ ../biblioteke/matrica/*~

beauty:
	indent -fc1 -fca -kr --no-tabs --line-length68 -i2 *.c ../biblioteke/sortiranje/*.[ch] ../biblioteke/matrica/*.[ch]
