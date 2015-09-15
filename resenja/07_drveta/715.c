#include<stdio.h>
#include<stdlib.h>

/* Ukljucujemo biblioteku za rad sa stablima */
#include "stabla.h"

/* Funkcija proverava da li je zadato binarno stablo celih
   pozitivnih brojeva heap. Ideja koju cemo implementirati u
   osnovi ima pronalazenje maksimalne vrednosti levog i
   maksimalne vrednosti desnog podstabla - ako je vrednost u
   korenu veca od izracunatih vrednosti uoceni fragment stabla
   zadovoljava uslov za heap. Zato ce funkcija vracati
   maksimalne vrednosti iz uocenog podstabala ili vrednost -1
   ukoliko zakljucimo da stablo nije heap. */
int heap(Cvor * koren)
{

  int max_levo, max_desno;

  /* Prazno sablo je heap. */
  if (koren == NULL) {
    /* posto je 0 najmanji pozitivan broj, moze nam posluziti
       kao indikator */
    return 0;

  }
  /* Ukoliko je stablo list ... */
  if (koren->levo == NULL && koren->desno == NULL) {
    /* ... vracamo njegovu vrednost */
    return koren->broj;
  }

  /* Proveravamo svojstvo za levo podstablo. */
  max_levo = heap(koren->levo);

  /* Proveravamo svojstvo za desno podstablo. */
  max_desno = heap(koren->desno);
  /* Ako levo ili desno podstablo uocenog cvora nije heap, onda
     nije ni celo stablo. */
  if (max_levo == -1 || max_desno == -1) {
    return -1;
  }

  /* U suprotonom proveravamo da li svojstvo vazi za uoceni
     cvor. */
  if (koren->broj > max_levo && koren->broj > max_desno) {
    /* ako vazi, vracamo vrednost korena */
    return koren->broj;
  }

  /* u suprotnom zakljucujemo da stablo nije heap */
  return -1;
}

int main(int argc, char **argv)
{
  Cvor *koren;
  int heap_indikator;

  /* Kreiramo stablo koje sadrzi brojeve 100 19 36 17 3 25 1 2 7 
   */
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

  /* pozivamo funkciju kojom proveravamo da li je stablo heap */
  heap_indikator = heap(koren);

  /* i ispisujemo rezultat */
  if (heap_indikator == -1) {
    printf("Zadato tablo nije heap\n");
  } else {
    printf("Zadato stablo je heap!\n");
  }

  /* Oslobadjamo memoriju zauzetu stablom. */
  oslobodi_stablo(&koren);

  /* Zavrsavamo sa programom */
  return 0;

}
