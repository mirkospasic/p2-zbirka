#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

int main()
{
  Cvor *koren;
  int n;
  Cvor *trazeni_cvor;

  /* Proglasava se stablo praznim */
  koren = NULL;

  /* Citaju se vrednosti i dodaju u stablo uz proveru uspesnosti
     dodavanja */
  printf("Unesite brojeve (CTRL+D za kraj unosa): ");
  while (scanf("%d", &n) != EOF) {
    if (dodaj_u_stablo(&koren, n) == 1) {
      fprintf(stderr, "Greska: Neuspelo dodavanje broja %d.\n", n);
      oslobodi_stablo(&koren);
      exit(EXIT_FAILURE);
    }
  }

  /* Generisu se trazeni ispisi: */
  printf("\nInfiksni ispis: ");
  ispisi_stablo_infiksno(koren);
  printf("\nPrefiksni ispis: ");
  ispisi_stablo_prefiksno(koren);
  printf("\nPostfiksni ispis: ");
  ispisi_stablo_postfiksno(koren);

  /* Demonstrira se rad funkcije za pretragu */
  printf("\nTrazi se broj: ");
  scanf("%d", &n);
  trazeni_cvor = pretrazi_stablo(koren, n);
  if (trazeni_cvor == NULL)
    printf("Broj se ne nalazi u stablu!\n");

  else
    printf("Broj se nalazi u stablu!\n");

  /* Demonstrira se rad funkcije za brisanje */
  printf("Brise se broj: ");
  scanf("%d", &n);
  obrisi_element(&koren, n);
  printf("Rezultujuce stablo: ");
  ispisi_stablo_infiksno(koren);
  printf("\n");

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  exit(EXIT_SUCCESS);
}
