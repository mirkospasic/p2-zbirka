#include <stdio.h>
#include <stdlib.h>

/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x
   kreiranjem odgovarajuce maske i njenim pomeranjem */
int prebroj_bitove_1(int x)
{
  int br = 0;
  unsigned broj_pomeranja = sizeof(unsigned) * 8 - 1;

  /* Formiranje se maska cija binarna reprezentacija izgleda
     100000...0000000, koja sluzi za ocitavanje bita najvece tezine.
     U svakoj iteraciji maska se pomera u desno za 1 mesto, i
     ocitava se sledeci bit. Petlja se zavrsava kada vise nema
     jedinica tj. kada maska postane nula. */
  unsigned maska = 1 << broj_pomeranja;
  for (; maska != 0; maska >>= 1)
    x & maska ? br++ : 1;

  return br;
}

/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x
   formiranjem odgovarajuce maske i pomeranjem promenljive x */
int prebroj_bitove_2(int x)
{
  int br = 0;
  unsigned broj_pomeranja = sizeof(int) * 8 - 1;

  /* Kako je argument funkcije oznacen ceo broj x naredba x>>=1 bi
     vrsila aritmeticko pomeranje u desno, tj. popunjavanje bita
     najvece tezine bitom znaka. U tom slucaju nikad ne bi bio
     ispunjen uslov x!=0 i program bi bio zarobljen u beskonacnoj
     petlji. Zbog toga se koristi pomeranje broja x ulevo i maska
     koja ocitava bit najvece tezine. */

  unsigned maska = 1 << broj_pomeranja;
  for (; x != 0; x <<= 1)
    x & maska ? br++ : 1;

  return br;
}

int main()
{
  int x, i;

  /* Ucitava se broj sa ulaza */
  printf("Unesite broj:\n");
  scanf("%x", &x);

  /* Dozvoljava se korisniku da bira na koji nacin ce biti izracunat
     broj jedinica u zapisu broja */
  printf("Unesite redni broj funkcije:\n");
  scanf("%d", &i);

  /* Ispisuje se odgovarajuci rezultat na osnovu unesenog rednog
     broja funkcije */
  if (i == 1) {
    printf("Poziva se funkcija prebroj_bitove_1\n");
    printf("Broj jedinica u zapisu je %d\n", prebroj_bitove_1(x));
  } else if (i == 2) {
    printf("Poziva se funkcija prebroj_bitove_2\n");
    printf("Broj jedinica u zapisu je %d\n", prebroj_bitove_2(x));
  } else {
    fprintf(stderr, "Greska: Neodgovarajuci redni broj funkcije.\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
