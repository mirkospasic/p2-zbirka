#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

Cvor *napravi_cvor(int broj)
{

/* Dinamicki kreiramo cvor */
    Cvor *novi = (Cvor *) malloc(sizeof(Cvor));

/* U slucaju greske ... */
    if (novi == NULL) {
	fprintf(stderr, "-1\n");
	exit(1);
    }

/* Inicijalizacija */
    novi->vrednost = broj;
    novi->levi = NULL;
    novi->desni = NULL;

/* Vracamo adresu novog cvora */
    return novi;
}

void dodaj_u_stablo(Cvor **koren, int broj)
{

/* Izlaz iz rekurzije: ako je stablo bilo prazno,
   novi koren je upravo novi cvor */
  if (*koren == NULL) {
    *koren = napravi_cvor(broj);
    return;
  }

/* Ako je stablo neprazno, i koren sadrzi manju vrednost
   od datog broja, broj se umece u desno podstablo, 
   rekurzivnim pozivom */
  if ((*koren)->vrednost < broj)
    dodaj_u_stablo(&(*koren)->desni, broj);
/* Ako je stablo neprazno, i koren sadrzi vecu vrednost
   od datog broja, broj se umece u levo podstablo,
   rekurzivnim pozivom */
  else if ((*koren)->vrednost > broj)
    dodaj_u_stablo(&(*koren)->levi, broj);

}

void prikazi_stablo(Cvor * koren)
{
/* Izlaz iz rekurzije */
    if (koren == NULL)
	return;

    prikazi_stablo(koren->levi);
    printf("%d ", koren->vrednost);
    prikazi_stablo(koren->desni);
}

Cvor* ucitaj_stablo() {
  Cvor *koren = NULL;
  int x;
  while (scanf("%d", &x) == 1)
    dodaj_u_stablo(&koren, x);
  return koren;
}

void oslobodi_stablo(Cvor **koren)
{

/* Izlaz iz rekurzije */
    if (*koren == NULL)
	return;

    oslobodi_stablo(&(*koren)->levi);
    oslobodi_stablo(&(*koren)->desni);
    free(*koren);

    *koren = NULL;
}

