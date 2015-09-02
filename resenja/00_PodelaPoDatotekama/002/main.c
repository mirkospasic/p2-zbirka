/* 
 * Koristimo korektno definisanu biblioteku kompleksnih brojeva. 
 * U zaglavlju complex.h nalazi se definicija komplesnog broja i popis deklaracija podrzanih funkcija
 * a u complex.c se nalaze njihove definicije.
 * 
 * Ovde pisemo i main() funkciju drugaciju od prethodnog zadatka. 
 * 
 * I dalje kompilacija programa se najjednostavnije postize naredbom
 * gcc -Wall -lm -o izvrsni complex.c main.c 
 
 Kompilaciju mozemo uraditi i na sledeci nacin:
gcc -Wall -c -o complex.o complex.c
gcc -Wall -c -o main.o main.c
gcc -lm -o complex complex.o main.o

Objasnjenje naredbi
gcc -Wall -c -o complex.o complex.c
Poziva prevodilac za kod compex.c sa opcijama:

 –Wall (stampaj upozorenja prevodioca),
 -lm (za linkovanje sa math.h bibiliotekom),
 -o (fajl koji prevodilac generiSe imenuj sa complex.o)
 -c (ne vrsi prevodjenje do izvrsnog programa, vec samo
do objektnog koda).
 Rezultat ovoga je objektni fajl complex.o, koji sadrZi
program na maSinskom jeziku. Jos uvek nije izvrSni
program, jer nije uradjeno uvezivanje (linkovanje)
biblioteka koje su u njemu koriscene, i ostalih
objektnih fajlova koji se koriste sa njim.
 Druga naredba radi analogno za main.c.
 
 Ova dva objektna fajla treba ulinkovati medjusobno, i sa
objektnim kodom standardne biblioteke. To se radi trecom
naredbom. Prevodilac gcc prepoznaje da su njegovi
argumenti objektni fajlovi i da ne treba da ih prevodi, veC
samo da ih ulinkuje ispravno.
gcc -lm -o complex complex.o main.o
*/


#include <stdio.h>
/* Ukljucujemo zaglavlje neophodno za rad sa kompleksnim brojevima */
#include "complex.h"

/* U main funkciji za uneti kompleksan broj ispisujemo njegov polarni oblik */
int main() {
   KompleksanBroj z;
   
   /* Ucitavamo kompleksan broj */
   ucitaj_kompleksan_broj(&z);
  
   ispisi_kompleksan_broj(z);
   
   printf("\n");
   
   printf("Polarni oblik kompleksnog broj je %.2f *  e^i * %.2f\n",moduo(z), argument(z));
  
   return 0;
}

