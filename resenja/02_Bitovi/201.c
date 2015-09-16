#include <stdio.h>

/* Funkcija prikazuje na standardni izlaz binarnu reprezentaciju 
   celog broja u memoriji. Bitove u zapisu broja 
   ispisujemo sa leva na desno, tj. od bita najvece tezine ka
   bitu najmanje tezine.  */
void print_bits(unsigned x)
{

  /* broj bitova celog broja */
  unsigned velicina = sizeof(unsigned) * 8;
  /* maska koja se koristi za "ocitavanje" bitova */
  unsigned maska;

  /* Pocetna vrednost maske se postavlja na broj ciji binarni 
   zapis na mestu bita najvece tezine sadrzi jedinicu, a na
   svim ostalim mestima sadrzi nulu. U svakoj iteraciji ova 
   jedinica se pomera u desno, kako bi se ocitao naredni bit. Odgovarajuci
   karakter, ('0' ili '1'), ispisuje se na standardnom izlazu. Zbog
   siftovanja maske u desno, koja na pocetku ima najvisi bit
   postavljen na 1, neophodno je da maska bude neoznacen ceo
   broj kako bi se siftovanjem u desno vrsilo logicko sifotvanje
   (popunjavanje nulama) a ne aritmeticko siftovanje (popunjavanje
   znakom broja). */
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
