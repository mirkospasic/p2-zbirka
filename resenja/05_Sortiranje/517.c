#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <search.h>

#define MAX 100

/* Funkcija poredi dva cela broja */
int compare_int(const void *a, const void *b)
{
  /* Konvertujemo void pokazivace u int pokazivace koje zatim
     dereferenciramo, dobijamo int-ove koje oduzimamo i razliku
     vracamo. */

  /* Zbog moguceg prekoracenja opsega celih brojeva necemo ih
     oduzimati return *((int *)a) - *((int *)b); */

  int b1 = *((int *) a);
  int b2 = *((int *) b);

  if (b1 > b2)
    return 1;
  else if (b1 < b2)
    /* Ovo uredjenje favorizujemo jer zelimo rastuci poredak */
    return -1;
  else
    return 0;
}

int compare_int_desc(const void *a, const void *b)
{
  /* Za obrnuti poredak mozemo samo oduzimati a od b */
  /* return *((int *)b) - *((int *)a); */

  /* Ili samo promeniti znak vrednosti koju koju vraca prethodna
     funkcija */
  return -compare_int(a, b);
}

/* Test program */
int main()
{
  size_t n;
  int i, x;
  int a[MAX], *p = NULL;

  /* Unosimo dimenziju */
  printf("Uneti dimenziju niza: ");
  scanf("%ld", &n);
  if (n > MAX)
    n = MAX;

  /* Unosimo elemente niza */
  printf("Uneti elemente niza:\n");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Sortiramo niz celih brojeva */
  qsort(a, n, sizeof(int), &compare_int);

  /* Prikazujemo sortirani niz */
  printf("Sortirani niz u rastucem poretku:\n");
  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  putchar('\n');

  /* Pretrazivanje niza */
  /* Vrednost koju cemo traziti u nizu */
  printf("Uneti element koji se trazi u nizu: ");
  scanf("%d", &x);

  /* Binarna pretraga */
  printf("Binarna pretraga: \n");
  p = bsearch(&x, a, n, sizeof(int), &compare_int);
  if (p == NULL)
    printf("Elementa nema u nizu!\n");
  else
    printf("Element je nadjen na poziciji %ld\n", p - a);

  /* Linearna pretraga */
  printf("Linearna pretraga (lfind): \n");
  p = lfind(&x, a, &n, sizeof(int), &compare_int);
  if (p == NULL)
    printf("Elementa nema u nizu!\n");
  else
    printf("Element je nadjen na poziciji %ld\n", p - a);

  return 0;
}
