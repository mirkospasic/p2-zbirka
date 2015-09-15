#include <stdio.h>

/* funkcija koja broji bitove svog argumenta */
/* 
   ako je x ==0, onda je count(x) = 0 inace count(x) =
   najvisi_bit +count(x<<1)

   Za svaki naredni rekurzivan poziv prosleduje se x<<1. Kako se 
   siftovanjem sa desne strane uvek dopisuju 0, argument x ce u
   nekom rekurzivnom pozivu biti bas 0 i izacicemo iz rekurzije. */

int count(int x)
{
  /* izlaz iz rekurzije */
  if (x == 0)
    return 0;

  /* Dakle, neki bit je postavljen na 1. */
  /* Proveravamo vrednost najviseg bita Kako za rekurzivni poziv 
     moramo slati siftovano x i x je oznacen ceo broj, onda ne
     smemo koristiti siftovanje desno, jer funkciji moze biti
     prosleden i negativan broj. Iz tog razloga, odlucujemo se
     da proveramo najvisi, umesto najnizeg bita */
  if (x & (1 << (sizeof(x) * 8 - 1)))
    return 1 + count(x << 1);
  /* Najvisi bit je 1. Sacekacemo da zavrsi poziv koji racuna
     koliko ima jedinica u ostatku binarnog zapisa x i potom
     uvecati taj rezultat za 1. */
  else
    /* Najvisi bit je 0. Stoga je broj jedinica u zapisu x isti
       kao broj jedinica u zapisu broja x<<1, jer se siftovanjem 
       u levo sa desne stane dopisuju 0. */
    return count(x << 1);

  /* jednolinijska return naredba sa proverom i rekurzivnim
     pozivom return ((x& (1<<(sizeof(x)*8-1))) ? 1 : 0) +
     count(x<<1); */
}

int main()
{
  int x;
  scanf("%x", &x);
  printf("%d\n", count(x));

  return 0;
}
