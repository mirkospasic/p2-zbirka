#include <stdio.h>


/* Rekurzivna funkcija za odredjivanje najvece oktalne cifre u broju */
int max_heksadekadna_cifra(unsigned x)
{
  /* Izlazak iz rekurzije */
  if (x == 0)
    return 0;
  /* Odredjivanje poslednje heksadekadne cifre u broju */
  int poslednja_cifra = x & 15;
  /* Odredjivanje maksimalne heksadekadne cifre broja kada se iz
     njega izbrise poslednja heksadekadna cifra */
  int max_bez_poslednje_cifre = max_heksadekadna_cifra(x >> 4);
  return poslednja_cifra >
      max_bez_poslednje_cifre ? poslednja_cifra :
      max_bez_poslednje_cifre;
}

int main()
{
  unsigned x;
  scanf("%u", &x);
  printf("%d\n", max_heksadekadna_cifra(x));
  return 0;
}
