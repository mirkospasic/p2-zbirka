#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() 
{
  Cvor * glava = NULL;
  int broj;

  /* Testiramo dodavanje na kraj liste */
  printf("Unesite elemente liste (za kraj unesite CTRL+D)\n");
  printf("\n\tLista: ");
  ispisi_listu(glava);

  while(scanf("%d",&broj) > 0)
    {
      dodaj_na_kraj_liste(&glava, broj);
      printf("\n\tLista: ");
      ispisi_listu(glava);
    }

  printf("\nUnesite element koji se brise iz liste: ");
  scanf("%d", &broj);

  /* Brisemo elemente iz liste cije polje vrednost je jednako
     broju procitanom sa ulaza */
  obrisi_element(&glava, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  oslobodi_listu(&glava);

  return 0;
}
