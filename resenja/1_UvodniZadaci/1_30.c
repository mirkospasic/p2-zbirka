#include <stdio.h>

/* Rekurzivna funkcija za odredjivanje najvece oktalne cifre u broju */
int max_oktalna_cifra(unsigned x)
{
  /* Izlazak iz rekurzije: ako je vrednost broja 0, onda je i
     vrednost najvece oktalne cifre u broju 0 */
  if (x == 0)
    return 0;

  /* Odredjivanje poslednje oktalne cifre u broju */
  int poslednja_cifra = x & 7;

  /* Odredjivanje maksimalne oktalne cifre u broju kada se iz njega
     izbrise poslednja oktalna cifra */
  int max_bez_poslednje_cifre = max_oktalna_cifra(x >> 3);

  return poslednja_cifra > max_bez_poslednje_cifre ? poslednja_cifra
      : max_bez_poslednje_cifre;
}

int main()
{
  unsigned x;

  /* Ucitava se neoznacen ceo broj */
  scanf("%u", &x);

  /* Ispisuje se vrednost najvece oktalne cifre unetog broja */
  printf("%d\n", max_oktalna_cifra(x));

  return 0;
}
