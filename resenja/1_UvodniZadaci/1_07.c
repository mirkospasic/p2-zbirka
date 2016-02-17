#include <stdio.h>
#include "stampanje_bitova.h"

/* Funkcija vraca najveci neoznaceni broj sastavljen od istih bitova
   koji se nalaze u binarnoj reprezentaciji vrednosti promenjive x */
unsigned najveci(unsigned x)
{
  unsigned velicina = sizeof(unsigned) * 8;

  /* Formira se maska 100000...0000000 */
  unsigned maska = 1 << (velicina - 1);

  /* Rezultat se inicijalizuje vrednoscu 0 */
  unsigned rezultat = 0;

  /* Promenljiva x se pomera u levo sve dok postoje jedinice u
     njenoj binarnoj reprezentaciji (tj. sve dok je promenljiva x
     razlicita od nule). */
  for (; x != 0; x <<= 1) {
    /* Za svaku jedinicu koja se koriscenjem maske detektuje na
       poziciji najvece tezine u binarnoj reprezentaciji promenjive
       x, potiskuje se jedna nova jedinicu sa leva u rezultat */
    if (x & maska) {
      rezultat >>= 1;
      rezultat |= maska;
    }
  }

  /* Vraca se dobijena vrednost */
  return rezultat;
}

/* Funkcija vraca najmanji neoznaceni broj sastavljen od istih
   bitova koji se nalaze u binarnoj reprezentaciji vrednosti
   promenjive x */
unsigned najmanji(unsigned x)
{
  /* Rezultat se inicijalizuje vrednoscu 0 */
  unsigned rezultat = 0;

  /* Promenljiva x se pomera u desno sve dok postoje jedinice u
     njenoj binarnoj reprezentaciji (tj. sve dok je promenljiva x
     razlicita od nule). */
  for (; x != 0; x >>= 1) {
    /* Za svaku jedinicu koja se koriscenjem vrednosti 1 za masku
       detektuje na poziciji najmanje tezine u binarnoj
       reprezentaciji promenjive x, potiskuje se jedna nova jedinicu
       sa desna u rezultat */
    if (x & 1) {
      rezultat <<= 1;
      rezultat |= 1;
    }
  }

  /* Vraca se dobijena vrednost */
  return rezultat;
}

int main()
{
  int broj;

  /* Ucitava se broj sa ulaza */
  scanf("%x", &broj);

  /* Ispisuju se, redom, najveci i najmanji broj formirani od bitova
     unetog broja */
  printf("Najveci:\n");
  stampaj_bitove(najveci(broj));

  printf("Najmanji:\n");
  stampaj_bitove(najmanji(broj));

  return 0;
}
