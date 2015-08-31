#include <stdio.h>
#include <stdlib.h>

int prvi_veci_od_nule(int niz[], int n)
{
  /* Granice pretrage */
  int l = 0, d = n - 1;
  int s;
  /* Sve dok je leva manja od desne granice */
  while (l <= d) {
    /* Racunamo sredisnju poziciju */
    s = (l + d) / 2;
    /* Ako je broj na toj poziciji veci od nule a eventualni
       njegov prethodnik manji ili jednak nuli */
    if (niz[s] > 0 && ((s > 0 && niz[s - 1] <= 0) || s == 0))
      return s;
    /* Pretrazujemo desnu polovinu niza */
    if (niz[s] <= 0)
      l = s + 1;
    /* Pretrazujemo levu polovinu binarnog zapisa */
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
