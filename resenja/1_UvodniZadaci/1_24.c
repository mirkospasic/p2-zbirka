#include <stdio.h>
#define MAKS_DIM 256

/* Rekurzivna funkcija koja odredjuje maksimum celobrojnog niza niz
   dimenzije n */
int maksimum_niza(int niz[], int n)
{
  /* Izlazak iz rekurzije: ako je niz dimenzije jedan, najveci je
     ujedno i jedini element niza */
  if (n == 1)
    return niz[0];

  /* Resavanje problema manje dimenzije */
  int max = maksimum_niza(niz, n - 1);

  /* Na osnovu poznatog resenja problema dimenzije n-1, resava se
     problem dimenzije n */
  return niz[n - 1] > max ? niz[n - 1] : max;
}

int main()
{
  int brojevi[MAKS_DIM];
  int n;

  /* Sve dok se ne stigne do kraja ulaza, brojeve se ucitavaju u
     niz. Promenljiva i predstavlja indeks tekuceg broja. U niz se
     ne moze ucitati vise od MAKS_DIM brojeva, pa se u slucaju da
     promenljiva i dostigne vrednost MAKS_DIM prekida unos novih
     brojeva. */
  int i = 0;
  while (scanf("%d", &brojevi[i]) != EOF) {
    i++;
    if (i == MAKS_DIM)
      break;
  }
  n = i;

  /* Stampa se maksimum unetog niza brojeva */
  printf("%d\n", maksimum_niza(brojevi, n));

  return 0;
}
