#include <stdio.h>

/* Funkcija prikazuje na standardni izlaz binarnu reprezentaciju
   celog broja u memoriji */
void print_bits(int x)
{
  unsigned velicina = sizeof(int) * 8;
  unsigned maska;

  for (maska = 1 << (velicina - 1); maska != 0; maska >>= 1)
    putchar(x & maska ? '1' : '0');

  putchar('\n');
}

/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x
   pomeranjem broja x */
int count_bits1(int x)
{
  int br = 0;
  unsigned wl = sizeof(int) * 8 - 1;

  /* Kako je argument funkcije oznacen ceo broj x naredba x>>=1
     vrsila bi aritmeticko pomeranje u desno, tj. popunjavanje bita
     najvece tezine bitom znaka. U tom slucaju nikad ne bi bio
     ispunjen uslov x!=0 i program bi bio zarobljen u beskonacnoj
     petlji. Zbog toga se koristi pomeranj broja x ulevo i maska
     koja ocitava bit najvece tezine. */

  unsigned maska = 1 << wl;
  for (; x != 0; x <<= 1)
    x & maska ? br++ : 1;

  return br;
}


int main()
{
  int x;
  scanf("%x", &x);
  printf("Broj jedinica u zapisu je %d.\n", count_bits1(x));

  return 0;
}
