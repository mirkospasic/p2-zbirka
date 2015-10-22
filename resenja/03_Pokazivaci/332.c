#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Funkcija ucitava matricu sa ulaza */
void ucitaj_matricu(int **M, int n, int m)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &M[i][j]);
}

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
  int m, n, i, j;
  int **matrica = NULL;

  printf("Unesite broj vrsta i broj kolona matrice:\n ");
  scanf("%d %d", &n, &m);

  /* Alocira se prostor za niz pokazivaca na vrste matrice */
  matrica = (int **) malloc(n * sizeof(int *));
  if (matrica == NULL) {
    fprintf(stderr, "malloc(): Neuspela alokacija\n");
    exit(EXIT_FAILURE);
  }

  /* Alocira se prostor za svaku vrstu matrice */
  for (i = 0; i < n; i++) {
    matrica[i] = (int *) malloc(m * sizeof(int));

    if (matrica[i] == NULL) {
      fprintf(stderr, "malloc(): Neuspela alokacija\n");
      for (j = 0; j < i; j++)
        free(matrica[j]);
      free(matrica);
      exit(EXIT_FAILURE);
    }
  }

  printf("Unesite elemente matrice, vrstu po vrstu:\n");
  ucitaj_matricu(matrica, n, m);

  printf("Elementi ispod glavne dijagonale matrice:\n");
  ispisi_elemente_ispod_dijagonale(matrica, n, m);

  /* Oslobadja se dinamicki alocirana memorija za matricu. Prvo se
     oslobadja memorija rezervisana za svaku vrstu */
  for (j = 0; j < n; j++)
    free(matrica[j]);

  /* Zatim se oslobadja memorija za niz pokazivaca na vrste matrice */
  free(matrica);

  return 0;
}
