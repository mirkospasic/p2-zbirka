#include <stdio.h>
#include <stdlib.h>

/* Funkcija koja ucitava elemente matrice a dimenzije nxm sa
   standardnog ulaza */
void ucitaj_matricu(int **a, int n, int m)
{
  printf("Unesite elemente matrice po vrstama:\n");
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }
}

/* Funkcija koja odredjuje zbir v-te vrste matrice a koja ima m
   kolona */
int zbir_vrste(int **a, int v, int m)
{
  int i, zbir = 0;

  for (i = 0; i < m; i++) {
    zbir += a[v][i];
  }
  return zbir;
}

/* Funkcija koja sortira vrste matrice (pokazivace na vrste) na
   osnovu zbira koriscenjem selection sort algoritma */
void sortiraj_vrste(int **a, int n, int m)
{
  int i, j, min;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++) {
      if (zbir_vrste(a, j, m) < zbir_vrste(a, min, m)) {
        min = j;
      }
    }
    if (min != i) {
      int *tmp;
      tmp = a[i];
      a[i] = a[min];
      a[min] = tmp;
    }
  }
}

/* Funkcija koja ispisuje elemente matrice a dimenzije nxm na
   standardni izlaz */
void ispisi_matricu(int **a, int n, int m)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}

/* Funkcija koja alocira memoriju za matricu dimenzija nxm */
int **alociraj_memoriju(int n, int m)
{
  int i, j;
  int **a;

  a = (int **) malloc(n * sizeof(int *));
  if (a == NULL) {
    fprintf(stderr, "Problem sa alokacijom memorije!\n");
    exit(EXIT_FAILURE);
  }
  /* Za svaku vrstu ponaosob */
  for (i = 0; i < n; i++) {
    /* Alocira se memorija */
    a[i] = (int *) malloc(m * sizeof(int));
    /* Proverava se da li je doslo do greske prilikom alokacije */
    if (a[i] == NULL) {
      /* Ako jeste, ispisuje se poruka */
      fprintf(stderr, "Problem sa alokacijom memorije!\n");
      /* I oslobadja memorija zauzeta do ovog koraka */
      for (j = 0; j < i; j++) {
        free(a[i]);
      }
      free(a);
      exit(EXIT_FAILURE);
    }
  }

  return a;
}

/* Funkcija koja oslobadja memoriju zauzetu matricom a dimenzije nxm */
void oslobodi_memoriju(int **a, int n, int m)
{
  int i;
  for (i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

int main(int argc, char *argv[])
{
  int **a;
  int n, m;

  /* Unos dimenzija matrice */
  printf("Unesite dimenzije matrice: ");
  scanf("%d %d", &n, &m);

  /* Alokacija memorije */
  a = alociraj_memoriju(n, m);

  /* Ucitavanje elementa matrice */
  ucitaj_matricu(a, n, m);

  /* Poziv funkcije koja sortira vrste matrice prema zbiru */
  sortiraj_vrste(a, n, m);

  /* Ispis rezultujuce matrice */
  printf("Sortirana matrica je:\n");
  ispisi_matricu(a, n, m);

  /* Oslobadjanje memorije */
  oslobodi_memoriju(a, n, m);

  return 0;
}
