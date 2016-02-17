#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija koja kreira stablo prema zadatoj slici. Povratna
   vrednost funkcije je 0 ako je stablo uspesno kreirano, odnosno 1
   ukoliko je doslo do greske */
int kreiraj_hip(Cvor ** adresa_korena)
{
  /* Stablo se proglasava praznim */
  *adresa_korena = NULL;

  /* Dodaje se cvor po cvor uz proveru uspesnosti dodavanja */
  if (((*adresa_korena) = napravi_cvor(100)) == NULL)
    return 1;
  if (((*adresa_korena)->levo = napravi_cvor(19)) == NULL)
    return 1;
  if (((*adresa_korena)->levo->levo = napravi_cvor(17)) == NULL)
    return 1;
  if (((*adresa_korena)->levo->levo->levo = napravi_cvor(2)) == NULL)
    return 1;
  if (((*adresa_korena)->levo->levo->desno =
       napravi_cvor(7)) == NULL)
    return 1;
  if (((*adresa_korena)->levo->desno = napravi_cvor(3)) == NULL)
    return 1;
  if (((*adresa_korena)->desno = napravi_cvor(36)) == NULL)
    return 1;
  if (((*adresa_korena)->desno->levo = napravi_cvor(25)) == NULL)
    return 1;
  if (((*adresa_korena)->desno->desno = napravi_cvor(1)) == NULL)
    return 1;

  /* Vraca se indikator uspesnog kreiranja */
  return 0;
}

/* Funkcija proverava da li je zadato binarno stablo celih
   pozitivnih brojeva hip. Ideja koja ce biti implementirana u
   osnovi ima pronalazenje maksimalne vrednosti levog i maksimalne
   vrednosti desnog podstabla - ako je vrednost u korenu veca od
   izracunatih vrednosti, uoceni fragment stabla zadovoljava uslov
   za hip. Zato ce funkcija vracati maksimalne vrednosti iz uocenog
   podstabala ili vrednost -1 ukoliko se zakljuci da stablo nije
   hip. */
int hip(Cvor * koren)
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
  /* Proverava se svojstvo za levo podstablo */
  max_levo = hip(koren->levo);

  /* Proverava se svojstvo za desno podstablo */
  max_desno = hip(koren->desno);

  /* Ako levo ili desno podstablo uocenog cvora nije hip, onda nije
     ni celo stablo */
  if (max_levo == -1 || max_desno == -1) {
    return -1;
  }

  /* U suprotonom proverava se da li svojstvo vazi za uoceni cvor */
  if (koren->broj > max_levo && koren->broj > max_desno) {
    /* Ako vazi, vraca se vrednost korena */
    return koren->broj;
  }

  /* U suprotnom se zakljucuje da stablo nije hip */
  return -1;
}

int main(int argc, char **argv)
{
  Cvor *koren;
  int hip_indikator;

  /* Kreira se stablo prema zadatoj slici */
  if (kreiraj_hip(&koren) == 1) {
    fprintf(stderr, "Greska: Neuspesno kreiranje hipa.\n");
    oslobodi_stablo(&koren);
    exit(EXIT_FAILURE);
  }

  /* Poziva se funkcija kojom se proverava da li je stablo hip */
  hip_indikator = hip(koren);

  /* Ispisuje se rezultat */
  if (hip_indikator == -1) {
    printf("Zadato stablo nije hip!\n");
  } else {
    printf("Zadato stablo je hip!\n");
  }

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  exit(EXIT_SUCCESS);
}
