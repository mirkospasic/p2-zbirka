#include <stdio.h>
#include <stdlib.h>
#define MAKS_DIM 100

/* Ako je n<=0, onda je suma niza jednaka nuli. Ako je n>0, onda je
   suma niza jednaka sumi prvih n-1 elementa uvecenoj za poslednji
   element niza. */
int suma_niza_1(int *a, int n)
{
  if (n <= 0)
    return 0;

  return suma_niza_1(a, n - 1) + a[n - 1];
}

/* Funkcija napisana na drugi nacin: Ako je n<=0, onda je suma niza
   jednaka nuli. Ako je n>0, suma niza je jednaka zbiru prvog
   elementa niza i sume preostalih n-1 elementa. */
int suma_niza_2(int *a, int n)
{
  if (n <= 0)
    return 0;

  return a[0] + suma_niza_2(a + 1, n - 1);
}

int main()
{
  int a[MAKS_DIM];
  int n, i = 0, ind;

  /* Ucitava se redni broj funkcije */
  printf("Unesite redni broj funkcije (1 ili 2):\n");
  scanf("%d", &ind);

  /* Ucitava se broj elemenata niza */
  printf("Unesite dimenziju niza:\n");
  scanf("%d", &n);

  /* Ucitava se n elemenata niza. */
  printf("Unesite elemente niza:\n");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Na osnovu vrednosti promenljive ind ispisuje se rezultat
     poziva funkcije suma_niza_1, ondosno suma_niza_2 */
  if (ind == 1)
    printf("Suma elemenata je %d\n", suma_niza_1(a, n));
  else if (ind == 2)
    printf("Suma elemenata je %d\n", suma_niza_2(a, n));
  else {
    fprintf(stderr,
            "Greska: Neodgovarajuci redni broj funkcije.\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
