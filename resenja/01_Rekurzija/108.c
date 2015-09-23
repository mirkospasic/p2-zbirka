#include <stdio.h>
#include <stdlib.h>

/* Rekurzivna funkcija za racunanje binomnog koeficijenta.  */
/* ako je k=0 ili k=n, onda je binomni koeficijent 0 ako je k
   izmedju 0 i n, onda je bk(n,k) = bk(n-1,k-1) + bk(n-1,k) */
int binomniKoeficijent(int n, int k)
{
  return (0 < k
          && k < n) ? binomniKoeficijent(n - 1,
                                         k - 1) +
      binomniKoeficijent(n - 1, k) : 1;
}

/* Iterativno izracunavanje datog binomnog koeficijenta.

   int binomniKoeficijent (int n, int k) { int i, j, b; for
   (b=i=1, j=n; i<=k; b=b*j--/i++); return b; }

 */

/* Prostim opaZanjem se uocava da se svaki element n-te
   hipotenuze (osim ivicnih 1) dobija kao zbir 2 elementa iz n-1 
   hipotenuze. Uz pomenute dve nove ivicne jedinice lako se
   zakljucuje da ce suma elementa n-te hipotenuze biti tacno 2
   puta veca. */
int sumaElemenataHipotenuze(int n)
{
  return n > 0 ? 2 * sumaElemenataHipotenuze(n - 1) : 1;
}

int main()
{
  int n, k, i, d, r;


  scanf("%d %d", &d, &r);

  /* Ispisivanje Paskalovog trougla */
  putchar('\n');
  for (n = 0; n <= d; n++) {
    for (i = 0; i < d - n; i++)
      printf("  ");
    for (k = 0; k <= n; k++)
      printf("%4d", binomniKoeficijent(n, k));
    putchar('\n');
  }

  if (r < 0) {
    fprintf(stderr,
            "Redni broj hipotenuze mora biti veci ili jednak od 0!\n");
    exit(EXIT_FAILURE);
  }
  printf("%d\n", sumaElemenataHipotenuze(r));

  exit(EXIT_SUCCESS);
}
