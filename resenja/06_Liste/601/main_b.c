#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* 2) Glavni program */
int main()
{
  Cvor *glava = NULL;
  int broj;

  /* Testiranje dodavanja novog broja na kraj liste. */
  printf("Unesite brojeve: (za kraj CTRL+D)\n");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1 onda je bilo greske pri alokaciji
       memorije za nov cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa. */
    if (dodaj_na_kraj_liste(&glava, broj) == 1) {
      fprintf(stderr, "Neuspela alokacija za cvor %d\n", broj);
      oslobodi_listu(&glava);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  printf("\nUnesite broj koji se brise: ");
  scanf("%d", &broj);

  /* Brisu se cvorovi iz liste cije polje vrednost je jednako broju
     procitanom sa ulaza */
  obrisi_cvor(&glava, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  oslobodi_listu(&glava);

  return 0;
}
