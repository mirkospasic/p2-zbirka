CC=gcc
CFLAGS=-Wall -ansi

all: 1_01.out 1_02.out 1_03.out 1_05.out 1_06.out 1_07.out 1_08.out 1_09.out 1_10.out 1_11.out 1_12.out 1_14.out 1_17.out 1_18.out 1_19.out 1_21.out 1_22.out 1_23.out 1_24.out 1_25.out 1_26.out 1_27.out 1_28.out 1_30.out 1_31.out 1_32.out 1_33.out 1_34.out
1_01.out: 1_01.c
	$(CC) -Wall -o $@ $< -lm
1_02.out: 1_02.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/kompleksan_broj/kompleksan_broj.c -I ../biblioteke/kompleksan_broj -lm
1_03.out: 1_03.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/polinom/polinom.c -I ../biblioteke/polinom
1_05.out: 1_05.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stampanje_bitova/stampanje_bitova.c -I ../biblioteke/stampanje_bitova
1_06.out: 1_06.c
	$(CC) $(CFLAGS) -o $@ $< 
1_07.out: 1_07.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stampanje_bitova/stampanje_bitova.c -I ../biblioteke/stampanje_bitova
1_08.out: 1_08.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stampanje_bitova/stampanje_bitova.c -I ../biblioteke/stampanje_bitova
1_09.out: 1_09.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stampanje_bitova/stampanje_bitova.c -I ../biblioteke/stampanje_bitova
1_10.out: 1_10.c
	$(CC) $(CFLAGS) -o $@ $< ../biblioteke/stampanje_bitova/stampanje_bitova.c -I ../biblioteke/stampanje_bitova
1_11.out: 1_11.c
	$(CC) $(CFLAGS) -o $@ $< 
1_12.out: 1_12.c
	$(CC) $(CFLAGS) -o $@ $< 
1_14.out: 1_14.c
	$(CC) $(CFLAGS) -o $@ $< 
1_17.out: 1_17.c
	$(CC) $(CFLAGS) -o $@ $<
1_18.out: 1_18.c
	$(CC) $(CFLAGS) -o $@ $<
1_19.out: 1_19.c
	$(CC) $(CFLAGS) -o $@ $<
1_21.out: 1_21.c
	$(CC) $(CFLAGS) -o $@ $<
1_22.out: 1_22.c
	$(CC) $(CFLAGS) -o $@ $<
1_23.out: 1_23.c
	$(CC) $(CFLAGS) -o $@ $<
1_24.out: 1_24.c
	$(CC) $(CFLAGS) -o $@ $<
1_25.out: 1_25.c
	$(CC) $(CFLAGS) -o $@ $<
1_26.out: 1_26.c
	$(CC) $(CFLAGS) -o $@ $<
1_27.out: 1_27.c
	$(CC) $(CFLAGS) -o $@ $<
1_28.out: 1_28.c
	$(CC) $(CFLAGS) -o $@ $< 
1_30.out: 1_30.c
	$(CC) $(CFLAGS) -o $@ $<
1_31.out: 1_31.c
	$(CC) $(CFLAGS) -o $@ $<
1_32.out: 1_32.c
	$(CC) $(CFLAGS) -o $@ $< 
1_33.out: 1_33.c
	$(CC) $(CFLAGS) -o $@ $<
1_34.out: 1_34.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean beauty

clean:
	rm -rf *~ *.out ../biblioteke/stampanje_bitova/*~ ../biblioteke/polinom/*~ ../biblioteke/kompleksan_broj/*~

beauty:
	indent -fc1 -fca -kr --no-tabs --line-length68 -i2 *.c ../biblioteke/stampanje_bitova/*.[ch] ../biblioteke/polinom/*.[ch] ../biblioteke/kompleksan_broj/*.[ch]
