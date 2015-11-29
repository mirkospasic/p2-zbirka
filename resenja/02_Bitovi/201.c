#include <stdio.h>
#include "stampanje_bitova.h"

int main()
{
  int broj;

  /* Ucitava se broj sa ulaza */
  scanf("%x", &broj);

  /* I ispisuje se njegova binarna reprezentacija */
  print_bits(broj);

  return 0;
}
