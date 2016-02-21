#include <stdio.h>
#include <stdlib.h>

/* Rekurzivna funkcija za racunanje binomnog koeficijenta */
int binomni_koeficijent(int n, int k)
{
  /* Ukoliko je k=0 ili k=n, onda je binomni koeficijent 0. Ukoliko
     je k strogo izmedju 0 i n, onda se koristi formula bk(n,k) =
     bk(n-1,k-1) + bk(n-1,k) koja se moze izvesti iz definicije
     binomnog koeficijenata */
  return (0 < k && k < n) ?
      binomni_koeficijent(n - 1, k - 1) +
      binomni_koeficijent(n - 1, k) : 1;
}

/******************************************************************
  Iterativno izracunavanje datog binomnog koeficijenta

  int binomni_koeficijent (int n, int k) {
    int i, j, b;
    
    for (b=i=1, j=n; i<=k; b =b * j-- / i++);
      
    return b;
  }
  
  Iterativno resenje je efikasnije i preporucuje se. Rekurzivno 
  resenje je navedeno u cilju demonstracije rekurzivnih tehnika.
*******************************************************************/

/* Svaki element n-te hipotenuze (osim ivicnih jedinica) dobija kao
   zbir 2 elementa iz n-1 hipotenuze. Ukljucujuci i pomenute dve
   ivicne jedinice suma elemenata n-te hipotenuze je tacno 2 puta
   veca od sume elemenata prethodne hipotenuze. */
int suma_elemenata_hipotenuze(int n)
{
  return n > 0 ? 2 * suma_elemenata_hipotenuze(n - 1) : 1;
}

int main()
{
  int n, k, i, d, r;

  /* Ucitavaju se brojevi d i r */
  scanf("%d %d", &d, &r);

  /* Ispisuje se Paskalov trougao */
  putchar('\n');
  for (n = 0; n <= d; n++) {
    for (i = 0; i < d - n; i++)
      printf("  ");
    for (k = 0; k <= n; k++)
      printf("%4d", binomni_koeficijent(n, k));
    putchar('\n');
  }

  /* Proverava se da li je r nenegativan */
  if (r < 0) {
    fprintf(stderr,
            "Greska: Redni broj hipotenuze mora biti veci ili jednak od 0!\n");
    exit(EXIT_FAILURE);
  }

  /* Ispisuje se suma elemenata hipotenuze */
  printf("%d\n", suma_elemenata_hipotenuze(r));

  exit(EXIT_SUCCESS);
}
