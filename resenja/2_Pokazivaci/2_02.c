#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Funkcija izracunava zbir elemenata niza */
double zbir(double *a, int n)
{
  double s = 0;
  int i;

  for (i = 0; i < n; s += *(a + i++));

  return s;
}

/* Funkcija izracunava proizvod elemenata niza */
double proizvod(double *a, int n)
{
  double p = 1;

  for (; n; n--)
    p *= (*(a + n - 1));

  return p;
}

/* Funkcija odredjuje minimalni element niza */
double min(double *a, int n)
{
  /* Na pocetku, minimalni element je prvi element */
  double min = *a;
  int i;

  /* Ispituje se da li se medju ostalim elementima niza nalazi
     minimalni */
  for (i = 1; i < n; i++)
    if (*(a + i) < min)
      min = *(a + i);

  return min;
}

/* Funkcija odredjuje maksimalni element niza */
double max(double *a, int n)
{
  /* Na pocetku, maksimalni element je prvi element */
  double max = *a;

  /* Ispituje se da li se medju ostalim elementima niza nalazi
     maksimalni */
  for (a++, n--; n > 0; a++, n--)
    if (*a > max)
      max = *a;

  return max;
}

int main()
{
  double a[MAX];
  int n, i;

  printf("Unesite dimenziju niza: ");
  scanf("%d", &n);

  /* Proverava se da li je doslo do prekoracenja ogranicenja
     dimenzije */
  if (n <= 0 || n > MAX) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija niza.\n");
    exit(EXIT_FAILURE);
  }

  printf("Unesite elemente niza:\n");
  for (i = 0; i < n; i++)
    scanf("%lf", a + i);

  /* Vrsi se testiranje definisanih funkcija */
  printf("Zbir elemenata niza je %5.3f.\n", zbir(a, n));
  printf("Proizvod elemenata niza je %5.3f.\n", proizvod(a, n));
  printf("Minimalni element niza je %5.3f.\n", min(a, n));
  printf("Maksimalni element niza je %5.3f.\n", max(a, n));

  exit(EXIT_SUCCESS);
}
