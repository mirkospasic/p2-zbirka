#include <stdio.h>
#include <stdlib.h>

int prvi_veci_od_nule(int niz[], int n)
{
  /* Granice pretrage */
  int l = 0, d = n - 1;
  int s;
  /* Sve dok je leva manja od desne granice */
  while (l <= d) {
    /* Racuna se sredisnja pozicija */
    s = (l + d) / 2;
    /* Ako je broj na toj poziciji veci od nule, a eventualni njegov
       prethodnik manji ili jednak nuli, pretraga je zavrsena */
    if (niz[s] > 0 && ((s > 0 && niz[s - 1] <= 0) || s == 0))
      return s;
    /* U slucaju broja manjeg ili jednakog nuli, pretrazuje se desna
       polovina niza */
    if (niz[s] <= 0)
      l = s + 1;
    /* A inace, leva polovina */
    else
      d = s - 1;
  }
  return -1;
}

#define MAX 256

int main()
{
  int niz[MAX];
  int n = 0;

  /* Unos niza */
  printf("Unesi rastuce sortiran niz celih brojeva: ");
  while (scanf("%d", &niz[n]) == 1)
    n++;

  /* Stampanje rezultata */
  printf("%d\n", prvi_veci_od_nule(niz, n));

  return 0;
}
