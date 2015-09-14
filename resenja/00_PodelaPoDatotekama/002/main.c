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
*/


#include <stdio.h>
/* Ukljucujemo zaglavlje neophodno za rad sa kompleksnim brojevima */
#include "complex.h"

/* U main funkciji za uneti kompleksan broj ispisujemo njegov polarni oblik */
int main() {
   KompleksanBroj z;
   
   /* Ucitavamo kompleksan broj */
   ucitaj_kompleksan_broj(&z);
     
   printf("Polarni oblik kompleksnog broja je %.2f *  e^i * %.2f\n",moduo(z), argument(z));
  
   return 0;
}

