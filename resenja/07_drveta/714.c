#include<stdio.h>
#include<stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija koja izracunava dubinu stabla */
int dubina_stabla(Cvor * koren)
{
  /* Dubina praznog stabla je 0 */
  if (koren == NULL)
    return 0;

  /* Izracunava se dubina levog podstabla */
  int dubina_levo = dubina_stabla(koren->levo);

  /* Izracunava se dubina desnog podstabla */
  int dubina_desno = dubina_stabla(koren->desno);

  /* Dubina stabla odgovara vecoj od dubina podstabala - 1 se dodaje
     jer se racuna i koren */
  return dubina_levo >
      dubina_desno ? dubina_levo + 1 : dubina_desno + 1;
}

/* Funkcija koja racuna broj cvorova koji ispunjavaju uslov za AVL
   stablo */
int avl(Cvor * koren)
{
  int dubina_levo, dubina_desno;

  /* Ako je stablo prazno, zaustavlja se brojanje */
  if (koren == NULL) {
    return 0;
  }

  /* Izracunava se dubina levog podstabla korena */
  dubina_levo = dubina_stabla(koren->levo);

  /* Izracunava se dubina desnog podstabla korena */
  dubina_desno = dubina_stabla(koren->desno);

  /* Ako je uslov za AVL stablo ispunjen */
  if (abs(dubina_desno - dubina_levo) <= 1) {
    /* Racuna se broj AVL cvorova u levom i desnom podstablu i
       uvecava za jedan iz razloga sto koren ispunjava uslov */
    return 1 + avl(koren->levo) + avl(koren->desno);
  } else {
    /* Inace, racuna se samo broj AVL cvorova u podstablima */
    return avl(koren->levo) + avl(koren->desno);
  }
}

int main(int argc, char **argv)
{
  Cvor *koren;
  int broj;

  /* Ucitavaju se vrednosti sa ulaza i dodaju u stablo */
  koren = NULL;
  while (scanf("%d", &broj) != EOF) {
    dodaj_u_stablo(&koren, broj);
  }

  /* Racuna se i ispisuje broj AVL cvorova */
  printf("%d\n", avl(koren));

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
