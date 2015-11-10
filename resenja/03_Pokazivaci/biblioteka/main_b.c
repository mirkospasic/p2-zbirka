#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

int main(int argc, char **argv)
{
  int **matrica = NULL;
  int n;
  FILE *f;

  /* Provera argumenata komandne linije */
  if (argc != 2) {
    fprintf(stderr, "Koriscenje programa: %s datoteka\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje fajla za citanje */
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "fopen() error\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje dimenzije matrice */
  if (fscanf(f, "%d", &n) != 1) {
    fprintf(stderr, "Neispravan pocetak fajla\n");
    exit(EXIT_FAILURE);
  }

  /* Provera dimenzije matrice */
  if (n <= 0) {
    fprintf(stderr, "Neodgovarajca dimenzija matrice\n");
    exit(EXIT_FAILURE);
  }

  /* Alokacija matrice i provera alokacije */
  matrica = alociraj_kvadratnu_matricu(n);
  if (matrica == NULL) {
    fprintf(stderr, "Neuspesna alokacija matrice\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje matrice iz datoteke */
  if (ucitaj_kvadratnu_matricu_iz_datoteke(matrica, n, f) != 0) {
    fprintf(stderr, "Neuspesno ucitavanje matrice iz datoteke\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Zatvaranje fajla */
  fclose(f);

  /* Ispis matrice na standardnom izlazu */
  ispisi_kvadratnu_matricu(matrica, n);

  /* Dealokacija matrice */
  matrica = dealociraj_matricu(matrica, n);

  return 0;
}
