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

/* Funkcija proverava da li je zadata matrica ortonormirana, odnosno, 
   da li je normirana i ortogonalna. Matrica je normirana ako je
   proizvod svake vrste matrice sa samom sobom jednak jedinici.
   Matrica je ortogonalna, ako je proizvod dve bilo koje razlicite
   vrste matrice jednak nuli */
int ortonormirana(int m[][MAX], int n)
{
  int i, j, k;
  int proizvod;

  /* Ispituje se uslov normiranosti */
  for (i = 0; i < n; i++) {
    proizvod = 0;

    for (j = 0; j < n; j++)
      proizvod += m[i][j] * m[i][j];

    if (proizvod != 1)
      return 0;
  }

  /* Ispituje se uslov ortogonalnosti */
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {

      proizvod = 0;

      for (k = 0; k < n; k++)
        proizvod += m[i][k] * m[j][k];

      if (proizvod != 0)
        return 0;
    }
  }

  /* Ako su oba uslova ispunjena, matrica je ortonormirana */
  return 1;
}

int main()
{
  int A[MAX][MAX];
  int n;

  printf("Unesite dimenziju matrice: ");
  scanf("%d", &n);

  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  printf("Unesite elemente matrice, vrstu po vrstu:\n");
  ucitaj_matricu(A, n);

  printf("Matrica %s ortonormirana.\n",
         ortonormirana(A, n) ? "je" : "nije");

  exit(EXIT_SUCCESS);
}
