#include <stdio.h>
#include <stdlib.h>
#include "dvostruko_povezana_lista.h"

/* 2) Glavni program */
int main()
{
  /* Lista je prazna na pocetku. */
  Cvor *glava = NULL;
  Cvor *kraj = NULL;
  int broj;

  /* Testira se funkcija za dodavanje novog broja na kraj liste */
  printf("Unesite brojeve (CTRL+D za kraj unosa): ");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za novi cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa */
    if (dodaj_na_kraj_liste(&glava, &kraj, broj) == 1) {
      fprintf(stderr,
              "Greska: Neuspesna alokacija memorije za cvor.\n");
      oslobodi_listu(&glava, &kraj);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  /* Testira se funkcija za brisanje elemenata iz liste */
  printf("\nUnesite broj koji se brise iz liste: ");
  scanf("%d", &broj);

  /* Brisu se cvorovi liste cija vrednost je jednaka unetom broju */
  obrisi_cvor(&glava, &kraj, broj);

  printf("Lista nakon brisanja: ");
  ispisi_listu(glava);

  /* Ispisuje se lista unazad */
  printf("\nLista ispisana u nazad: ");
  ispisi_listu_unazad(kraj);

  /* Oslobadja se memorija zauzeta za cvorove liste */
  oslobodi_listu(&glava, &kraj);

  exit(EXIT_SUCCESS);
}
