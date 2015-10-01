#include <stdio.h>
#include <stdlib.h>

#define MAX 32

/* Funkcija ucitava elemente kvadratne matrice sa standardnog ulaza */
void ucitaj_matricu(int m[][MAX], int n)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &m[i][j]);
}

/* Funkcija ispisuje elemente kvadratne matrice na standardni izlaz */
void ispisi_matricu(int m[][MAX], int n)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", m[i][j]);
    printf("\n");
  }
}

/* Funkcija proverava da li je zadata matrica ortonormirana */
int ortonormirana(int m[][MAX], int n)
{
  int i, j, k;
  int proizvod;

  /* Proveravamo uslov normiranosti, odnosno da li je proizvod svake
     vrste matrice sa samom sobom jednak jedinici */
  for (i = 0; i < n; i++) {

    /* Izracunavamo skalarni proizvod vrste sa samom sobom */
    proizvod = 0;

    for (j = 0; j < n; j++)
      proizvod += m[i][j] * m[i][j];

    /* Ako proizvod bar jedne vrste nije jednak jedinici, odmah
       zakljucujemo da matrica nije normirana */
    if (proizvod != 1)
      return 0;
  }

  /* Proveravamo uslov ortogonalnosti, odnosno da li je proizvod dve
     bilo koje razlicite vrste matrice jednak nuli */
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {

      /* Izracunavamo skalarni proizvod */
      proizvod = 0;

      for (k = 0; k < n; k++)
        proizvod += m[i][k] * m[j][k];

      /* Ako proizvod dve bilo koje razlicite vrste nije jednak nuli, 
         odmah zakljucujemo da matrica nije ortogonalna */
      if (proizvod != 0)
        return 0;
    }
  }

  /* Ako su oba uslova ispunjena, vracamo jedinicu kao rezultat */
  return 1;
}

int main()
{
  int A[MAX][MAX];
  int n;

  /* Ucitavamo vrednost dimenzije i proveravamo njenu korektnost */
  scanf("%d", &n);

  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo matricu */
  ucitaj_matricu(A, n);

  /* Ispisujemo rezultat rada funkcije */
  if (ortonormirana(A, n))
    printf("da\n");
  else
    printf("ne\n");

  return 0;
}
