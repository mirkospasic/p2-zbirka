#include <stdio.h>
#include <stdlib.h>
#include "dvostruko_povezana_lista.h"

/* 3) Glavni program */
int main()
{
  /* Lista je prazna na pocetku */
  Cvor *glava = NULL;
  Cvor *kraj = NULL;
  Cvor *trazeni = NULL;
  int broj;

  /* Testira se funkcija za dodavanje vrednosti u listu tako da ona
     bude uredjena neopadajuce */
  printf("Unosite brojeve (za kraj unesite CTRL+D)\n");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za novi cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa */
    if (dodaj_sortirano(&glava, &kraj, broj) == 1) {
      fprintf(stderr, "Neuspela alokacija za cvor %d\n", broj);
      oslobodi_listu(&glava, &kraj);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  /* Testira se funkcija za pretragu liste */
  printf("\nUnesite broj koji se trazi u listi: ");
  scanf("%d", &broj);

  /* Pokazivac trazeni dobija vrednost rezultata pretrage */
  trazeni = pretrazi_listu(glava, broj);
  if (trazeni == NULL)
    printf("Broj %d se ne nalazi u listi!\n", broj);
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  /* Testira se funkcija za brisanje elemenata iz liste */
  printf("\nUnesite broj koji se brise iz liste: ");
  scanf("%d", &broj);

  /* Brisu se cvorovi iz liste cije polje vrednost je jednako broju
     procitanom sa ulaza */
  obrisi_cvor_sortirane_liste(&glava, &kraj, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  /* Ispisuje se lista unazad */
  printf("\nLista ispisana u nazad: ");
  ispisi_listu_unazad(kraj);

  /* Oslobadja se memorija zauzeta za cvorove liste */
  oslobodi_listu(&glava, &kraj);

  exit(EXIT_SUCCESS);
}
