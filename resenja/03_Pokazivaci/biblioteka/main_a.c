#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

int main()
{
  int **matrica = NULL;
  int n, m;
  FILE *f;

  /* Ucitavanje dimenzije matrice */
  printf("Unesi broj vrsta matrice: ");
  scanf("%d", &n);
  printf("Unesi broj kolona matrice: ");
  scanf("%d", &m);

  /* Provera dimenzija matrice */
  if (n <= 0 || m <= 0) {
    fprintf(stderr, "Neodgovarajce dimenzije matrice\n");
    exit(EXIT_FAILURE);
  }

  /* Alokacija matrice i provera alokacije */
  matrica = alociraj_matricu(n, m);
  if (matrica == NULL) {
    fprintf(stderr, "Neuspesna alokacija matrice\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje matrice sa standardnog ulaza */
  printf("Unesi elemente matrice po vrstama:\n");
  ucitaj_matricu(matrica, n, m);

  /* Otvaranje fajla za upis matrice */
  if ((f = fopen("matrica.txt", "w")) == NULL) {
    fprintf(stderr, "fopen() error\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Upis matrice u fajl */
  if (upisi_matricu_u_datoteku(matrica, n, m, f) != 0) {
    fprintf(stderr, "Neuspesno upisivanje matrice u datoteku\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Zatvaranje fajla */
  fclose(f);

  /* Dealokacija matrice */
  matrica = dealociraj_matricu(matrica, n);

  return 0;
}
