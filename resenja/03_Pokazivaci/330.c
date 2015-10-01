#include <stdio.h>
#include <stdlib.h>
#define KORAK 10

int main(void)
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

  /* Inicijalizacija */
  alocirano = n = 0;

  printf("Unesite brojeve, nulu za kraj:\n");
  scanf("%d", &x);

  while (x != 0) {
    if (n == alocirano) {
      alocirano = alocirano + KORAK;

      /* Vrsi se realokacija memorije sa novom velicinom */
      /* Resenje sa funkcijom malloc() */
      b = (int *) malloc(alocirano * sizeof(int));

      if (b == NULL) {
        fprintf(stderr, "malloc(): ");
        fprintf(stderr, "greska pri alokaciji memorije.\n");
        free(a);
        exit(EXIT_FAILURE);
      }

      /* Svih n elemenata koji pocinju na adresi a prepisujemo na
         novu aderesu b */
      for (i = 0; i < n; i++)
        b[i] = a[i];

      free(a);

      /* Promenljivoj a dodeljuje se adresa pocetka novog, veceg
         bloka koji je prilikom alokacije zapamcen u promenljivoj b */
      a = b;

      /********************************************************
        Resenje sa funkcijom realloc()

        Zbog funkcije realloc je neophodno da i u prvoj iteraciji
        "a" bude inicijalizovano na NULL

        a = (int*) realloc(a,alocirano*sizeof(int));
        if(a == NULL) {
          fprintf(stderr, "realloc(): ");
          fprintf(stderr, "greska pri alokaciji memorije.\n");
          exit(EXIT_FAILURE);
        }
      ********************************************************/
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
