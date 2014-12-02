#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i, j;

  /* Pokazivac na dinamicki alociran niz pokazivaca na vrste matrice */
  double **A = NULL;

  /* Broj vrsta i broj kolona */
  int n = 0, m = 0;

  /* Trag matice */
  double trag = 0;

  printf("Unesite broj vrsta i broj kolona matrice:\n ");
  scanf("%d%d", &n, &m);

  /* Dinamicki se alocira prostor za n pokazivaca na double */
  A = malloc(sizeof(double *) * n);

  /* Provera se da li je doslo do greske pri alokaciji */
  if (A == NULL) {
    fprintf(stderr, "malloc(): ");
    fprintf(stderr, "greska pri alokaciji memorije.\n");
    exit(EXIT_FAILURE);
  }

  /* Dinamicki se alocira prostor za elemente u vrstama */
  for (i = 0; i < n; i++) {
    A[i] = malloc(sizeof(double) * m);

    /* Ukoliko je alokacija neuspesna, pre zavrsetka programa
       potrebno je osloboditi svih i-1 prethodno alociranih vrsta, i
       alociran niz pokazivaca */
    if (A[i] == NULL) {
      for (j = 0; j < i; j++)
        free(A[j]);
      free(A);
      exit(EXIT_FAILURE);
    }
  }

  printf("Unesite elemente matrice, vrstu po vrstu:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%lf", &A[i][j]);

  /* Izracunava se trag matrice, odnosno suma elemenata na glavnoj
     dijagonali */
  trag = 0.0;

  for (i = 0; i < n; i++)
    trag += A[i][i];

  printf("Trag unete matrice je %.2f.\n", trag);

  /* Oslobadja se prostor rezervisan za svaku vrstu */
  for (j = 0; j < n; j++)
    free(A[j]);

  /* Oslobadja se memorija za niz pokazivaca na vrste */
  free(A);

  return 0;
}
