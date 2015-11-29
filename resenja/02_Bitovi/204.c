#include <stdio.h>
#include "stampanje_bitova.h"

/* Funckija postavlja na nulu n bitova pocev od pozicije p. */
unsigned reset(unsigned x, unsigned n, unsigned p)
{
/***************************************************************
     Formira se maska cija binarna reprezentacija ima n bitova 
     postavljenih na 0 pocev od pozicije p, dok su svi ostali 
     postavljeni na 1. Na primer, za n=5 i p=10 formira se 
     maska oblika 
     1111 1111 1111 1111 1111 1000 0011 1111 
     To se postize na sledeci nacin: 
     ~0                  1111 1111 1111 1111 1111 1111 1111 1111 
(~0 << n)                1111 1111 1111 1111 1111 1111 1110 0000 
~(~0 << n)               0000 0000 0000 0000 0000 0000 0001 1111 
(~(~0 << n) << ( p-n+1)) 0000 0000 0000 0000 0000 0111 1100 0000 
~(~(~0 << n) << (p-n+1)) 1111 1111 1111 1111 1111 1000 0011 1111 
***************************************************************/
  unsigned maska = ~(~(~0 << n) << (p - n + 1));

  return x & maska;
}


/* Funckija postavlja na jedinicu n bitova pocev od pozicije p. */
unsigned set(unsigned x, unsigned n, unsigned p)
{

/***************************************************************
     Formira se maska kod koje je samo n bitova pocev od 
     pocev od pozicije p jednako 1, a ostali su 0. 
     Na primer, za n=5 i p=10 formira se maska oblika 
     0000 0000 0000 0000 0000 0111 1100 0000 
***************************************************************/
  unsigned maska = ~(~0 << n) << (p - n + 1);

  return x | maska;
}

/* Funkcija vraca celobrojno polje bitova, desno poravnato, koje 
   predstavlja n bitova pocev od pozicije p u binarnoj
   reprezentaciji broja x. */
unsigned get_bits(unsigned x, unsigned n, unsigned p)
{

/***************************************************************
     Kreira se maska kod koje su poslednjih n bitova 1, a
     ostali su 0. Na primer, za n=5 
     0000 0000 0000 0000 0000 0000 0001 1111 
***************************************************************/
  unsigned maska = ~(~0 << n);

  /* Najpre se vrednost promenljive x pomera u desno tako da trazeno
     polje bude uz desni kraj. Zatim se maskiraju ostali bitovi, sem
     zeljenih n i funkcija vraca tako dobijenu vrednost */
  return maska & (x >> (p - n + 1));
}


/* Funkcija vraca broj x kome su n bitova pocev od pozicije p
   postavljeni na vrednosti n bitova najnize tezine binarne
   reprezentacije broja y */
unsigned set_n_bits(unsigned x, unsigned n, unsigned p, unsigned y)
{
  /* Kreira se maska kod kod koje su poslednjih n bitova 1, a
     ostali su 0. */
  unsigned last_n_1 = ~(~0 << n);

  /* Kao i kod funkcije reset, i ovde se kreira maska koja ima n
     bitova postavljenih na 0 pocevsi od pozicije p, dok su
     ostali bitovi 1. */
  unsigned middle_n_0 = ~(~(~0 << n) << (p - n + 1));

  /* U promenljivu x_reset se smesta vrednost dobijena kada se u
     binarnoj reprezentaciji vrednosti promenljive x resetuje n
     bitova na pozicijama pocev od p */
  unsigned x_reset = x & middle_n_0;

  /* U promenlijvu y_shift_middle se smesta vrednost dobijena od
     binarne reprezentacije vrednosti promenljive y cijih je n bitova 
     najnize tezine pomera tako da stoje pocev od pozicije p. Ostali
     bitovi su nule. Sa (y & last_n_1) resetuju se svi bitovi osim
     najnizih n */
  unsigned y_shift_middle = (y & last_n_1) << (p - n + 1);

  return x_reset ^ y_shift_middle;
}


/* Funkcija invertuje bitove u zapisu broja x pocevsi od pozicije p
   njih n */
unsigned invert(unsigned x, unsigned n, unsigned p)
{
  /* Formira se maska sa n jedinica pocev od pozicije p. */
  unsigned maska = ~(~0 << n) << (p - n + 1);

  /* Operator ekskluzivno ili invertuje sve bitove gde je
     odgovarajuci bit maske 1. Ostali bitovi ostaju nepromenjeni. */
  return maska ^ x;
}

int main()
{
  unsigned x, p, n, y;

  /* Ucitavaju se vrednosti sa standardnog ulaza */
  printf("Unesite neoznacen ceo broj x:\n");
  scanf("%u", &x);
  printf("Unesite neoznacen ceo broj n:\n");
  scanf("%u", &n);
  printf("Unesite neoznacen ceo broj p:\n");
  scanf("%u", &p);
  printf("Unesite neoznacen ceo broj y:\n");
  scanf("%u", &y);
  
  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija reset za x, n i p*/
  printf("x = %6u %28s = ", x, "");
  print_bits(x);
  printf("reset(%10u,%6u,%6u)%12s = ", x, n, p, "");
  print_bits( reset(x, n, p));

  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija set za x, n i p*/
  printf("x = %10u %28s = ", x, "");
  print_bits(x);
  printf("set(%10u,%6u,%6u)%14s = ", x, n, p, "");
  print_bits( set(x, n, p));

  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija get_bits za x, n i p*/
  printf("x = %10u %28s = ", x, "");
  print_bits(x);
  printf("get_bits(%10u,%6u,%6u)%9s = ", x, n, p, "");
  print_bits( get_bits(x, n, p));

  /* Ispisuju se binarne reprezentacije brojeva x, y i broja koji se 
     dobije kada se primeni funkcija set_n_bits za x, n i p*/
  printf("x = %10u %28s = ", x, "");
  print_bits(x);
  printf("y = %10u %29s= ", y, "");
  print_bits(y);
  printf("set_n_bits(%10u,%4u,%4u,%10u) = ", x, n, p, y);
  print_bits( set_n_bits(x, n, p, y));

  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija invert za x, n i p*/
  printf("x = %10u %28s = ", x, "");
  print_bits(x);
  printf("invert(%10u,%6u,%6u)%11s = ", x, n, p, "");
  print_bits( invert(x, n, p));

  return 0;
}
