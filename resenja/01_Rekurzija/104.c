#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* NAPOMENA: Ovaj problem je iskoriscen da ilustruje 
  uzajamnu (posrednu) rekurziju.
 */

/* Deklaracija funkcije neparan mora da bude navedena 
  jer se ta funkcija koristi u telu funkcije paran,
  tj. koristi se pre svoje definicije.
  Funkcija je mogla biti deklarisana i u telu funkcije paran.
 */

unsigned neparan(unsigned n);

 /* Funckija vraca 1 ako broj n ima paran broj cifara inace vraca 0. */
unsigned paran(unsigned n) {
    if(n>=0 && n<=9) 
        return 0;
    else 
        return neparan(n/10);
}

 /* Funckija vraca 1 ako broj n ima neparan broj cifara inace vraca 0. */
unsigned neparan(unsigned n) {
    if(n>=0 && n<=9) 
        return 1;
    else 
        return paran(n/10);
}

/* Glavna funkcija za testiranje */
int main( ) {
    int n;    
    scanf("%d", &n);        
    printf("Uneti broj ima %sparan broj cifara\n", (paran(n) == 1 ? "": "ne"));  
    return 0;
}
