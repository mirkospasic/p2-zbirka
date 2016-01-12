#include <stdio.h>
#include "stampanje_bitova.h"

int main()
{
  int broj;

  /* Ucitava se broj sa ulaza */
  scanf("%x", &broj);

  /* I ispisuje se njegova binarna reprezentacija */
  stampaj_bitove(broj);

  return 0;
}
