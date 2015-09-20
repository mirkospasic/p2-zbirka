#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
  Cvor *glava = NULL;
  Cvor *trazeni = NULL;
  int broj;

  /* Testira se dodavanje u listu tako da ona bude neopadajuce
     uredjena */
  printf("Unosite brojeve (za kraj unesite CTRL+D)\n");
  printf("\tLista: ");
  ispisi_listu(glava);

  while (scanf("%d", &broj) > 0) {
    /* Ako je funkcija vratila 1 onda je bilo greske pri
       alokaciji memorije za nov cvor. Memoriju alociranu za
       cvorove liste treba osloboditi pre napustanja programa. */
    if (dodaj_sortirano(&glava, broj) == 1) {
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

  printf("\nUnesite broj koji se brise iz liste: ");
  scanf("%d", &broj);

  /* Brisu se cvorovi iz liste cije polje vrednost je jednako
     broju procitanom sa ulaza */
  obrisi_cvor_sortirane_liste(&glava, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  printf("\nLista ispisana u nazad: ");
  ispisi_listu_u_nazad(glava);
  
  oslobodi_listu(&glava);

  return 0;
}
