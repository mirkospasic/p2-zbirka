#include <stdio.h>

int lin_pretgraga_rek(int a[], int n, int x)
{
  int tmp;
  /* izlaz iz rekurzije */
  if (n <= 0)
    return -1;
  /* ako je prvi element trazeni */
  if (a[0] == x)                /* if (a[n-1] == x) */
    return 0;                   /* return n - 1; */
  /* pretraga ostatka niza */
  tmp = lin_pretgraga_rek(a + 1, n - 1, x);
  return tmp < 0 ? tmp : tmp + 1;
  /* return lin_pretgraga_rek(a, n - 1, x); */
}

int bin_pretgraga_rek(int a[], int l, int d, int x)
{
  int srednji;
  if (l > d)
    return -1;
  /* srednja pozicija na kojoj se trazi vrednost x */
  srednji = (l + d) / 2;
  /* ako je sredisnji element trazeni */
  if (a[srednji] == x)
    return srednji;
  /* ako je trazeni broj veci od srednjeg, pretrazujemo desnu
     polovinu niza */
  if (a[srednji] < x)
    return bin_pretgraga_rek(a, srednji + 1, d, x);
  /* ako je trazeni broj manji od srednjeg, pretrazujemo levu
     polovinu niza */
  else
    return bin_pretgraga_rek(a, l, srednji - 1, x);
}


int interp_pretgraga_rek(int a[], int l, int d, int x)
{
  int p;
  if (x < a[l] || x > a[d])
    return -1;
  if (a[d] == a[l])
    return l;
  /* pozicija na kojoj se trazi vrednost x */
  p = l + (d - l) * (x - a[l]) / (a[d] - a[l]);
  if (a[p] == x)
    return p;
  if (a[p] < x)
    return interp_pretgraga_rek(a, p + 1, d, x);
  else
    return interp_pretgraga_rek(a, l, p - 1, x);
}

#define MAX 1024

int main()
{
  int a[MAX];
  int x;
  int i, indeks;

  /* ucitavamo trazeni broj */
  scanf("%d", &x);

  /* ucitavamo elemente niza sve do kraja ulaza - ocekujemo da
     korisnik pritisne CTRL+D za naznaku kraja */
  i = 0;
  while (scanf("%d", &a[i]) == 1) {
    i++;
  }

  printf("Linearna pretraga\n");
  indeks = lin_pretgraga_rek(a, i, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  printf("Binarna pretraga\n");
  indeks = bin_pretgraga_rek(a, 0, i - 1, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  printf("Interpolaciona pretraga\n");
  indeks = interp_pretgraga_rek(a, 0, i - 1, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  return 0;
}
