#include <stdio.h>
#define MAX_DIM 256

/* Funkcija koja izracunava skalarni proizvod dva data vektora */
int skalarno(int a[], int b[], int n)
{
  /* Izlazak iz rekurzije: vektori su duzine 0 */
  if (n == 0)
    return 0;

  /******************************************************************
    Na osnovu resenja problema dimenzije n-1, resava se problem
    dimenzije n primenom definicije skalarnog proizvoda
    a*b = a[0]*b[0] + a[1]*b[1] +...+  a[n-2]*a[n-2] + a[n-1]*a[n-1]
    Dakle, skalarni proizvod dva vektora duzine n se dobija kada se 
    na skalarni proizvod dva vektora duzine n-1 koji se dobiju od 
    polazna dva vektora otklanjanjem poslednjih elemenata, doda 
    proizvod poslednja dva elementa polaznih vektora tj.
    skalarno(a,b,n) = skalarno(a, b, n - 1) + a[n-1]*a[n-1]
  ******************************************************************/
  else
    return skalarno(a, b, n - 1) + a[n - 1] * b[n - 1];
}

int main()
{
  int i, a[MAX_DIM], b[MAX_DIM], n;

  /* Unosi se dimenzija nizova */
  printf("Unesite dimenziju nizova:");
  scanf("%d", &n);

  /* Provera da li je dimenzija niza odgovarajuca */
  if (n < 0 || n > MAX_DIM) {
    printf("Dimenzija mora biti prirodan broj <= %d!\n", MAX_DIM);
    return 0;
  }

  /* A zatim i elementi nizova */
  printf("Unesite elemente prvog niza:");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  printf("Unesite elemente drugog niza:");
  for (i = 0; i < n; i++)
    scanf("%d", &b[i]);

  /* Ispisuje se rezultat skalarnog proizvoda dva ucitana niza */
  printf("Skalarni proizvod je %d\n", skalarno(a, b, n));

  return 0;
}
