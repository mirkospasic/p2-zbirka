/* Rekurzivne funkcije za rad sa jednostruko povezanom listom */
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() 
{
  /* Lista je prazna na pocetku. */
  Cvor *glava = NULL; 
  Cvor *trazeni = NULL;
  int broj;

  /* Testiramo dodavanje na pocetak*/
  printf("Unosite elemente liste! (za kraj unesite CTRL+D)\n");
  while(scanf("%d",&broj)>0)
    { 
      /* Ako je funkcija vratila 1 onda je bilo greske pri 
         alokaciji memorije za nov cvor. Listu moramo osloboditi
         pre napustanja programa. */
      if ( dodaj_na_pocetak_liste(&glava, broj) == 1) 
        {
          fprintf(stderr,"Neuspela alokacija za cvor %d\n",broj);
          oslobodi_listu(&glava);
          exit(EXIT_FAILURE);
        }
      printf("\n\tLista: ");
      ispisi_listu(glava);
    }

  ispisi_listu(glava);

  printf("\nUnesite element koji se trazi u listi: ");
  scanf("%d", &broj);

  trazeni=pretrazi_listu(glava, broj);
  if( trazeni == NULL)
    printf("Element NIJE u listi!\n");
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  oslobodi_listu(&glava);

  return 0;
}