#include <stdio.h>
#include "stampanje_bitova.h"

int main()
{
  int broj_int;
  short broj_short;
  char broj_char;

  /* Ucitavanje broja tipa int */
  printf("Unesite broj tipa int: ");
  scanf("%x", &broj_int);

  /* Ispisivanje binarne reprezentacije unetog broja */
  printf("Binarna reprezentacija: ");
  stampaj_bitove(broj_int);

  /* Ucitavanje broja tipa short */
  printf("Unesite broj tipa short: ");
  scanf("%hx", &broj_short);

  /* Ispisivanje binarne reprezentacije unetog broja */
  printf("Binarna reprezentacija: ");
  stampaj_bitove_short(broj_short);

  /* Ucitavanje broja tipa char */
  printf("Unesite broj tipa char: ");
  scanf("%hhx", &broj_char);

  /* Ispisivanje binarne reprezentacije unetog broja */
  printf("Binarna reprezentacija: ");
  stampaj_bitove_char(broj_char);

  return 0;
}
