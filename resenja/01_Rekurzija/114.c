#include <stdio.h>
#define MAX_DIM 256

int tri_uzastopna_clana(int x, int y, int z, int a[], int n)
{
  /* Ako niz ima manje od tri elementa izlazi se iz rekurzije */
  if (n < 3)
    return 0;

  else
    return ((a[n - 3] == x) && (a[n - 2] == y)
            && (a[n - 1] == z))
        || tri_uzastopna_clana(x, y, z, a, n - 1);
}

int main()
{
  int x, y, z, a[MAX_DIM];
  int n;

  /* Ucitavaju se tri cela broja za koje se ispituje da li su
     uzastopni clanovi niza */
  printf("Unesite tri cela broja:");
  scanf("%d%d%d", &x, &y, &z);

  printf("Unesite elemente niza:");
  int i = 0;
  while (scanf("%d", &a[i]) != EOF) {
    i++;
  }
  n = i;

  if (tri_uzastopna_clana(x, y, z, a, n))
    printf("Uneti brojevi jesu uzastopni clanovi niza.\n");
  else
    printf("Uneti brojevi nisu uzastopni clanovi niza.\n");

  return 0;
}
