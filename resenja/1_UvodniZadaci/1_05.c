#include <stdio.h>
#include "stampanje_bitova.h"

int main()
{
  int broj_int;
  short broj_short;
  char broj_char;

  /* Ucitava se broj tipa int */
  printf("Unesite broj tipa int: ");
  scanf("%x", &broj_int);

  /* Ispisuje se binarna reprezentacija unetog broja */
  printf("Binarna reprezentacija: ");
  stampaj_bitove(broj_int);

  /* Ucitava se broj tipa short */
  printf("Unesite broj tipa short: ");
  scanf("%hx", &broj_short);

  /* Ispisuje se binarna reprezentacija unetog broja */
  printf("Binarna reprezentacija: ");
  stampaj_bitove_short(broj_short);

  /* Ucitava se broj tipa char */
  printf("Unesite broj tipa char: ");
  scanf("%hhx", &broj_char);

  /* Ispisuje se binarna reprezentacija unetog broja */
  printf("Binarna reprezentacija: ");
  stampaj_bitove_char(broj_char);

  return 0;
}
