#include <stdio.h>
#include <stdlib.h>
#include "dvostruko_povezana_lista.h"

/* 2) Glavni program */
int main()
{
  Cvor *glava = NULL;
  Cvor *kraj = NULL;
  int broj;

  /* Testiranje dodavanja novog broja na kraj liste. */
  printf("Unesite brojeve: (za kraj unesite CTRL+D)\n");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za nov cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa. */
    if (dodaj_na_kraj_liste(&glava, &kraj, broj) == 1) {
      fprintf(stderr, "Neuspela alokacija za cvor %d\n", broj);
      oslobodi_listu(&glava, &kraj);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  printf("\nUnesite broj koji se brise iz liste: ");
  scanf("%d", &broj);

  /* Brisu se cvorovi iz liste cije polje vrednost je jednako broju
     procitanom sa ulaza. */
  obrisi_cvor(&glava, &kraj, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  printf("\nLista ispisana u nazad: ");
  ispisi_listu_unazad(kraj);

  oslobodi_listu(&glava, &kraj);

  return 0;
}
