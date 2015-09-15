#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i, j;

  /* Pokazivac na dinamicki alociran niz pokazivaca na vrste
     matrice */
  double **A = NULL;

  /* Broj vrsta i broj kolona */
  int n = 0, m = 0;

  /* Trag matice */
  double trag = 0;

  /* Unosimo dimenzije matrice */
  scanf("%d%d", &n, &m);

  /* Dinamicki alociramo prostor za n pokazivaca na double */
  A = malloc(sizeof(double *) * n);

  /* Proveramo da li je doslo do greske pri alokaciji */
  if (A == NULL) {
    fprintf(stderr, "malloc(): ");
    fprintf(stderr, "greska pri alokaciji memorije.\n");
    exit(EXIT_FAILURE);
  }

  /* Dinamicki alociramo prostor za elemente u vrstama */
  for (i = 0; i < n; i++) {
    A[i] = malloc(sizeof(double) * m);

    if (A[i] == NULL) {
      /* Alokacija je neuspesna. Pre zavrsetka programa moramo
         da oslobodimo svih i-1 prethodno alociranih vrsta, i
         alociran niz pokazivaca */
      for (j = 0; j < i; j++)
        free(A[j]);
      free(A);

      exit(EXIT_FAILURE);
    }
  }

  /* Unosimo sa standardnog ulaza brojeve u matricu. Popunjavamo 
     vrstu po vrstu */
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%lf", &A[i][j]);

  /* Racunamo trag matrice, odnosno sumu elemenata na glavnoj
     dijagonali */
  trag = 0.0;

  for (i = 0; i < n; i++)
    trag += A[i][i];

  printf("%.2f\n", trag);

  /* Oslobadjamo prostor rezervisan za svaku vrstu */
  for (j = 0; j < n; j++)
    free(A[j]);

  /* Oslobadjamo memoriju za niz pokazivaca na vrste */
  free(A);

  return 0;
}
