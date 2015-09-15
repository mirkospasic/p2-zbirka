#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Funkcija racuna zbir elemenata niza */
double zbir(double *a, int n)
{
  double s = 0;
  int i;

  for (i = 0; i < n; s += a[i++]);

  return s;
}

/* Funkcija racuna proizvod elemenata niza */
double proizvod(double a[], int n)
{
  double p = 1;

  for (; n; n--)
    p *= *a++;

  return p;
}

/* Funkcija racuna najmanji element niza */
double min(double *a, int n)
{
  /* Za najmanji element se najpre postavlja prvi element */
  double min = a[0];
  int i;

  /* Ispitujemo da li se medju ostalim elementima niza nalazi
     najmanji */
  for (i = 1; i < n; i++)
    if (a[i] < min)
      min = a[i];

  return min;
}

/* Funkcija racuna najveci element niza */
double max(double *a, int n)
{
  /* Za najveci element se najpre postavlja prvi element */
  double max = *a;

  /* Ispitujemo da li se medju ostalim elementima niza nalazi
     najveci */
  for (a++, n--; n > 0; a++, n--)
    if (*a > max)
      max = *a;

  return max;
}


int main()
{
  double a[MAX];
  int n, i;

  /* Ucitavamo dimenziju niza */
  scanf("%d", &n);

  /* Proveravamo da li je prekoraceno ogranicenje dimenzije */
  if (n <= 0 || n > MAX) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija niza.\n");
    exit(EXIT_FAILURE);
  }

  /* Unosimo elemente niza */
  for (i = 0; i < n; i++)
    scanf("%lf", a + i);

  /* Testiramo definisane funkcije */
  printf("zbir = %5.3f\n", zbir(a, n));
  printf("proizvod = %5.3f\n", proizvod(a, n));
  printf("min = %5.3f\n", min(a, n));
  printf("max = %5.3f\n", max(a, n));

  return 0;
}
