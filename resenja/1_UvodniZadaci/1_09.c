#include <stdio.h>
#include "stampanje_bitova.h"

/* Funkcija ceo broj x rotira u levo za n mesta. */
unsigned rotiraj_ulevo(int x, unsigned n)
{
  unsigned bit_najvece_tezine;

  /* Maska koja ima samo bit na poziciji najvece tezine postavljen na
     1 je neophodna da bi pre pomeranja u levo za 1 bit na poziciji 
	 najvece tezine bio sacuvan */
  unsigned bit_najvece_tezine_maska = 1 << (sizeof(unsigned) * 8 - 1);
  int i;

  /* n puta se vrsi rotaciju za jedan bit u levo. U svakoj iteraciji
     se odredi bit na poziciji najvece tezine, a potom se pomera 
	 binarna reprezentacija trenutne vrednosti promenljive x u levo 
	 za 1. Nakon toga, bit na poziciji najmanje tezine se postavlja 
	 na vrednost koju je imao bit na poziciji najvece tezine koji je 
	 istisnut pomeranjem */
  for (i = 0; i < n; i++) {
    bit_najvece_tezine = x & bit_najvece_tezine_maska;
    x = x << 1 | (bit_najvece_tezine ? 1 : 0);
  }

  /* Vraca se dobijena vrednost */
  return x;
}

/* Funkcija neoznacen broj x rotira u desno za n mesta. */
unsigned rotiraj_udesno(unsigned x, unsigned n)
{
  unsigned bit_najmanje_tezine;
  int i;

  /* n puta se ponavlja rotacija u desno za jedan bit. U svakoj
     iteraciji se odredjuje bit na poziciji najmanje tezine broja x,
	 zatim tako odredjeni bit se pomera u levo tako da bit na 
	 poziciji najmanje tezine dodje do pozicije najvece tezine. 
	 Zatim, nakon pomeranja binarne reprezentacije trenutne vrednosti
	 promenljive x za 1 u desno, bit na poziciji najvece tezine se 
	 postaljva na vrednost vec zapamcenog bita koji je bio na 
	 poziciji najmanje tezine. */
  for (i = 0; i < n; i++) {
    bit_najmanje_tezine = x & 1;
    x = x >> 1 | bit_najmanje_tezine << (sizeof(unsigned) * 8 - 1);
  }

  /* Vraca se dobijena vrednost */
  return x;
}

/* Verzija funkcije koja broj x rotira u desno za n mesta, gde je
   argument funkcije x oznaceni ceo broj */
int rotiraj_udesno_oznaceni(int x, unsigned n)
{
  unsigned bit_najmanje_tezine;
  int i;

  /* U svakoj iteraciji se odredjuje bit na poziciji najmanje tezine
     i smesta u promenljivu bit_najmanje_tezine. Kako je x oznacen 
	 ceo broj, tada se prilikom pomeranja u desno vrsi aritmeticko 
	 pomeranje i cuva se znak broja. Dakle, razlikuju se dva slucaja
	 u zavisnosti od znaka broja x. Nije dovoljno da se ova provera 
	 izvrsi pre petlje, s obzirom da rotiranjem u desno na poziciju 
	 nejvece tezine moze doci i 0 i 1, nezavisno od pocetnog znaka 
	 broja smestenog u promenljivu x. */
  for (i = 0; i < n; i++) {
    bit_najmanje_tezine = x & 1;

    if (x < 0)
  /******************************************************************
    Siftovanjem u desno broja koji je negativan dobija se 1 kao bit 
	na poziciji najvece tezine. Na primer ako je x      
    1010 1011 1100 1101 1110 0001 0010 001b 
      (sa b je oznacen ili 1 ili 0 na poziciji najmanje tezine) 
    Onda je sadrzaj promenljive bit_najmanje_tezine:
    0000 0000 0000 0000 0000 0000 0000 000b 
    Nakon siftovanja sadrzaja promenljive x za 1 u desno 
    1101 0101 1110 0110 1111 0000 1001 0001 
    Kako bi umesto 1 na poziciji najvece tezine u trenutnoj binarnoj 
    reprezentaciji x bilo postavljeno b nije dovoljno da se pomeri na 
    poziciju najvece tezine jer bi se time dobile 0, a u ovom slucaju
	su potrebne jedinice zbog bitovskog & zato se prvo vrsi 
    komplementiranje, a zatim pomeranje 
    ~bit_najmanje_tezine << (sizeof(int)*8 -1) 
    B000 0000 0000 0000 0000 0000 0000 0000 
    gde B oznacava ~b.
    Potom se ponovo vrsi komplementiranje kako bi se b nalazilo na 
    poziciji najvece tezine i sve jedinice na ostalim pozicijama 
    ~(~bit_najmanje_tezine << (sizeof(int)*8 -1)) 
    b111 1111 1111 1111 1111 1111 1111 1111 
  ******************************************************************/
      x = (x >> 1) & ~(~bit_najmanje_tezine << (sizeof(int) * 8 - 1));
    else
      x = (x >> 1) | bit_najmanje_tezine << (sizeof(int) * 8 - 1);
  }

  /* Vraca se dobijena vrednost */
  return x;
}

int main()
{
  unsigned x, k;

  /* Ucitavaju se vrednosti sa standardnog ulaza */
  printf("Unesite neoznacen ceo broj x:");
  scanf("%x", &x);
  printf("Unesite neoznacen ceo broj k:");
  scanf("%x", &k);

  /* Ispisuje se binarna reprezentacija broja x */
  printf("x = ", "");
  stampaj_bitove(x);

  /* Testira se rad napisanih funkcija */
  printf("rotiraj_ulevo(%10u,%10u) %10s= ", x, k, "");
  stampaj_bitove(rotiraj_ulevo(x, k));

  printf("rotiraj_udesno(%10u,%10u) %9s= ", x, k, "");
  stampaj_bitove(rotiraj_udesno(x, k));

  printf("rotiraj_udesno_oznaceni(%10u,%10u) = ", x, k);
  stampaj_bitove(rotiraj_udesno_oznaceni(x, k));

  return 0;
}