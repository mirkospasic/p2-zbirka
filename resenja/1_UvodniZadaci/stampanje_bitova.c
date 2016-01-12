#include <stdio.h>
#include <stdlib.h>
#include "stampanje_bitova.h"

void stampaj_bitove(unsigned x)
{
  /* Broj bitova celog broja */
  unsigned velicina = sizeof(unsigned) * 8;

  /* Maska koja se koristi za "ocitavanje" bitova */
  unsigned maska;

  /* Pocetna vrednost maske se postavlja na broj ciji binarni zapis
     na mestu bita najvece tezine sadrzi jedinicu, a na svim ostalim
     mestima sadrzi nulu. U svakoj iteraciji maska se menja tako sto
     se jedini bit jedinica pomera udesno, kako bi se ocitao naredni
     bit broja x koji je argument funkcije. Odgovarajuci karakter,
     ('0' ili '1'), ispisuje se na standardnom izlazu. Neophodno je
     da promenljiva maska bude deklarisana kao neoznacen ceo broj
     kako bi se pomeranjem u desno vrsilo logicko pomeranje
     (popunjavanje nulama) a ne aritmeticko pomeranje (popunjavanje
     znakom broja). */
  for (maska = 1 << (velicina - 1); maska != 0; maska >>= 1)
    putchar(x & maska ? '1' : '0');

  putchar('\n');
}