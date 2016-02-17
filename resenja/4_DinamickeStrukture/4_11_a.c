#include <stdio.h>
#include <stdlib.h>
#include "dvostruko_povezana_lista.h"

/* 1) Glavni program */
int main()
{
  /* Lista je prazna na pocetku */
  /* Cuvaju se pokazivaci na glavu liste i na poslednji cvor liste,
     da bi operacije poput dodavanja na kraj liste i ispisivanja
     liste unazad bile efikasne poput dodavanja na pocetak liste i
     ispisivanja liste od pocetnog do poslednjeg cvora. */
  Cvor *glava = NULL;
  Cvor *kraj = NULL;
  Cvor *trazeni = NULL;
  int broj;

  /* Testiranje funkcije za dodavanja novog broja na pocetak liste */
  printf("Unesite brojeve (CTRL+D za kraj unosa): ");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za novi cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa */
    if (dodaj_na_pocetak_liste(&glava, &kraj, broj) == 1) {
      fprintf(stderr,
              "Greska: Neuspesna alokacija memorije za cvor.\n");
      oslobodi_listu(&glava, &kraj);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  /* Testiranje funkcije za pretragu liste */
  printf("\nUnesite broj koji se trazi u listi: ");
  scanf("%d", &broj);

  /* Pokazivac trazeni dobija vrednost rezultata pretrage */
  trazeni = pretrazi_listu(glava, broj);
  if (trazeni == NULL)
    printf("Broj %d se ne nalazi u listi!\n", broj);
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  /* Ispisivanje liste unazad */
  printf("\nLista ispisana u nazad: ");
  ispisi_listu_unazad(kraj);

  /* Oslobadjanje memorije zauzete za cvorove liste */
  oslobodi_listu(&glava, &kraj);

  exit(EXIT_SUCCESS);
}
