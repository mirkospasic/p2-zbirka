#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 100

/* Deklarisemo funkcije koje cemo kasnije da definisemo */
double euklidska_norma(int M[][MAX], int n);
int trag(int M[][MAX], int n);
int gornja_vandijagonalna_norma(int M[][MAX], int n);

int main()
{
  int A[MAX][MAX];
  int i, j, n;

  /* Unosimo dimenziju kvadratne matrice */
  scanf("%d", &n);

  /* Proveravamo da li je prekoraceno ogranicenje */
  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Popunjavamo vrstu po vrstu matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &A[i][j]);

  /* Ispis elemenata matrice koriscenjem indeksne sintakse. Ispis
     vrsimo vrstu po vrstu */
  for (i = 0; i < n; i++) {
    /* Ispisujemo elemente i-te vrste */
    for (j = 0; j < n; j++)
      printf("%d ", A[i][j]);
    printf("\n");
  }

  /* Ispis elemenata matrice koriscenjem pokazivacke sintakse. Kod
     ovako definisane matrice, elementi su uzastopno smesteni u
     memoriju, kao na traci. To znaci da su svi elementi prve vrste
     redom smesteni jedan iza drugog. Odmah iza poslednjeg elementa
     prve vrste smesten je prvi element druge vrste za kojim slede
     svi elementi te vrste i tako dalje redom */
  /* 
     for( i = 0; i<n; i++) { for ( j=0 ; j<n; j++) printf("%d ",
     *(*(A+i)+j)); printf("\n"); } */

  int tr = trag(A, n);
  printf("trag = %d\n", tr);

  printf("euklidska norma = %.2f\n", euklidska_norma(A, n));
  printf("vandijagonalna norma = %d\n",
         gornja_vandijagonalna_norma(A, n));

  return 0;
}

/* Definisemo funkcije koju smo ranije deklarisali */

/* Funkcija izracunava trag matrice */
int trag(int M[][MAX], int n)
{
  int trag = 0, i;
  for (i = 0; i < n; i++)
    trag += M[i][i];
  return trag;
}

/* Funkcija izracunava euklidsku normu matrice */
double euklidska_norma(int M[][MAX], int n)
{
  double norma = 0.0;
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      norma += M[i][j] * M[i][j];

  return sqrt(norma);
}

/* Funkcija izracunava gornju vandijagonalnu normu matrice */
int gornja_vandijagonalna_norma(int M[][MAX], int n)
{
  int norma = 0;
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++)
      norma += abs(M[i][j]);
  }

  return norma;
}
