#include <stdio.h>
#define MAX_DIM 256

int br_pojave(int x, int a[], int n)
{
  /* Izlazak iz rekurzije */
  if (n == 1)
    return a[0] == x ? 1 : 0;

  int bp = br_pojave(x, a, n - 1);
  return a[n - 1] == x ? 1 + bp : bp;
}

int main()
{
  int x, a[MAX_DIM];
  int n, i = 0;

  printf("Unesite ceo broj:");
  scanf("%d", &x);

  /* Sve dok se ne stigne do kraja ulaza, ucitavaju se brojevi u niz; 
     Promenljiva i predstavlja indeks tekuceg broja */
  printf("Unesite elemente niza:");
  i = 0;
  while (scanf("%d", &a[i]) != EOF) {
    i++;
  }
  n = i;

  printf("Broj pojavljivanja je %d\n", br_pojave(x, a, n));
  return 0;
}
