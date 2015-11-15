#include <stdio.h>

/***************************************************************
   Funckija postavlja na nulu n bitova pocev od pozicije p.
   Pozicije se broje pocev od pozicije najnizeg bita, pri cemu
   se broji od nule . 
   
   Npr, za n=5, p=10 1010 1011 1100 1101 1110 
   1010 1110 0111 1010 1011 1100 1101 1110 1000 0010 0111 */
unsigned reset(unsigned x, unsigned n, unsigned p)
{
/***************************************************************
     Cilj je anulirati samo zeljene bitove, a da ostali
     ostanu nepromenjeni. Maska koja ce se koristiti je ona cija 
     binarna reprezentacija ima n bitova
     postavljenih na 0 pocev od pozicije p, dok su svi ostali
     postavljeni na 1.

     Na primer, za n=5 i p=10 cilj je maska oblika 
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


/***************************************************************
   Funckija postavlja na 1 n bitova pocev od pozicije p.
   Pozicije se broje pocev od pozicije najnizeg bita, pri cemu
   se broji od nule . 
   
   Npr, za n=5, p=10 
   1010 1011 1100 1101 1110 1010 1110 0111 
   1010 1011 1100 1101 1110 1111 1110 0111 
***************************************************************/
unsigned set(unsigned x, unsigned n, unsigned p)
{

/***************************************************************
     Cilj je samo odredjenih n bitova postaviti na 1, dok 
     ostali treba da ostanu netaknuti. 
     
     Na primer, za n=5 i p=10 formira se maska oblika 
     0000 0000 0000 0000 0000 0111 1100 0000 
     prateci vrlo slican postupak kao za prethodnu funkciju 
***************************************************************/
  unsigned maska = ~(~0 << n) << (p - n + 1);

  return x | maska;
}

/***************************************************************
   Funkcija vraca celobrojno polje bitova, desno poravnato, koje 
   predstavlja n bitova pocev od pozicije p u binarnoj
   reprezentaciji broja x, pri cemu se pozicija broji sa desna
   ulevo, gde je pocetna pozicija 0. 
   
   Na primer za n = 5 i p = 10 
   i broj cija je binarna reprezentacija:
   1010 1011 1100 1101 1110 1010 1110 0111 
   trazi se
   0000 0000 0000 0000 0000 0000 0000 1011 
***************************************************************/
unsigned get_bits(unsigned x, unsigned n, unsigned p)
{

/***************************************************************
     Kreira se maska kod koje su poslednjih n bitova 1, a
     ostali su 0. 
     
     Na primer za n=5 
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
/***************************************************************
     Kreira se maska kod kod koje su poslednjih n bitova 1, a
     ostali su 0. 
     
     Na primer za n=5 
     0000 0000 0000 0000 0000 0000 0001 1111 
***************************************************************/
  unsigned last_n_1 = ~(~0 << n);
/***************************************************************
     Kao sto je i u funkciji reset, i ovde se kreira masku koja ima n
     bitova postavljenih na 0 pocevsi od pozicije p, dok su
     ostali bitovi 1. 
     
     Na primer za n=5 i p =10 
     1111 1111 1111 1111 1111 1000 0011 1111 
***************************************************************/
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
/***************************************************************
     Formira se maska sa n jedinica pocev od pozicije p.
     
     Na primer za n=5 i p=10 
     0000 0000 0000 0000 0000 0111 1100 0000 
***************************************************************/
  unsigned maska = ~(~0 << n) << (p - n + 1);

  /* Operator ekskluzivno ili invertuje sve bitove gde je
     odgovarajuci bit maske 1. Ostali bitovi ostaju nepromenjeni. */
  return maska ^ x;
}


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

  /* Ispisuju se binarne reprezentacije brojeva x i y */
  printf("x = %u = ", x);
  print_bits(x);

  printf("y = %u = ", y);
  print_bits(y);

  /* Testira se rad napisanih funkcija */
  printf("reset(%u,%u,%u) = ", x, n, p);
  print_bits(reset(x, n, p));

  printf("set(%u,%u,%u) = ", x, n, p);
  print_bits(set(x, n, p));

  printf("get_bits(%u,%u,%u) = ", x, n, p);
  print_bits(get_bits(x, n, p));

  printf("set_n_bits(%u,%u,%u,%u) = ", x, n, p, y);
  print_bits(set_n_bits(x, n, p, y));

  printf("invert(%u,%u,%5u) = ", x, n, p);
  print_bits(invert(x, n, p));

  return 0;
}
