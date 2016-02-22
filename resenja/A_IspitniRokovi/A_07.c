#include <stdio.h>

/* Funkcija vraca broj ciji binarni zapis se dobija kada se binarni
   zapis argumenta x rotira za n mesta udesno */
unsigned int rotiraj(unsigned int x, unsigned int n)
{
  int i;
  unsigned int maska = 1;
  /* Formira se maska sa n jedinica na kraju, npr za n=4 maska bi
     izgledala: 000...00001111 */
  /* Maska se moze formirati i naredbom: maska = (1 << n) - 1; U
     nastavku je drugi nacin. */
  for (i = 1; i < n; i++)
    maska = (maska << 1) | 1;
  /* Kada se x pomeri za n mesta udesno x >> n, poslednjih n bitova 
     binarne reprezentacije broja x ce "ispasti". Za rotaciju je
     potrebno da se tih n bitova postavi na pocetak broja. Kreirana 
     maska omogucava da se tih n bitova izdvoji sa (maska & x), a
     zatim se pomeranjem za (sizeof(unsigned) * 8 - n) mesta ulevo
     tih n bitova postavlja na pocetak primenom bitovske
     disjunkcije i dobija se trazeni broj. */
  return (x >> n) | ((maska & x) << (sizeof(unsigned) * 8 - n));
}

int main()
{
  unsigned int x, n;

  /* Ucitaju se brojevi sa standardnog ulaza */
  scanf("%u%u", &x, &n);

  /* Ispisuje se rezultat */
  printf("%u\n", rotiraj(x, n));
  return 0;
}
