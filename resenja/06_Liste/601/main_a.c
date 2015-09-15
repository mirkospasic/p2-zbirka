#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
  /* Lista je na pocetku prazna. */
  Cvor * glava = NULL;
  Cvor * trazeni = NULL;
  int broj;

  /* Testiramo dodavanje na pocetak*/
  printf("Unesite elemente liste (za kraj unesite CTRL+D)\n");
  printf("\n\tLista: ");
  ispisi_listu(glava);

  while(scanf("%d",&broj)>0)
    {
      dodaj_na_pocetak_liste(&glava, broj);
      printf("\n\tLista: ");
      ispisi_listu(glava);
    }

  printf("\nUnesite element koji se trazi u listi: ");
  scanf("%d", &broj);

  trazeni = pretrazi_listu(glava, broj);
  if(trazeni == NULL)
    printf("Element NIJE u listi!\n");
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  oslobodi_listu(&glava);

  return 0;
}
