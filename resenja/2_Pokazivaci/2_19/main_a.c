#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

int main()
{
  int **matrica = NULL;
  int n, m;
  FILE *f;

  /* Ucitavanje dimenzije matrice */
  printf("Unesite broj vrsta matrice: ");
  scanf("%d", &n);
  printf("Unesite broj kolona matrice: ");
  scanf("%d", &m);

  /* Provera dimenzija matrice */
  if (n <= 0 || m <= 0) {
    fprintf(stderr, "Greska: Neodgovarajce dimenzije matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Alokacija matrice i provera alokacije */
  matrica = alociraj_matricu(n, m);
  if (matrica == NULL) {
    fprintf(stderr, "Greska: Neuspesna alokacija matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje matrice sa standardnog ulaza */
  printf("Unesite elemente matrice po vrstama:\n");
  ucitaj_matricu(matrica, n, m);

  /* Otvaranje datoteke za upis matrice */
  if ((f = fopen("matrica.txt", "w")) == NULL) {
    fprintf(stderr, "Greska: Neuspesno otvaranje datoteke.\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Upis matrice u datoteku */
  if (upisi_matricu_u_datoteku(matrica, n, m, f) != 0) {
    fprintf(stderr, "Greska: Neuspesno upisivanje matrice u datoteku.\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Zatvaranje datoteke */
  fclose(f);

  /* Oslobadjanje memorije koju je zauzimala matrica */
  matrica = dealociraj_matricu(matrica, n);

  exit(EXIT_SUCCESS);
}
