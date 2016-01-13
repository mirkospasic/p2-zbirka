#include <stdio.h>

/* Funkcija koja broji bitove postavljene na 1. */
int prebroj(int x)
{
  /* Izlaz iz rekurzije */
  if (x == 0)
    return 0;

  /* Ukoliko vrednost promenljive x nije 0, neki od bitova broja x je 
     postavljen na 1. Koriscenjem odgovarajuce maske proverava se
     vrednost bita na poziciji najvece tezine i na osnovu toga se 
	 razlikuju dva slucaja. Ukoliko je na toj poziciji nula, onda je 
	 broj jedinica u zapisu x isti kao broj jedinica u zapisu broja 
	 x<<1, jer se pomeranjem u levo sa desne stane dopisuju 0. Ako je
	 na poziciji najvece tezine jedinica, rezultat dobijen 
	 rekurzivnim pozivom funkcije za x<<1 treba uvecati za jedan.
     Za rekurzivni poziv se salje vrednost koja se dobija kada se x
     pomeri u levo. Napomena: argument funkcije x je oznacen ceo
     broj, usled cega se ne koristi pomeranje udesno, jer funkciji
     moze biti prosledjen i negativan broj. Iz tog razloga,
     odlucujemo se da proveramo najvisi, umesto najnizeg bita */
  if (x & (1 << (sizeof(x) * 8 - 1)))
    return 1 + prebroj(x << 1);
  else
    return prebroj(x << 1);
  /******************************************************************
    Krace zapisano
    return ((x& (1<<(sizeof(x)*8-1))) ? 1 : 0) + prebroj(x<<1);
  ******************************************************************/
}

int main()
{
  int x;

  /* Ucitava se ceo broj */
  scanf("%x", &x);

  /* Ispisuje se rezultat */
  printf("%d\n", prebroj(x));

  return 0;
}
