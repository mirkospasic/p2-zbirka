#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <search.h>

#define MAX 100

/* Funkcija racuna broj delilaca broja x */
int no_of_deviders(int x)
{
  int i;
  int br;

  /* Ako je argument negativan broj menjamo mu znak */
  if (x < 0)
    x = -x;
  if (x == 0)
    return 0;
  if (x == 1)
    return 1;
  /* Svaki broj veci od 1 ima bar 2 delioca, (1 i samog sebe) */
  br = 2;
  /* Sve dok je */
  for (i = 2; i < sqrt(x); i++)
    if (x % i == 0)
      /* Ako i deli x onda su delioci: i, x/i */
      br += 2;
  /* Ako je broj bas kvadrat, onda smo iz petlje izasli kada je
     i bilo bas jednako korenu od x, tada x ima jos jednog
     delioca */
  if (i * i == x)
    br++;

  return br;
}

/* Funkcija poredjenja dva cela broja po broju delilaca */
int compare_no_deviders(const void *a, const void *b)
{
  int ak = *(int *) a;
  int bk = *(int *) b;
  int n_d_a = no_of_deviders(ak);
  int n_d_b = no_of_deviders(bk);

  if (n_d_a > n_d_b)
    return 1;
  else if (n_d_a < n_d_b)
    return -1;
  else
    return 0;
}

/* Test program */
int main()
{
  size_t n;
  int i;
  int a[MAX];

  /* Unosimo dimenziju */
  printf("Uneti dimenziju niza: ");
  scanf("%ld", &n);
  if (n > MAX)
    n = MAX;

  /* Unosimo elemente niza */
  printf("Uneti elemente niza:\n");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Sortiramo niz celih brojeva prema broju delilaca */
  qsort(a, n, sizeof(int), &compare_no_deviders);

  /* Prikazujemo sortirani niz */
  printf
      ("Sortirani niz u rastucem poretku prema broju delilaca:\n");
  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  putchar('\n');

  return 0;
}
