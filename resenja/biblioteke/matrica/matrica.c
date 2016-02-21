#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

int **alociraj_matricu(int n, int m)
{
  int **matrica = NULL;
  int i, j;

  /* Alocira se prostor za niz vrsta matrice */
  matrica = (int **) malloc(n * sizeof(int *));
  /* Ako alokacija nije prosla uspesno, povratna vrednost funkcije
     ce biti NULL, sto mora biti provereno u main funkciji */
  if (matrica == NULL)
    return NULL;

  /* Alocira se prostor za svaku vrstu matrice */
  for (i = 0; i < n; i++) {
    matrica[i] = (int *) malloc(m * sizeof(int));
    /* Ako alokacija nije prosla uspesno, oslobadjaju se svi
       prethodno alocirani resursi, i povratna vrednost je NULL */
    if (matrica[i] == NULL) {
      for (j = 0; j < i; j++)
        free(matrica[j]);
      free(matrica);
      return NULL;
    }
  }
  return matrica;
}

int **alociraj_kvadratnu_matricu(int n)
{
  /* Alociranje matrice dimenzije n x n */
  return alociraj_matricu(n, n);
}

int **dealociraj_matricu(int **matrica, int n)
{
  int i;
  /* Oslobadja se prostor rezervisan za svaku vrstu */
  for (i = 0; i < n; i++)
    free(matrica[i]);
  /* Oslobadja se memorija za niz pokazivaca na vrste */
  free(matrica);

  /* Matrica postaje prazna, tj. nealocirana */
  return NULL;
}

void ucitaj_matricu(int **matrica, int n, int m)
{
  int i, j;
  /* Elementi matrice se ucitavaju po vrstama */
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &matrica[i][j]);
}

void ucitaj_kvadratnu_matricu(int **matrica, int n)
{
  /* Ucitavanje matrice n x n */
  ucitaj_matricu(matrica, n, n);
}

void ispisi_matricu(int **matrica, int n, int m)
{
  int i, j;
  /* Ispis po vrstama */
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      printf("%d ", matrica[i][j]);
    printf("\n");
  }
}

void ispisi_kvadratnu_matricu(int **matrica, int n)
{
  /* Ispis matrice n x n */
  ispisi_matricu(matrica, n, n);
}

int ucitaj_matricu_iz_datoteke(int **matrica, int n, int m, FILE * f)
{
  int i, j;
  /* Elementi matrice se ucitavaju po vrstama */
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      /* Ako je nemoguce ucitati sledeci element, povratna vrednost
         funkcije je 1, kao indikator neuspesnog ucitavanja */
      if (fscanf(f, "%d", &matrica[i][j]) != 1)
        return 1;

  /* Uspesno ucitana matrica */
  return 0;
}

int ucitaj_kvadratnu_matricu_iz_datoteke(int **matrica, int n,
                                         FILE * f)
{
  /* Ucitavanje matrice n x n iz datoteke */
  return ucitaj_matricu_iz_datoteke(matrica, n, n, f);
}

int upisi_matricu_u_datoteku(int **matrica, int n, int m, FILE * f)
{
  int i, j;
  /* Ispis po vrstama */
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      /* Ako je nemoguce ispisati sledeci element, povratna vrednost
         funkcije je 1, kao indikator neuspesnog ispisa */
      if (fprintf(f, "%d ", matrica[i][j]) <= 0)
        return 1;
    fprintf(f, "\n");
  }

  /* Uspesno upisana matrica */
  return 0;
}

int upisi_kvadratnu_matricu_u_datoteku(int **matrica, int n,
                                       FILE * f)
{
  /* Ispis matrice n x n u datoteku */
  return upisi_matricu_u_datoteku(matrica, n, n, f);
}
