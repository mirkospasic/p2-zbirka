#include <stdio.h>
#include <stdlib.h>

/* NAPOMENA: Primer demonstrira dinamicku alokaciju niza od n
   elemenata. Dovoljno je alocirati n * sizeof(T) bajtova, gde je T
   tip elemenata niza. Povratnu adresu malloc()-a treba pretvoriti iz 
   void * u T *, kako bismo dobili pokazivac koji pokazuje na prvi
   element niza tipa T. Na dalje se elementima moze pristupati na
   isti nacin kao da nam je dato ime niza (koje se tako i ponasa -
   kao pokazivac na element tipa T koji je prvi u nizu) */
int main()
{
  int *p = NULL;
  int i, n;

  /* Unosimo dimenziju niza. Ova vrednost nije ogranicena bilo kakvom 
     konstantom, kao sto je to ranije bio slucaj kod staticke
     alokacije gde je dimenzija niza bila unapred ogranicena
     definisanim prostorom. */
  scanf("%d", &n);

  /* Alociramo prostor za n celih brojeva */
  if ((p = (int *) malloc(sizeof(int) * n)) == NULL) {
    fprintf(stderr, "malloc(): ");
    fprintf(stderr, "greska pri alokaciji memorije.\n");
    exit(EXIT_FAILURE);
  }

  /* Od ovog trenutka pokazivac "p" mozemo da koristimo kao da je ime 
     niza, odnosno i-tom elementu se moze pristupiti sa p[i] */

  /* Unosimo elemente niza */
  for (i = 0; i < n; i++)
    scanf("%d", &p[i]);

  /* Ispisujemo elemente niza unazad */
  for (i = n - 1; i >= 0; i--)
    printf("%d ", p[i]);
  printf("\n");

  /* Oslobadjamo prostor */
  free(p);

  return 0;
}
