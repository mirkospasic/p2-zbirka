#include <stdio.h>
#include "stampanje_bitova.h"

int main()
{
 int broj_int;
 short broj_short;
 char broj_char;
 
 printf("Unesite broj tipa int: ");
 /* Ucitava se broj sa ulaza */
 scanf("%x", &broj_int);

 /* I ispisuje se njegova binarna reprezentacija */
 printf("Binarna reprezentacija: ");
 stampaj_bitove(broj_int);
 
 printf("Unesite broj tipa short: ");
 /* Ucitava se broj sa ulaza */
 scanf("%hx", &broj_short);

 /* I ispisuje se njegova binarna reprezentacija */
 printf("Binarna reprezentacija: ");
 stampaj_bitove_short(broj_short);
 
 printf("Unesite broj tipa char: ");
 /* Ucitava se broj sa ulaza */
 scanf("%hhx", &broj_char);

 /* I ispisuje se njegova binarna reprezentacija */
 printf("Binarna reprezentacija: ");
 stampaj_bitove_char(broj_char);
 
 return 0;
 }
 