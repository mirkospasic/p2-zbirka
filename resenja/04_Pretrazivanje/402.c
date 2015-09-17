#include <stdio.h>

int lin_pretgraga_rek_sufiks(int a[], int n, int x)
{
  int tmp;
  /* Izlaz iz rekurzije */
  if (n <= 0)
    return -1;
  /* Ako je prvi element trazeni */
  if (a[0] == x)
    return 0;
  /* Pretraga ostatka niza */
  tmp = lin_pretgraga_rek_sufiks(a + 1, n - 1, x);
  return tmp < 0 ? tmp : tmp + 1;
}

int lin_pretgraga_rek_prefiks(int a[], int n, int x)
{
  /* Izlaz iz rekurzije */
  if (n <= 0)
    return -1;
  /* Ako je poslednji element trazeni */
  if (a[n - 1] == x)
    return n - 1;
  /* Pretraga ostatka niza */
  return lin_pretgraga_rek_prefiks(a, n - 1, x);
}

int bin_pretgraga_rek(int a[], int l, int d, int x)
{
  int srednji;
  if (l > d)
    return -1;
  /* Sredisnja pozicija na kojoj se trazi vrednost x */
  srednji = (l + d) / 2;
  /* Ako je element na sredisnjoj poziciji trazeni */
  if (a[srednji] == x)
    return srednji;
  /* Ako je trazeni broj veci od broja na sredisnjoj poziciji,
     pretrazuje se desna polovina niza */
  if (a[srednji] < x)
    return bin_pretgraga_rek(a, srednji + 1, d, x);
  /* Ako je trazeni broj manji od broja na sredisnjoj poziciji,
     pretrazuje se leva polovina niza */
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
  /* Pozicija na kojoj se trazi vrednost x */
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

  /* Ucitavanje trazenog broja */
  printf("Unesite trazeni broj: ");
  scanf("%d", &x);

  /* Ucitavanje elemenata niza sve do kraja ulaza - ocekuje se da
     korisnik pritisne CTRL+D za naznaku kraja */
  i = 0;
  printf("Unesite sortiran niz elemenata: ");
  while (scanf("%d", &a[i]) == 1) {
    i++;
  }

  /* Linearna pretraga */
  printf("Linearna pretraga\n");
  indeks = lin_pretgraga_rek_sufiks(a, i, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  /* Binarna pretraga */
  printf("Binarna pretraga\n");
  indeks = bin_pretgraga_rek(a, 0, i - 1, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  /* Interpolaciona pretraga */
  printf("Interpolaciona pretraga\n");
  indeks = interp_pretgraga_rek(a, 0, i - 1, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  return 0;
}
