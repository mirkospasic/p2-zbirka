#include<stdio.h>
#define MAX_DIM 256

/* Funkcija za sortiranje niza */
void selectionSort(int a[], int n)
{
  int i, j, min, pom;
  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (a[j] < a[min])
        min = j;
    if (min != i) {
      pom = a[i];
      a[i] = a[min];
      a[min] = pom;
    }
  }
}

/* Funkcija za binarnu pretragu niza. funkcija vraca: 1 - ako se 
   element x nalazi u nizu; 0 - inace. pretpostavlja se da je
   niz sortiran u rastucem poretku */
int binarna_pretraga(int a[], int n, int x)
{
  int levi = 0, desni = n - 1, srednji;

  while (levi <= desni) {
    srednji = (levi + desni) / 2;
    if (a[srednji] == x)
      return 1;
    else if (a[srednji] > x)
      desni = srednji - 1;
    else if (a[srednji] < x)
      levi = srednji + 1;
  }
  return 0;
}

int main()
{
  int a[MAX_DIM], n = 0, zbir, i;

  /* Ucitava se trazeni zbir */
  printf("Unesite trazeni zbir: ");
  scanf("%d", &zbir);

  /* Ucitavaju se elementi niza sve do kraja ulaza */
  i = 0;
  printf("Unesite elemente niza: ");
  while (scanf("%d", &a[i]) != EOF)
    i++;
  n = i;

  selectionSort(a, n);

  for (i = 0; i < n; i++)
    /* Za i-ti element niza binarno se pretrazuje da li se u
       ostatku niza nalazi element koji sabran sa njim ima
       ucitanu vrednost zbira */
    if (binarna_pretraga(a + i + 1, n - i - 1, zbir - a[i])) {
      printf("da\n");
      return 0;
    }
  printf("ne\n");
  return 0;
}
