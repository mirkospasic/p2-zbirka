CC=gcc
CFLAGS=-Wall -ansi

all: 4_01_a.out 4_01_b.out 4_01_c.out 4_02_a.out 4_02_b.out 4_02_c.out 4_03.out 4_04.out 4_06.out 4_08.out 4_09.out 4_10.out 4_11_a.out 4_11_b.out 4_11_c.out 4_14.out 4_15.out 4_16.out 4_17.out 4_18.out 4_19.out 4_20.out 4_21.out 4_22.out 4_23.out 4_25.out 4_26.out       
4_01_a.out: 401_i_402/main_a.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_iterativna/lista.c -I ../biblioteke/lista_iterativna
4_01_b.out: 401_i_402/main_b.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_iterativna/lista.c -I ../biblioteke/lista_iterativna
4_01_c.out: 401_i_402/main_c.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_iterativna/lista.c -I ../biblioteke/lista_iterativna	

4_02_a.out: 401_i_402/main_a.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_rekurzivna/lista.c -I ../biblioteke/lista_rekurzivna
4_02_b.out: 401_i_402/main_b.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_rekurzivna/lista.c -I ../biblioteke/lista_rekurzivna
4_02_c.out: 401_i_402/main_c.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_rekurzivna/lista.c -I ../biblioteke/lista_rekurzivna	

4_03.out: 4_03.c
	$(CC) $(CFLAGS) -o $@ $<
4_04.out: 4_04.c
	$(CC) $(CFLAGS) -o $@ $<	
4_06.out: 4_06.c
	$(CC) -Wall -o $@ $< ../biblioteke/lista_iterativna/lista.c -I ../biblioteke/lista_iterativna	
4_08.out: 4_08.c
	$(CC) $(CFLAGS) -o $@ $<
4_09.out: 4_09.c
	$(CC) -Wall -o $@ $< ../biblioteke/stek/stek.c -I ../biblioteke/stek		
4_10.out: 4_10.c
	$(CC) -Wall -o $@ $< ../biblioteke/red/red.c -I ../biblioteke/red
4_11_a.out: 4_11_a.c
	$(CC) -Wall -o $@ $< ../biblioteke/dvostruko_povezana_lista/dvostruko_povezana_lista.c -I ../biblioteke/dvostruko_povezana_lista	
4_11_b.out: 4_11_b.c
	$(CC) -Wall -o $@ $< ../biblioteke/dvostruko_povezana_lista/dvostruko_povezana_lista.c -I ../biblioteke/dvostruko_povezana_lista	
4_11_c.out: 4_11_c.c
	$(CC) -Wall -o $@ $< ../biblioteke/dvostruko_povezana_lista/dvostruko_povezana_lista.c -I ../biblioteke/dvostruko_povezana_lista	
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
	rm -rf *~ *.out ../biblioteke/lista_iterativna/*~ ../biblioteke/lista_rekurzivna/*~ ../biblioteke/stek/*~ ../biblioteke/red/*~ ../biblioteke/dvostruko_povezana_lista/*~ ../biblioteke/stabla/*~ 401_i_402/*~

beauty:
	indent -fc1 -fca -kr --no-tabs --line-length68 -i2 *.c ../biblioteke/lista_iterativna/*.[ch] ../biblioteke/lista_rekurzivna/*.[ch] ../biblioteke/stek/*.[ch] ../biblioteke/red/*.[ch] ../biblioteke/dvostruko_povezana_lista/*.[ch] ../biblioteke/stabla/*.[ch]  401_i_402/*.c
