#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
int sumirajN(Cvor * koren, int n) 
{
  /* Ako je stablo prazno, suma je nula */
  if (koren == NULL)
    return 0;
  /* Inace ... */
  /* Ako je n jednako nula, vraca se broj iz korena  */
  if (n == 0)
    return koren->broj;
  /* Inace, izracunava se suma na (n-1)-om nivou u levom podstablu, 
     kao i suma na (n-1)-om nivou u desnom podstablu i vraca se zbir
     te dve izracunate vrednosti jer predstavlja zbir svih cvorova na
	 n-tom nivou u pocetnom stablu */
  return sumirajN(koren->levo, n - 1) + sumirajN(koren->desno,
                                                   n - 1);}
int main() 
{
  Cvor * koren = NULL;
  int n;
  int nivo;
  
  /* Ucitava se vrednost nivoa */
  scanf("%d", &nivo);
  while (1) {
    scanf("%d", &n);
    /* Ukoliko je korisnik uneo 0, prekida se dalje citanje. */ 
    if (n == 0)
      break;
    /* Ako nije, dodaje se procitani broj u stablo. */ 
    if (dodaj_u_stablo(&koren, n) == 1) {
      fprintf(stderr, "-1\n", n);
      oslobodi_stablo(&koren);
      exit(EXIT_FAILURE);
    }
  }
    /* Ispisuje se rezultat rada trazene funkcije */ 
  printf("%d\n", sumirajN(koren, nivo));
    /* Oslobadja se memorija */ 
  oslobodi_stablo(&koren);
  
  exit(EXIT_SUCCESS);}


