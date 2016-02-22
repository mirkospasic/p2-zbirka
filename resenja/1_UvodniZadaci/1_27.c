#include <stdio.h>
#define MAKS_DIM 256

/* Funkcija koja proverava da li su tri zadata broja uzastopni
   clanovi niza */
int tri_uzastopna_clana(int x, int y, int z, int a[], int n)
{
  /* Ako niz ima manje od tri elementa izlazi se iz rekurzije i
     vraca se 0 jer nije ispunjeno da su x, y i z uzastopni clanovi
     niza */
  if (n < 3)
    return 0;

  /* Da bi bilo ispunjeno da su x, y i z uzastopni clanovi niza a
     dovoljno je da su oni poslednja tri clana niza ili da se oni
     rekuzivno tri uzastopna clana niza a bez poslednjeg elementa */
  return ((a[n - 3] == x) && (a[n - 2] == y) && (a[n - 1] == z))
      || tri_uzastopna_clana(x, y, z, a, n - 1);
}

int main()
{
  int x, y, z, a[MAKS_DIM], n;

  /* Ucitavaju se tri cela broja za koje se ispituje da li su
     uzastopni clanovi niza */
  printf("Unesite tri cela broja:");
  scanf("%d%d%d", &x, &y, &z);

  /* Sve dok se ne stigne do kraja ulaza, brojeve se ucitavaju u
     niz. Promenljiva i predstavlja indeks tekuceg broja. U niz se
     ne moze ucitati vise od MAKS_DIM brojeva, pa se u slucaju da
     promenljiva i dostigne vrednost MAKS_DIM prekida unos novih
     brojeva. */
  printf("Unesite elemente niza:");
  int i = 0;
  while (scanf("%d", &a[i]) != EOF) {
    i++;
    if (i == MAKS_DIM)
      break;
  }
  n = i;

  /* Na osnovu rezultata poziva funkcije tri_uzastopna_clana
     ispisuje se odgovarajuca poruka */
  if (tri_uzastopna_clana(x, y, z, a, n))
    printf("Uneti brojevi jesu uzastopni clanovi niza.\n");
  else
    printf("Uneti brojevi nisu uzastopni clanovi niza.\n");

  return 0;
}
