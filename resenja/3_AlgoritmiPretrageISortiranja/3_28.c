#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

/* Funkcija koja odredjuje zbir v-te vrste matrice a koja ima m
   kolona */
int zbir_vrste(int **a, int v, int m)
{
  int i, zbir = 0;

  for (i = 0; i < m; i++) {
    zbir += a[v][i];
  }
  return zbir;
}

/* Funkcija koja sortira vrste matrice (pokazivace na vrste) na
   osnovu zbira koriscenjem selection sort algoritma */
void sortiraj_vrste(int **a, int n, int m)
{
  int i, j, min;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++) {
      if (zbir_vrste(a, j, m) < zbir_vrste(a, min, m)) {
        min = j;
      }
    }
    if (min != i) {
      int *tmp;
      tmp = a[i];
      a[i] = a[min];
      a[min] = tmp;
    }
  }
}

int main(int argc, char *argv[])
{
  int **a;
  int n, m;

  /* Unos dimenzija matrice */
  printf("Unesite dimenzije matrice: ");
  scanf("%d %d", &n, &m);

  /* Alokacija memorije */
  a = alociraj_matricu(n, m);
  if (a == NULL) {
    fprintf(stderr, "Neuspesna alokacija matrice\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje elementa matrice */
  printf("Unesite elemente matrice po vrstama:\n");
  ucitaj_matricu(a, n, m);

  /* Poziv funkcije koja sortira vrste matrice prema zbiru */
  sortiraj_vrste(a, n, m);

  /* Ispis rezultujuce matrice */
  printf("Sortirana matrica je:\n");
  ispisi_matricu(a, n, m);

  /* Oslobadjanje memorije */
  a = dealociraj_matricu(a, n);

  return 0;
}
