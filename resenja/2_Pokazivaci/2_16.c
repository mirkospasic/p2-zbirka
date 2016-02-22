#include <stdio.h>
#include <stdlib.h>

#define KORAK 10

int main()
{
  /* Adresa prvog alociranog bajta */
  int *a = NULL;

  /* Velicina alocirane memorije */
  int alocirano;

  /* Broj elemenata niza */
  int n;

  /* Broj koji se ucitava sa ulaza */
  int x;
  int i;
  int *b = NULL;
  char realokacija;

  /* Inicijalizacija */
  alocirano = n = 0;

  printf("Unesite zeljeni nacin realokacije (M ili R):\n");
  scanf("%c", &realokacija);

  printf("Unesite brojeve, nulu za kraj:\n");
  scanf("%d", &x);

  while (x != 0) {
    if (n == alocirano) {
      alocirano = alocirano + KORAK;

      if (realokacija == 'M') {
        /* Vrsi se realokacija memorije sa novom velicinom */
        b = (int *) malloc(alocirano * sizeof(int));

        if (b == NULL) {
          fprintf(stderr,
                  "Greska: Neuspesna alokacija memorije.\n");
          free(a);
          exit(EXIT_FAILURE);
        }

        /* Svih n elemenata koji pocinju na adresi a prepisuju se
           na novu aderesu b */
        for (i = 0; i < n; i++)
          b[i] = a[i];

        free(a);

        /* Promenljivoj a dodeljuje se adresa pocetka novog, veceg
           bloka cija je adresa prilikom alokacije zapamcena u
           promenljivoj b */
        a = b;
      } else if (realokacija == 'R') {

        /* Zbog funkcije realloc je neophodno da i u prvoj
           iteraciji "a" bude inicijalizovano na NULL */
        a = (int *) realloc(a, alocirano * sizeof(int));
        if (a == NULL) {
          fprintf(stderr,
                  "Greska: Neupesna realokacija memorije.\n");
          exit(EXIT_FAILURE);
        }
      }
    }
    a[n++] = x;
    scanf("%d", &x);
  }
  printf("Niz u obrnutom poretku je: ");
  for (n--; n >= 0; n--)
    printf("%d ", a[n]);
  printf("\n");

  /* Oslobadja se dinamicki alocirana memorija */
  free(a);

  exit(EXIT_SUCCESS);
}
