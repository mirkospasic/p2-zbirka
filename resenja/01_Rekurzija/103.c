#include <stdio.h>

/*************************************************************
   Funkcija koja broji bitove svog argumenta

   ako je x ==0, onda je count(x) = 0 
   inace count(x) = najvisi_bit +count(x<<1)

   Za svaki naredni rekurzivan poziv prosleduje se x<<1. Kako se 
   pomeranjem sa desne strane uvek dopisuju 0, argument x ce u
   nekom rekurzivnom pozivu biti bas 0 i izacice se iz rekurzije. 
*************************************************************/
int count(int x)
{
  /* Izlaz iz rekurzije */
  if (x == 0)
    return 0;

  /* Ukoliko vrednost promenljive x nije 0, neki od bitova broja x je 
     postavljen na 1. Koriscenjem odgovarajuce maske proverava se
     vrednost najviseg bita. Rezultat koliko ima jedinica u ostatku
     binarnog zapisa broja x se uvecava za 1. Najvisi bit je 0. Stoga 
     je broj jedinica u zapisu x isti kao broj jedinica u zapisu
     broja x<<1, jer se pomeranjem u levo sa desne stane dopisuju 0.
     Za rekurzivni poziv se salje vrednost koja se dobija kada se x
     pomeri u levo. Napomena: argument funkcije x je oznacen ceo
     broj, usled cega se ne koristi pomeranje udesno, jer funkciji
     moze biti prosledjen i negativan broj. Iz tog razloga,
     odlucujemo se da proveramo najvisi, umesto najnizeg bita */
  if (x & (1 << (sizeof(x) * 8 - 1)))
    return 1 + count(x << 1);
  else
    return count(x << 1);
  /******************************************************************
    Krace napisano
    return ((x& (1<<(sizeof(x)*8-1))) ? 1 : 0) + count(x<<1);
  ******************************************************************/
}

int main()
{
  int x;

  /* Ucitava se ceo broj */
  scanf("%x", &x);

  /* Ispisuje se rezultat */
  printf("%d\n", count(x));

  return 0;
}
