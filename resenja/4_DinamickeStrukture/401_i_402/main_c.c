#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* 3) Glavni program */
int main()
{
  /* Lista je prazna na pocetku */
  Cvor *glava = NULL;
  Cvor *trazeni = NULL;
  int broj;

  /* Testiranje funkcije za dodavanje vrednosti u listu tako da bude
     uredjena neopadajuce */
  printf("Unesite brojeve (CTRL+D za kraj unosa): ");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za nov cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa. */
    if (dodaj_sortirano(&glava, broj) == 1) {
      fprintf(stderr, "Greska: Neuspesna alokacija memorije za cvor %d\n", broj);
      oslobodi_listu(&glava);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  /* Testiranje funkcija za pretragu liste */
  printf("\nUnesite broj koji se trazi: ");
  scanf("%d", &broj);

  trazeni = pretrazi_listu(glava, broj);
  if (trazeni == NULL)
    printf("Broj %d se ne nalazi u listi!\n", broj);
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  /* Testiranje funkcija kojom se brise cvor liste */
  printf("\nUnesite broj koji se brise: ");
  scanf("%d", &broj);

  /* Brisanje cvorova iz liste cije polje vrednost je jednako broju
     procitanom sa ulaza */
  obrisi_cvor_sortirane_liste(&glava, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  /* Oslobadjanje memorije zauzete listom */
  oslobodi_listu(&glava);

  exit(EXIT_SUCCESS);
}
