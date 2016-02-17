#include <stdio.h>
#include <stdlib.h>

#define MAX 32

/* Funkcija izracunava najveci element na sporednoj dijagonali. Za
   elemente sporedne dijagonale vazi da je zbir indeksa vrste i
   indeksa kolone jednak n-1 */
int max_sporedna_dijagonala(int m[][MAX], int n)
{
  int i;
  int max_na_sporednoj_dijagonali = m[0][n - 1];

  for (i = 1; i < n; i++)
    if (m[i][n - 1 - i] > max_na_sporednoj_dijagonali)
      max_na_sporednoj_dijagonali = m[i][n - 1 - i];

  return max_na_sporednoj_dijagonali;
}

/* Funkcija izracunava indeks kolone najmanjeg elementa */
int indeks_min(int m[][MAX], int n)
{
  int i, j;
  int min = m[0][0], indeks_kolone = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (m[i][j] < min) {
        min = m[i][j];
        indeks_kolone = j;
      }

  return indeks_kolone;
}

/* Funkcija izracunava indeks vrste najveceg elementa */
int indeks_max(int m[][MAX], int n)
{
  int i, j;
  int max = m[0][0], indeks_vrste = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (m[i][j] > max) {
        max = m[i][j];
        indeks_vrste = i;
      }
  return indeks_vrste;
}

/* Funkcija izracunava broj negativnih elemenata matrice */
int broj_negativnih(int m[][MAX], int n)
{
  int i, j;
  int broj_negativnih = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (m[i][j] < 0)
        broj_negativnih++;

  return broj_negativnih;
}

int main(int argc, char *argv[])
{
  int m[MAX][MAX];
  int n;
  int i, j;

  /* Proverava se broj argumenata komandne linije */
  if (argc < 2) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s br_vrsta_mat.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Ucitava se broj vrsta matrice */
  n = atoi(argv[1]);

  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: Neodgovarajuci broj ");
    fprintf(stderr, "vrsta matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitava se matrica */
  printf("Unesite elemente matrice dimenzije %dx%d:\n", n, n);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &m[i][j]);

  printf("Najveci element sporedne dijagonale je %d.\n",
         max_sporedna_dijagonala(m, n));

  printf("Indeks kolone sa najmanjim elementom je %d.\n",
         indeks_min(m, n));

  printf("Indeks vrste sa najvecim elementom je %d.\n",
         indeks_max(m, n));

  printf("Broj negativnih elemenata matrice je %d.\n",
         broj_negativnih(m, n));

  exit(EXIT_SUCCESS);
}
