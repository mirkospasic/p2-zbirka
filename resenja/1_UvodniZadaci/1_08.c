#include <stdio.h>
#include "stampanje_bitova.h"

/* Funckija postavlja na nulu n bitova pocev od pozicije p. */
unsigned postavi_0(unsigned x, unsigned n, unsigned p)
{
/********************************************************************
  Formira se maska cija binarna reprezentacija ima n bitova 
  postavljenih na 0 pocev od pozicije p, dok su svi ostali 
  postavljeni na 1. Na primer, za n=5 i p=10 formira se maska oblika 
  1111 1111 1111 1111 1111 1000 0011 1111 
  To se postize na sledeci nacin: 
  ~0                         1111 1111 1111 1111 1111 1111 1111 1111 
  (~0 << n)                  1111 1111 1111 1111 1111 1111 1110 0000 
  ~(~0 << n)                 0000 0000 0000 0000 0000 0000 0001 1111 
  (~(~0 << n) << ( p-n+1))   0000 0000 0000 0000 0000 0111 1100 0000 
  ~(~(~0 << n) << (p-n+1))   1111 1111 1111 1111 1111 1000 0011 1111 
********************************************************************/
  unsigned maska = ~(~(~0 << n) << (p - n + 1));

  return x & maska;
}

/* Funckija postavlja na jedinicu n bitova pocev od pozicije p. */
unsigned postavi_1(unsigned x, unsigned n, unsigned p)
{

  /******************************************************************
    Formira se maska kod koje je samo n bitova pocev od pocev od 
    pozicije p jednako 1, a ostali su 0. 
    Na primer, za n=5 i p=10 formira se maska oblika 
    0000 0000 0000 0000 0000 0111 1100 0000 
  ******************************************************************/
  unsigned maska = ~(~0 << n) << (p - n + 1);

  return x | maska;
}

/* Funkcija vraca celobrojno polje bitova, desno poravnato, koje 
   predstavlja n bitova pocev od pozicije p u binarnoj
   reprezentaciji broja x. */
unsigned vrati_bitove(unsigned x, unsigned n, unsigned p)
{

  /******************************************************************
    Kreira se maska kod koje su poslednjih n bitova 1, a ostali su 0.
    Na primer, za n=5 
    0000 0000 0000 0000 0000 0000 0001 1111 
  ******************************************************************/
  unsigned maska = ~(~0 << n);

  /* Najpre se vrednost promenljive x pomera u desno tako da trazeno
     polje bude uz desni kraj. Zatim se maskiraju ostali bitovi, sem
     zeljenih n i funkcija vraca tako dobijenu vrednost */
  return maska & (x >> (p - n + 1));
}

/* Funkcija vraca broj x kome su n bitova pocev od pozicije p
   postavljeni na vrednosti n bitova najmanje tezine binarne
   reprezentacije broja y */
unsigned postavi_1_n_bitova(unsigned x, unsigned n, unsigned p, unsigned y)
{
  /* Kreira se maska kod kod koje su poslednjih n bitova 1, a
     ostali su 0. */
  unsigned poslednjih_n_1 = ~(~0 << n);

  /* Kao i kod funkcije postavi_0, i ovde se kreira maska koja ima n
     bitova postavljenih na 0 pocevsi od pozicije p, dok su
     ostali bitovi 1. */
  unsigned srednjih_n_0 = ~(~(~0 << n) << (p - n + 1));

  /* U promenljivu x_postavi_0 se smesta vrednost dobijena kada se u
     binarnoj reprezentaciji vrednosti promenljive x postavi na 0 n
     bitova na pozicijama pocev od p */
  unsigned x_postavi_0 = x & srednjih_n_0;

  /* U promenlijvu y_pomeri_srednje se smesta vrednost dobijena od
     binarne reprezentacije vrednosti promenljive y cijih je n bitova 
     najnize tezine pomera tako da stoje pocev od pozicije p. Ostali
     bitovi su nule. Sa (y & poslednjih_n_1) postave na 0 svi bitovi
     osim najnizih n */
  unsigned y_pomeri_srednje = (y & poslednjih_n_1) << (p - n + 1);

  return x_postavi_0 ^ y_pomeri_srednje;
}

/* Funkcija invertuje bitove u zapisu broja x pocevsi od pozicije p
   njih n */
unsigned invertuj(unsigned x, unsigned n, unsigned p)
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
     dobije kada se primeni funkcija postavi_0 za x, n i p*/
  printf("x = %10u %36s = ", x, "");
  stampaj_bitove(x);
  printf("postavi_0(%10u,%6u,%6u)%16s = ", x, n, p, "");
  stampaj_bitove( postavi_0(x, n, p));
  printf("\n");

  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija postavi_1 za x, n i p*/
  printf("x = %10u %36s = ", x, "");
  stampaj_bitove(x);
  printf("postavi_1(%10u,%6u,%6u)%16s = ", x, n, p, "");
  stampaj_bitove( postavi_1(x, n, p));
  printf("\n");

  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija vrati_bitove za x, n i p*/
  printf("x = %10u %36s = ", x, "");
  stampaj_bitove(x);
  printf("vrati_bitove(%10u,%6u,%6u)%13s = ", x, n, p, "");
  stampaj_bitove( vrati_bitove(x, n, p));
  printf("\n");

  /* Ispisuju se binarne reprezentacije brojeva x, y i broja koji se 
     dobije kada se primeni funkcija postavi_1_n_bitova za x, n i p*/
  printf("x = %10u %36s = ", x, "");
  stampaj_bitove(x);
  printf("y = %10u %36s = ", y, "");
  stampaj_bitove(y);
  printf("postavi_1_n_bitova(%10u,%4u,%4u,%10u) = ", x, n, p, y);
  stampaj_bitove( postavi_1_n_bitova(x, n, p, y));
  printf("\n");

  /* Ispisuju se binarne reprezentacije broja x i broja koji se 
     dobije kada se primeni funkcija invertuj za x, n i p*/
  printf("x = %10u %36s = ", x, "");
  stampaj_bitove(x);
  printf("invertuj(%10u,%6u,%6u)%17s = ", x, n, p, "");
  stampaj_bitove( invertuj(x, n, p));

  return 0;
}
