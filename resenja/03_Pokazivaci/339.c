#include <stdio.h>
#include <stdlib.h>

/* Funkcija ucitava elemente matrice dimenzije n x m sa standardnog
   ulaza */
void ucitaj_matricu(int **a, int n, int m)
{
  int i, j;

  printf("Unesite elemente matrice:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &a[i][j]);
}

/* Funkcija odredjuje zbir v-te vrste matrice */
int zbir_vrste(int **a, int v, int k)
{
  int i, zbir = 0;

  for (i = 0; i < k; i++)
    zbir += a[v][i];

  return zbir;
}

/* Funkcija sortira vrste matrice na osnovu zbira elemenata u vrsti
   koriscenjem selection sort algoritma */
void sortiraj_vrste(int **a, int n, int m)
{
  int i, j, k, min, tmp;
  min = 0;

  for (i = 0; i < n - 1; i++) {
    min = i;

    for (j = i + 1; j < n; j++)
      if (zbir_vrste(a, j, m) < zbir_vrste(a, min, m))
        min = j;

    /* Zamenjujemo mesta vrstama sa indeksima "min" i "i" */
    if (min != i)
      for (k = 0; k < m; k++) {
        tmp = a[i][k];
        a[i][k] = a[min][k];
        a[min][k] = tmp;
      }
  }
}

/* Funkcija ispisuje elemente matrice dimenzije n x m na standardni
   izlaz */
void ispisi_matricu(int **a, int n, int m)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      printf("%d ", a[i][j]);
    printf("\n");
  }
}

/* Funkcija alocira memoriju za matricu dimenzije n x m */
int **alociraj_memoriju(int n, int m)
{
  int i, j;
  int **a;

  a = (int **) malloc(n * sizeof(int *));
  if (a == NULL) {
    fprintf(stderr, "malloc(): neuspela alokacija!\n");
    exit(EXIT_FAILURE);
  }

  /* Za svaku vrstu matrice */
  for (i = 0; i < n; i++) {

    /* Alociramo memoriju */
    a[i] = (int *) malloc(m * sizeof(int));

    /* Proveravamo da li je doslo do greske pri alokaciji */
    if (a[i] == NULL) {
      /* Ako jeste oslobadjamo memoriju zauzetu do ovog koraka */
      for (j = 0; j < i; j++)
        free(a[i]);
      free(a);
      exit(EXIT_FAILURE);
    }
  }

  return a;
}

/* Funkcija oslobadja memoriju zauzetu matricom */
void oslobodi_memoriju(int **a, int n, int m)
{
  int i;

  for (i = 0; i < n; i++)
    free(a[i]);
  free(a);
}

int main(int argc, char *argv[])
{
  int **a;
  int n, m;

  /* citamo dimenziju matrice */
  printf("Unesite dimenzije matrice:\n");
  scanf("%d %d", &n, &m);

  /* Alociramo memoriju */
  a = alociraj_memoriju(n, m);

  /* Ucitavamo elemente matrice */
  ucitaj_matricu(a, n, m);

  /* Pozivamo funkciju koja sortira vrste matrice prema zbiru */
  sortiraj_vrste(a, n, m);

  /* Ispisujemo rezultujucu matricu */
  printf("Sortirana matrica je:\n");
  ispisi_matricu(a, n, m);

  /* oslobasamo memoriju */
  oslobodi_memoriju(a, n, m);

  /* i prekidamo sa izvrsavanjem programa */
  return 0;
}
