#include <stdio.h>
#include <stdlib.h>
#include "stablo.h"

/* Funkcija racuna duzinu najduzeg puta od korena do nekog lista */
int najduzi_put(Cvor *koren) {
  /* Pomocne promenljive */
  int najduzi_u_levom,najduzi_u_desnom;
  
  /* Ako je stablo prazno, povratna vrednost je -1 */
  if(koren==NULL)
    return -1;
  
  /* Rekurzivno se izracuna duzina najduzeg puta u levom podstablu */
  najduzi_u_levom=najduzi_put(koren->levo);
  
  /* Rekurzivno se izracuna duzina najduzeg puta u levom podstablu */
  najduzi_u_desnom=najduzi_put(koren->desno);
  
  /* Veca od prethodno izracunatih vrednosti za podstabla se uvecava 
     za 1 i vraca kao konacan rezultat */
  return 1 + (najduzi_u_levom > najduzi_u_desnom ? najduzi_u_levom : najduzi_u_desnom);
}

int main() {
  Cvor *stablo = NULL;
  int x;

  /* U svakoj iteraciji se procitani broj dodaje u stablo. */
  while (scanf("%d", &x) == 1)
    if (dodaj_u_stablo(&stablo, x) == 1) {
      fprintf(stderr, "-1\n");
      exit(EXIT_FAILURE);
    }

  /* Ispisuje se rezultat rada trazene funkcije */
  printf("%d\n", najduzi_put(stablo));
  
  /* Oslobadja se memorija */
  oslobodi_stablo(&stablo);

  exit(EXIT_SUCCESS);
}
