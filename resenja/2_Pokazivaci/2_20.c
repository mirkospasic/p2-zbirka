#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrica.h"

/* Funkcija ispisuje elemente matrice ispod glavne dijagonale */
void ispisi_elemente_ispod_dijagonale(int **M, int n, int m)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j <= i; j++)
      printf("%d ", M[i][j]);
    printf("\n");
  }
}

int main()
{
  int m, n;
  int **matrica = NULL;

  printf("Unesite broj vrsta i broj kolona:\n ");
  scanf("%d %d", &n, &m);

  /* Alocira se matrica */
  matrica = alociraj_matricu(n, m);
  /* Provera alokacije */
  if (matrica == NULL) {
    fprintf(stderr, "Greska: Neuspesna alokacija matrice.\n");
    exit(EXIT_FAILURE);
  }

  printf("Unesite elemente matrice po vrstama:\n");
  ucitaj_matricu(matrica, n, m);

  printf("Elementi ispod glavne dijagonale matrice:\n");
  ispisi_elemente_ispod_dijagonale(matrica, n, m);

  /* Oslobadjanje memorije */
  matrica = dealociraj_matricu(matrica, n);

  exit(EXIT_SUCCESS);
}
