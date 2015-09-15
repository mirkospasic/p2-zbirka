#include <stdio.h>

/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju 
   celog broja u memoriji. Bitove u zapisu broja treba da
   ispisujemo sa leva na desno, tj. od bita najvece tezine ka
   bitu najmanje tezine. Iz tog razloga, za pocetnu vrednost
   maske uzimamo vrednost ciji binarni zapis je takav da je bit
   najvece tezine 1, a svi ostali nule. Nakon toga, u svakoj
   iteraciji cemo tu jedinicu pomerati u desno, kako bismo
   ocitali naredni bit, gledano s leva na desno. Odgovarajuci
   karakter, ('0' ili '1'), ispisuje se na ekranu. Zbog
   siftovanja maske u desno koja na pocetku ima najvisi bit
   postavljen na 1, neophodno je da maska bude neoznacen ceo
   broj i da se siftovanjem u desno ova 1 ne bi smatrala znakom
   i prepisivala, vec da bi nam se svakim siftovanjem sa levog
   kraja binarnog zapisa pojavljivale 0. */
void print_bits(unsigned x)
{

  /* broj bitova celog broja */
  unsigned velicina = sizeof(unsigned) * 8;
  /* maska koju cemo koristiti za "ocitavanje" bitova */
  unsigned maska;

  for (maska = 1 << (velicina - 1); maska != 0; maska >>= 1)
    putchar(x & maska ? '1' : '0');

  putchar('\n');
}


int main()
{
  int broj;
  scanf("%x", &broj);
  print_bits(broj);

  return 0;
}
