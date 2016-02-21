#include <stdio.h>
#include "stampanje_bitova.h"

/* Funkcija vraca vrednost cija je binarna reprezentacija slika u
   ogledalu binarne reprezentacije broja x. */
unsigned ogledalo(unsigned x)
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
    /* Potiskivanjem trenutnog rezultata ka levom kraju svi
       prethodno postavljeni bitovi dobijaju vecu poziciju. Novi bit 
       se postavlja na najnizu poziciju */
    rezultat <<= 1;
    rezultat |= najnizi_bit;
  }

  /* Vraca se izracunata vrednost */
  return rezultat;
}

int main()
{
  int broj;

  /* Ucitava se broj sa ulaza */
  scanf("%x", &broj);

  /* Ispisuje se njegova binarna reprezentacija */
  stampaj_bitove(broj);

  /* Ispisuje se i binarna reprezentacija broja izracunatog pozivom
     funkcije ogledalo */
  stampaj_bitove(ogledalo(broj));

  return 0;
}
