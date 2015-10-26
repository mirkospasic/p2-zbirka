#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija proverava da li je zadato binarno stablo celih pozitivnih 
   brojeva hip. Ideja koja ce biti implementirana u osnovi ima
   pronalazenje maksimalne vrednosti levog i maksimalne vrednosti
   desnog podstabla - ako je vrednost u korenu veca od izracunatih
   vrednosti, uoceni fragment stabla zadovoljava uslov za hip. Zato
   ce funkcija vracati maksimalne vrednosti iz uocenog podstabala ili 
   vrednost -1 ukoliko se zakljuci da stablo nije hip. */
int heap(Cvor * koren)
{
  int max_levo, max_desno;

  /* Prazno sablo je hip - kao rezultat se vraca 0 kao najmanji
     pozitivan broj */
  if (koren == NULL) {
    return 0;
  }
  /* Ukoliko je stablo list... */
  if (koren->levo == NULL && koren->desno == NULL) {
    /* Vraca se njegova vrednost */
    return koren->broj;
  }
  /* Inace... */

  /* Proverava se svojstvo za levo podstablo. */
  max_levo = heap(koren->levo);

  /* Proverava se svojstvo za desno podstablo. */
  max_desno = heap(koren->desno);

  /* Ako levo ili desno podstablo uocenog cvora nije hip, onda nije
     ni celo stablo. */
  if (max_levo == -1 || max_desno == -1) {
    return -1;
  }

  /* U suprotonom proverava se da li svojstvo vazi za uoceni cvor. */
  if (koren->broj > max_levo && koren->broj > max_desno) {
    /* Ako vazi, vraca se vrednost korena */
    return koren->broj;
  }

  /* U suprotnom zakljucuje se da stablo nije hip */
  return -1;
}

int main(int argc, char **argv)
{
  Cvor *koren;
  int hip_indikator;

  /* Kreira se stablo koje sadrzi brojeve 100 19 36 17 3 25 1 2 7 */
  koren = NULL;
  koren = napravi_cvor(100);
  koren->levo = napravi_cvor(19);
  koren->levo->levo = napravi_cvor(17);
  koren->levo->levo->levo = napravi_cvor(2);
  koren->levo->levo->desno = napravi_cvor(7);
  koren->levo->desno = napravi_cvor(3);
  koren->desno = napravi_cvor(36);
  koren->desno->levo = napravi_cvor(25);
  koren->desno->desno = napravi_cvor(1);

  /* Poziva se funkcija kojom se proverava da li je stablo hip */
  hip_indikator = heap(koren);

  /* Ispisuje se rezultat */
  if (hip_indikator == -1) {
    printf("Zadato stablo nije hip!\n");
  } else {
    printf("Zadato stablo je hip!\n");
  }

  /* Oslobadja se memorija zauzeta stablom. */
  oslobodi_stablo(&koren);

  return 0;
}
