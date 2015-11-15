#include <stdio.h>
#include <stdlib.h>
#define MAX 50

/* Funkcija ucitava elemenate matrice sa standardnog ulaza */
void ucitaj_matricu(int m[][MAX], int v, int k)
{
  int i, j;
  for (i = 0; i < v; i++) {
    for (j = 0; j < k; j++) {
      scanf("%d", &m[i][j]);
    }
  }
}

/* Funkcija racuna broj negativnih elemenata u k-oj koloni matrice m
   koja ima v vrsta */
int broj_negativnih_u_koloni(int m[][MAX], int v, int k)
{
  int broj_negativnih = 0;
  int i;
  for(i=0; i<v; i++){
    if(m[i][k]<0)
    broj_negativnih++;
  }
  return broj_negativnih;
}

int max_indeks(int m[][MAX], int v, int k)
{
  int i, j;
  int broj_negativnih;
  /* Inicijalizujemo na nulu indeks kolone sa maksimalnim brojem 
     negativnih (max_indeks_kolone), kao i maksimalni broj negativnih
     elemenata u nekoj koloni (max_broj_negativnih) */
  int max_indeks_kolone = 0;
  int max_broj_negativnih = 0;
  
  for (j = 0; j < k; j++) {
    /* Racunamo broj negativnih u j-oj koloni */
    broj_negativnih = broj_negativnih_u_koloni(m, v, j);
    /* Ukoliko broj negativnih u j-toj koloni veci od trenutnog 
       maksimalnog, azuriramo trenutni maksimalni broj negativnih 
       kao i indeks kolone sa maksimalnim brojem negativnih */
    if(max_broj_negativnih < broj_negativnih ){
      max_indeks_kolone = j;
      max_broj_negativnih = broj_negativnih;
    }
  }
  return max_indeks_kolone;
}

int main() 
{
  int m[MAX][MAX];
  int v, k; 
  
  /* Ucitavanje dimenzije matrice */ 
  scanf("%d", &v); 
  if (v < 0 || v > MAX) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);  
  }
  scanf("%d", &k);
  if (k < 0 || k > MAX) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);  
  }
  /* Ucitavanje elemenata matrice */ 
  ucitaj_matricu(m, v, k);
  
  /* Pronalazenje kolone koja sadrzi najveci broj negativnih 
     elemenata i ispisivanje trazenog rezultata */ 
  printf("%d\n", max_indeks(m, v, k));
  exit(EXIT_SUCCESS);
}
