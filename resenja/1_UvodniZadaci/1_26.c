#include <stdio.h>
#define MAKS_DIM 256

/* Funkcija koja racuna broj pojavljivanja elementa x u nizu a
   duzine n */
int br_pojave(int x, int a[], int n)
{
  /* Izlazak iz rekurzije: za niz duzine jedan broj pojava broja x
     u nizu je 1 ukoliko je jedini element a[0] bas x ili 0 inace */
  if (n == 1)
    return a[0] == x ? 1 : 0;

  /* U promenljivu bp se smesta broj pojave broja x u prvih n-1
     elemenata niza a. Ukupan broj pojavljivanja broja x u celom
     nizu a je jednak bp uvecanom za jedan ukoliko je se na
     poziciji n-1 u nizu a nalazi broj x */
  int bp = br_pojave(x, a, n - 1);
  return a[n - 1] == x ? 1 + bp : bp;
}

int main()
{
  int x, a[MAKS_DIM];
  int n, i = 0;

  /* Ucitava se ceo broj */
  printf("Unesite ceo broj:");
  scanf("%d", &x);

  /* Sve dok se ne stigne do kraja ulaza, ucitavaju se brojevi u
     niz. Promenljiva i predstavlja indeks tekuceg broja. U niz se
     ne moze ucitati vise od MAKS_DIM brojeva, pa se u slucaju da
     promenljiva i dostigne vrednost MAKS_DIM prekida unos novih
     brojeva. */
  printf("Unesite elemente niza:");
  i = 0;
  while (scanf("%d", &a[i]) != EOF) {
    i++;
    if (i == MAKS_DIM)
      break;
  }
  n = i;

  /* Ispisuje se broj pojavljivanja */
  printf("Broj pojavljivanja je %d\n", br_pojave(x, a, n));

  return 0;
}
