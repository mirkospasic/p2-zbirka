#include <stdio.h>
#include <stdlib.h>

#define MAX 32

int max_sporedna_dijagonala(int m[][MAX], int n)
{
  int i, j;
  /* Trazimo najveci element na sporednoj dijagonali. Za
     elemente sporedne dijagonale vazi da je zbir indeksa vrste
     i indeksa kolone jednak n-1. Za pocetnu vrednost maksimuma
     uzimamo element u gornjem desnom uglu */
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
  /* Za pocetnu vrednost minimuma uzimamo element u gornjem
     levom uglu */
  int min = m[0][0], indeks_kolone = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      /* Ako je tekuci element manji od minimalnog */
      if (m[i][j] < min) {
        /* cuvamo njegovu vrednost */
        min = m[i][j];
        /* i cuvamo indeks kolone u kojoj se nalazi */
        indeks_kolone = j;
      }
  return indeks_kolone;
}

/* Funkcija izracunava indeks vrste najveceg elementa */
int indeks_max(int m[][MAX], int n)
{
  int i, j;
  /* Za maksimalni element uzimamo gornji levi ugao */
  int max = m[0][0], indeks_vrste = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      /* Ako je tekuci element manji od minimalnog */
      if (m[i][j] > max) {
        /* cuvamo njegovu vrednost */
        max = m[i][j];
        /* i cuvamo indeks vrste u kojoj se nalazi */
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

  /* Proveravamo broj argumenata komandne linije */
  if (argc < 2) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s dim_matrice.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo vrednost dimenzije i proveravamo njenu korektnost 
   */
  n = atoi(argv[1]);

  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo element po element matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &m[i][j]);

  int max_sd = max_sporedna_dijagonala(m, n);
  int i_min = indeks_min(m, n);
  int i_max = indeks_max(m, n);
  int bn = broj_negativnih(m, n);

  /* Ispisujemo rezultat */
  printf("%d %d %d %d\n", max_sd, i_min, i_max, bn);

  /* Prekidamo izvrsavanje programa */
  return 0;
}
