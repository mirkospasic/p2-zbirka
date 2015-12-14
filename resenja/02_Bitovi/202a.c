#include <stdio.h>
#include "stampanje_bitova.h"


/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x
   pomeranjem broja x */
int count_bits(int x)
{
  int br = 0;
  unsigned wl = sizeof(unsigned) * 8 - 1;

  /* Formiramo masku 100000...0000000 koja sluzi za ocitavanje bita
     najvece tezine. U svakoj iteraciji maska se pomera u desno za
     jedno mesto, i ocitava se sledeci bit. Petlja se zavrsava kada
     vise nema jedinica u maski tj. kada maska postane nula. */
  unsigned maska = 1 << wl;
  for (; maska != 0; maska >>= 1)
    x & maska ? br++ : 1;

  return br;
}


int main()
{
  int x;

  /* Ucitava se broj sa ulaza */
  scanf("%x", &x);

  /* Ispisuje se rezultat */
  printf("Broj jedinica u zapisu je %d.\n", count_bits(x));

  return 0;
}
