#include<stdio.h>
#include<stdlib.h>

/* Ukljucujemo biblioteku za rad sa stablima */
#include "stabla.h"

/* Funckija koja izracunava dubinu stabla */
int dubina_stabla(Cvor * koren)
{
  /* Dubina praznog stabla je 0 */
  if (koren == NULL)
    return 0;

  /* Izracunavamo dubinu levog podstabla */
  int dubina_levo = dubina_stabla(koren->levo);

  /* Izracunavamo dubinu desnog podstabla */
  int dubina_desno = dubina_stabla(koren->desno);

  /* Dubina stabla odgovara vecoj od dubina podstabala - 1
     dodajemo jer racunamo i koren */
  return dubina_levo >
      dubina_desno ? dubina_levo + 1 : dubina_desno + 1;
}

/* Funkcija koja racuna broj cvorova koji ispunjavaju uslov za
   AVL stablo */
int avl(Cvor * koren)
{
  int dubina_levo, dubina_desno;

  /* Ako je stablo prazno, zaustavljamo brojanje */
  if (koren == NULL) {
    return 0;
  }

  /* Izracunavamo dubinu levog podstabla korena */
  dubina_levo = dubina_stabla(koren->levo);

  /* Izracunavamo dubinu desnog podstabla korena */
  dubina_desno = dubina_stabla(koren->desno);

  /* Ako je uslov za AVL stablo ispunjen */
  if (abs(dubina_desno - dubina_levo) <= 1) {
    /* Racunamo broj avl cvorova u levom i desnom podstablu i
       uvecavamo za jedan iz razloga sto koren ispunjava uslov */
    return 1 + avl(koren->levo) + avl(koren->desno);
  } else {
    /* Inace, racunamo samo broj avl cvorova u podstablima */
    return avl(koren->levo) + avl(koren->desno);
  }
}

int main(int argc, char **argv)
{
  Cvor *koren;
  int broj;

  /* Citamo vrednosti sa ulaza i dodajemo ih u stablo */
  koren = NULL;
  while (scanf("%d", &broj) != EOF) {
    dodaj_u_stablo(&koren, broj);
  }

  /* Racunamo i ispisujemo broj AVL cvorova */
  printf("%d\n", avl(koren));

  /* Oslobadjamo memoriju zauzetu stablom */
  oslobodi_stablo(&koren);

  /* Prekidamo izvrsavanje programa */
  return 0;
}
