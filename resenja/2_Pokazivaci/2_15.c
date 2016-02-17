#include <stdio.h>
#include <stdlib.h>

int main()
{
  int *p = NULL;
  int i, n;

  printf("Unesite dimenziju niza: ");
  scanf("%d", &n);

  /* Rezervise se prostor za n celih brojeva */
  if ((p = (int *) malloc(sizeof(int) * n)) == NULL) {
    fprintf(stderr, "Greska: Neupesna alokacija memorije.\n");
    exit(EXIT_FAILURE);
  }

  printf("Unesite elemente niza: ");
  for (i = 0; i < n; i++)
    scanf("%d", &p[i]);

  printf("Niz u obrnutom poretku je: ");
  for (i = n - 1; i >= 0; i--)
    printf("%d ", p[i]);
  printf("\n");

  /* Oslobadja se prostor rezervisan funkcijom malloc() */
  free(p);

  exit(EXIT_SUCCESS);
}
