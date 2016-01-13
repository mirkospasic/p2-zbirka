#include <stdio.h>
#include "sort.h"
#define MAX_DIM 256

/* Funkcija za odredjivanje onog elementa sortiranog niza koji se
   najvise puta pojavio u tom nizu */
int najvise_puta(int a[], int n)
{
  int i, j, br_pojava, i_max_pojava = -1, max_br_pojava = -1;
  /* Za i-ti element izracunava se koliko puta se pojavio u nizu */
  for (i = 0; i < n; i = j) {
    br_pojava = 1;
    for (j = i + 1; j < n && a[i] == a[j]; j++)
      br_pojava++;
    /* Ispitivanje da li se do tog trenutka i-ti element pojavio
       najvise puta u nizu */
    if (br_pojava > max_br_pojava) {
      max_br_pojava = br_pojava;
      i_max_pojava = i;
    }
  }
  /* Vraca se element koji se najvise puta pojavio u nizu */
  return a[i_max_pojava];
}

int main()
{
  int a[MAX_DIM], i;

  /* Ucitavanje elemenata niza sve do kraja ulaza */
  i = 0;
  while (scanf("%d", &a[i]) != EOF)
    i++;

  /* Za sortiranje niza moze se koristiti bilo koja od funkcija
     sortiranja iz sort.h. Ilustracije radi, u ovom zadatku koristi
     se merge sort. */
  merge_sort(a, 0, i - 1);

  /* Odredjuje se broj koji se najvise puta pojavio u nizu */
  printf("%d\n", najvise_puta(a, i));

  return 0;
}
