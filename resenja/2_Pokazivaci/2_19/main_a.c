#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

int main()
{
  int **matrica = NULL;
  int n, m;
  FILE *f;

  /* Ucitava se broj vrsta i broj kolona matrice */
  printf("Unesite broj vrsta matrice: ");
  scanf("%d", &n);
  printf("Unesite broj kolona matrice: ");
  scanf("%d", &m);

  /* Provera dimenzija matrice */
  if (n <= 0 || m <= 0) {
    fprintf(stderr,
            "Greska: Broj vrsta i broj kolona ne mogu biti negativni brojevi.\n");
    exit(EXIT_FAILURE);
  }

  /* Rezervise se memorijski prostor za matricu i proverava se da
     li je memorijski prostor uspesno rezervisan */
  matrica = alociraj_matricu(n, m);
  if (matrica == NULL) {
    fprintf(stderr, "Greska: Neuspesna alokacija matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitava se matrica sa standardnog ulaza */
  printf("Unesite elemente matrice po vrstama:\n");
  ucitaj_matricu(matrica, n, m);

  /* Otvara se datoteka za upis matrice */
  if ((f = fopen("matrica.txt", "w")) == NULL) {
    fprintf(stderr, "Greska: Neuspesno otvaranje datoteke.\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Upis matrice u datoteku */
  if (upisi_matricu_u_datoteku(matrica, n, m, f) != 0) {
    fprintf(stderr,
            "Greska: Neuspesno upisivanje matrice u datoteku.\n");
    matrica = dealociraj_matricu(matrica, n);
    exit(EXIT_FAILURE);
  }

  /* Zatvara se datoteka */
  fclose(f);

  /* Oslobadja se memorija koju je zauzimala matrica */
  matrica = dealociraj_matricu(matrica, n);

  exit(EXIT_SUCCESS);
}
