#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <search.h>

#define MAX 100

/* Funkcija racuna broj delilaca broja x */
int broj_delilaca(int x)
{
  int i;
  int br;

  /* Negativni brojevi imaju isti broj delilaca kao i pozitivni */
  if (x < 0)
    x = -x;
  if (x == 0)
    return 0;
  if (x == 1)
    return 1;
  /* Svaki broj veci od 1 ima bar 2 delioca, (1 i samog sebe) */
  br = 2;
  for (i = 2; i < sqrt(x); i++)
    if (x % i == 0)
      /* Ako i deli x onda su delioci: i, x/i */
      br += 2;
  /* Ako je broj x bas kvadrat, onda se iz petlje izaslo kada je
     promenljiva i bila bas jednaka korenu od x, i tada broj x ima
     jos jednog delioca */
  if (i * i == x)
    br++;

  return br;
}

/* Funkcija poredjenja dva cela broja po broju delilaca */
int poredi_po_broju_delilaca(const void *a, const void *b)
{
  int ak = *(int *) a;
  int bk = *(int *) b;
  int n_d_a = broj_delilaca(ak);
  int n_d_b = broj_delilaca(bk);

  return n_d_a - n_d_b;
}

int main()
{
  size_t n;
  int i;
  int a[MAX];

  /* Unos dimenzije */
  printf("Uneti dimenziju niza: ");
  scanf("%ld", &n);
  if (n > MAX)
    n = MAX;

  /* Unos elementa niza */
  printf("Uneti elemente niza:\n");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Sortiranje niza celih brojeva prema broju delilaca */
  qsort(a, n, sizeof(int), &poredi_po_broju_delilaca);

  /* Prikaz sortiranog niza */
  printf("Sortirani niz u rastucem poretku prema broju delilaca:\n");
  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  putchar('\n');

  return 0;
}
