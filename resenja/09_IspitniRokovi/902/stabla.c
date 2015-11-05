#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

Cvor *napravi_cvor(int b)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja novog Cvora */
  novi->broj = b;
  novi->levo = NULL;
  novi->desno = NULL;

  return novi;
}

void oslobodi_stablo(Cvor ** adresa_korena)
{
  /* Prazno stablo i nema sta da se oslobadja */
  if (*adresa_korena == NULL)
    return;

  /* Rekurzivno se oslobadja najpre levo, a onda i desno podstablo */
  if ((*adresa_korena)->levo)
    oslobodi_stablo(&(*adresa_korena)->levo);
  if ((*adresa_korena)->desno)
    oslobodi_stablo(&(*adresa_korena)->desno);

  free(*adresa_korena);
  *adresa_korena = NULL;
}

int dodaj_u_stablo(Cvor ** adresa_korena, int broj)
{
  /* Postojece stablo je prazno */
  if (*adresa_korena == NULL) {
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;
    /* Kreirani Cvor novi ce biti od sada koren stabla */
    *adresa_korena = novi;
    return 0;
  }

  /* Brojevi se smestaju u uredjeno binarno stablo, pa ako je broj
     koji se ubacuje manji od broja koji je u korenu onda se dodaje u 
     levo podstablo. */
  if (broj < (*adresa_korena)->broj)
    return dodaj_u_stablo(&(*adresa_korena)->levo, broj);
  /* Ako je broj manji ili jednak od broja koji je u korenu stabla,
     dodaje se nov Cvor desno od korena. */
  else
    return dodaj_u_stablo(&(*adresa_korena)->desno, broj);
}
