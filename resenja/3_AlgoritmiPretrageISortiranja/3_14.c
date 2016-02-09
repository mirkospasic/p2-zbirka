#include <stdio.h>
#include "sort.h"

#define MAX 256

/* Funkcija koja pronalazi najmanje rastojanje izmedju dva broja u
   sortiranom nizu celih brojeva */
int najmanje_rastojanje(int a[], int n)
{
  int i, min;
  min = a[1] - a[0];
  for (i = 2; i < n; i++)
    if (a[i] - a[i - 1] < min)
      min = a[i] - a[i - 1];
  return min;
}

int main()
{
  int i, a[MAX];

  /* Ucitavaju se elementi niza sve do kraja ulaza */
  i = 0;
  while (scanf("%d", &a[i]) != EOF)
    i++;

  /* Za sortiranje niza moze se koristiti bilo koja od funkcija
     sortiranja iz sort.h. Ilustracije radi, u ovom zadatku koristi
     se selection sort. */
  selection_sort(a, i);

  /* Ispis rezultata */
  printf("%d\n", najmanje_rastojanje(a, i));

  return 0;
}
