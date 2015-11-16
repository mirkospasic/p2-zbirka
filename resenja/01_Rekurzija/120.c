#include <stdio.h>


/* Rekurzivna funkcija za odredjivanje najvece heksadekadne cifre u
   broju */
int max_heksadekadna_cifra(unsigned x)
{
  /* Izlazak iz rekurzije: ako je vrednost broja 0, onda je i
     vrednost najvece heksadekadne cifre u broju 0 */
  if (x == 0)
    return 0;

  /* Odredjivanje poslednje heksadekadne cifre u broju */
  int poslednja_cifra = x & 15;

  /* Odredjivanje maksimalne heksadekadne cifre broja kada se iz
     njega izbrise poslednja heksadekadna cifra */
  int max_bez_poslednje_cifre = max_heksadekadna_cifra(x >> 4);

  return poslednja_cifra > max_bez_poslednje_cifre ? poslednja_cifra
      : max_bez_poslednje_cifre;
}

int main()
{
  unsigned x;

  /* Ucitava se neoznacen ceo broj */
  scanf("%u", &x);

  /* Ispisuje se vrednost najvece heksadekadne cifre unetog broja */
  printf("%d\n", max_heksadekadna_cifra(x));

  return 0;
}
