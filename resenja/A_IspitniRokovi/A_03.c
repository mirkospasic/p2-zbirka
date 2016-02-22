#include <stdio.h>
#include <stdlib.h>
#define MAKS 50

/* Funkcija ucitava elemenate matrice sa standardnog ulaza */
void ucitaj_matricu(int m[][MAKS], int v, int k)
{
  int i, j;
  for (i = 0; i < v; i++) {
    for (j = 0; j < k; j++) {
      scanf("%d", &m[i][j]);
    }
  }
}

/* Funkcija racuna broj negativnih elemenata u k-oj koloni matrice
   m koja ima v vrsta */
int broj_negativnih_u_koloni(int m[][MAKS], int v, int k)
{
  int broj_negativnih = 0;
  int i;
  for (i = 0; i < v; i++) {
    if (m[i][k] < 0)
      broj_negativnih++;
  }
  return broj_negativnih;
}

/* Funkcija vraca indeks kolone matrice m u kojoj se nalazi najvise
   negativnih elemenata */
int maks_indeks(int m[][MAKS], int v, int k)
{
  int j;
  int broj_negativnih;
  /* Inicijalizacija na nulu indeksa kolone sa maksimalnim brojem
     negativnih (maks_indeks_kolone), kao i maksimalnog broja
     negativnih elemenata u nekoj koloni (maks_broj_negativnih) */
  int maks_indeks_kolone = 0;
  int maks_broj_negativnih = 0;

  for (j = 0; j < k; j++) {
    /* Racuna se broj negativnih u j-oj koloni */
    broj_negativnih = broj_negativnih_u_koloni(m, v, j);
    /* Ukoliko broj negativnih u j-oj koloni veci od trenutnog
       maksimalnog, azurira se trenutni maksimalni broj negativnih
       kao i indeks kolone sa maksimalnim brojem negativnih */
    if (maks_broj_negativnih < broj_negativnih) {
      maks_indeks_kolone = j;
      maks_broj_negativnih = broj_negativnih;
    }
  }
  return maks_indeks_kolone;
}

int main()
{
  int m[MAKS][MAKS];
  int v, k;

  /* Ucitava se broj vrsta matrice */
  scanf("%d", &v);

  /* Proverava se validnost broja vrsta */
  if (v < 0 || v > MAKS) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitava se broj kolona matrice */
  scanf("%d", &k);

  /* Proverava se validnost broja kolona */
  if (k < 0 || k > MAKS) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
  /* Ucitaju se elementi matrice */
  ucitaj_matricu(m, v, k);

  /* Pronalazi se kolona koja sadrzi najveci broj negativnih
     elemenata i ispisuje se rezultat */
  printf("%d\n", maks_indeks(m, v, k));

  exit(EXIT_SUCCESS);
}
