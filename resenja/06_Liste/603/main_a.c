#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* 1) Glavni program */
int main()
{
  /* Lista je prazna na pocetku. */
  Cvor *glava = NULL;
  Cvor *trazeni = NULL;
  int broj;

  /* Testiranje dodavanja novog broja na pocetak liste. */
  printf("Unesite brojeve: (za kraj CTRL+D)\n");
  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za nov cvor. Memoriju alociranu za cvorove liste
       treba osloboditi pre napustanja programa. */
    if (dodaj_na_pocetak_liste(&glava, broj) == 1) {
      fprintf(stderr, "Neuspela alokacija za cvor %d\n", broj);
      oslobodi_listu(&glava);
      exit(EXIT_FAILURE);
    }
    printf("\tLista: ");
    ispisi_listu(glava);
  }

  printf("\nUnesite broj koji se trazi u listi: ");
  scanf("%d", &broj);

  trazeni = pretrazi_listu(glava, broj);
  if (trazeni == NULL)
    printf("Broj %d se ne nalazi u listi!\n", broj);
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  printf("\nLista ispisana u nazad: ");
  ispisi_listu_unazad(glava);

  oslobodi_listu(&glava);

  return 0;
}
