/**************************************************************
Ovaj program koristi korektno definisanu biblioteku kompleksnih 
brojeva. U zaglavlju complex.h nalazi se definicija komplesnog 
broja i popis deklaracija podrzanih funkcija, a u complex.c se 
nalaze njihove definicije.

Kompilacija programa se najjednostavnije postize naredbom
gcc -Wall -lm -o izvrsni complex.c main.c 
 
Kompilacija se moze uraditi i na sledeci nacin:
gcc -Wall -c -o complex.o complex.c
gcc -Wall -c -o main.o main.c
gcc -lm -o complex complex.o main.o
**************************************************************/


#include <stdio.h>
/* Ukljucuje aw zaglavlje neophodno za rad sa kompleksnim 
   brojevima */
#include "complex.h"

/* U glavnoj funkciji se za uneti kompleksan broj ispisuje
   njegov polarni oblik */
int main() {
   KompleksanBroj z;
   
   /* Ucitavamo kompleksan broj */
   ucitaj_kompleksan_broj(&z);
     
   printf("Polarni oblik kompleksnog broja je %.2f *  e^i * %.2f\n", moduo(z), argument(z));
  
   return 0;
}

