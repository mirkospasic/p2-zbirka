CC=gcc
CFLAGS=-Wall -ansi

all: 4_14.out 4_15.out 4_16.out 4_17.out 4_18.out 4_19.out 4_20.out 4_21.out 4_22.out 4_23.out 4_25.out 4_26.out 
4_14.out: 4_14.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_15.out: 4_15.c
	$(CC) $(CFLAGS) -o $@ $<
4_16.out: 4_16.c
	$(CC) $(CFLAGS) -o $@ $<
4_17.out: 4_17.c
	$(CC) $(CFLAGS) -o $@ $< 
4_18.out: 4_18.c
	$(CC) $(CFLAGS) -o $@ $< 
4_19.out: 4_19.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_20.out: 4_20.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_21.out: 4_21.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_22.out: 4_22.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_23.out: 4_23.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_25.out: 4_25.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla
4_26.out: 4_26.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stabla/stabla.c -I ../biblioteke/stabla

.PHONY: clean beauty

clean:
	rm -rf *~ *.out

beauty:
	indent -fc1 -fca -kr --no-tabs --line-length70 -i2 *.c ../biblioteke/stabla/*.[ch]
