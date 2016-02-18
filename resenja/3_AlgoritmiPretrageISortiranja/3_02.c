#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

/* Rekurzivna linearna pretraga od pocetka niza */
int linearna_pretraga_r1(int a[], int n, int x)
{
  int tmp;
  /* Izlaz iz rekurzije */
  if (n <= 0)
    return -1;
  /* Ako je prvi element trazeni */
  if (a[0] == x)
    return 0;
  /* Pretraga ostatka niza */
  tmp = linearna_pretraga_r1(a + 1, n - 1, x);
  return tmp < 0 ? tmp : tmp + 1;
}

/* Rekurzivna linearna pretraga od kraja niza */
int linearna_pretraga_r2(int a[], int n, int x)
{
  /* Izlaz iz rekurzije */
  if (n <= 0)
    return -1;
  /* Ako je poslednji element trazeni */
  if (a[n - 1] == x)
    return n - 1;
  /* Pretraga ostatka niza */
  return linearna_pretraga_r2(a, n - 1, x);
}

/* Rekurzivna binarna pretraga */
int binarna_pretraga_r(int a[], int l, int d, int x)
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
    return binarna_pretraga_r(a, srednji + 1, d, x);
  /* Ako je trazeni broj manji od broja na sredisnjoj poziciji,
     pretrazuje se leva polovina niza */
  else
    return binarna_pretraga_r(a, l, srednji - 1, x);
}

/* Rekurzivna interpolaciona pretaga */
int interpolaciona_pretraga_r(int a[], int l, int d, int x)
{
  int p;
  /* Ako je trazeni element manji od prvog ili veci od poslednjeg */
  if (x < a[l] || x > a[d])
    return -1;
  /* Ako je ostao jedan element u delu niza koji se pretrazuje */
  if (a[d] == a[l])
    return l;
  /* Pozicija na kojoj se trazi vrednost x */
  p = l + (d - l) * (x - a[l]) / (a[d] - a[l]);
  if (a[p] == x)
    return p;
  /* Pretraga sufiksa niza */
  if (a[p] < x)
    return interpolaciona_pretraga_r(a, p + 1, d, x);
  /* Pretraga prefiksa niza */
  else
    return interpolaciona_pretraga_r(a, l, p - 1, x);
}

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
  while (i < MAX && scanf("%d", &a[i]) == 1) {
    if (i > 0 && a[i] < a[i - 1]) {
      fprintf(stderr, "Greska: Elementi moraju biti uneseni ");
      fprintf(stderr, "u neopadajucem poretku\n");
      exit(EXIT_FAILURE);
    }
    i++;
  }

  /* Rezultati linearnih pretraga */
  printf("Linearna pretraga\n");
  indeks = linearna_pretraga_r1(a, i, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);
  indeks = linearna_pretraga_r2(a, i, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  /* Rezultati binarna pretrage */
  printf("Binarna pretraga\n");
  indeks = binarna_pretraga_r(a, 0, i - 1, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  /* Rezultati interpolacione pretrage */
  printf("Interpolaciona pretraga\n");
  indeks = interpolaciona_pretraga_r(a, 0, i - 1, x);
  if (indeks == -1)
    printf("Element se ne nalazi u nizu.\n");
  else
    printf("Pozicija elementa je %d.\n", indeks);

  exit(EXIT_SUCCESS);
}
