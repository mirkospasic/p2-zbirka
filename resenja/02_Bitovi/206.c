#include <stdio.h>
#include "stampanje_bitova.h"

/* Funkcija vraca vrednost cija je binarna reprezentacija slika
   u ogledalu binarne reprezentacije broja x. */
unsigned mirror(unsigned x)
{
  unsigned najnizi_bit;
  unsigned rezultat = 0;

  int i;
  /* U svakoj iteraciji najnizi bit u binarnoj reprezentaciji tekuce
     vrednosti broja x se odredjuje i pamti u promenljivoj
     najnizi_bit, nakon cega se na promenljivu x primeni pomeranje u
     desno */
  for (i = 0; i < sizeof(x) * 8; i++) {
    najnizi_bit = x & 1;
    x >>= 1;
    /* Potiskivanjem trenutnog rezultata ka levom kraju svi prethodno 
       postavljeni bitovi dobijaju vecu poziciju. Novi bit se
       postavlja na najnizu poziciju */
    rezultat <<= 1;
    rezultat |= najnizi_bit;
  }

  /* Vraca se dobijena vrednost */
  return rezultat;
}

int main()
{
  int broj;

  /* Ucitava se broj sa ulaza */
  scanf("%x", &broj);

  /* Ispisuje se njegova binarna reprezentacija */
  print_bits(broj);

  /* Ispisuje se i binarna reprezentacija broja dobijenog pozivom
     funkcije mirror */
  print_bits(mirror(broj));

  return 0;
}
