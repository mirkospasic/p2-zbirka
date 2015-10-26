#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija koja proverava da li su dva stabla koja sadrze cele
   brojeve identicna. Povratna vrednost funkcije je 1 ako jesu,
   odnosno 0 ako nisu */
int identitet(Cvor * koren1, Cvor * koren2)
{
  /* Ako su oba stabla prazna, jednaka su */
  if (koren1 == NULL && koren2 == NULL)
    return 1;

  /* Ako je jedno stablo prazno, a drugo nije, stabla nisu jednaka */
  if (koren1 == NULL || koren2 == NULL)
    return 0;

  /* Ako su oba stabla neprazna i u korenu se nalaze razlicite
     vrednosti, moze se zakljuciti da se razlikuju */
  if (koren1->broj != koren2->broj)
    return 0;

  /* Inace, proverava se da li vazi i jednakost levih i desnih
     podstabala */
  return (identitet(koren1->levo, koren2->levo)
          && identitet(koren1->desno, koren2->desno));
}

int main()
{
  int broj;
  Cvor *koren1, *koren2;

  /* Ucitavaju se elementi prvog stabla */
  koren1 = NULL;
  printf("Prvo stablo: ");
  scanf("%d", &broj);
  while (broj != 0) {
    dodaj_u_stablo(&koren1, broj);
    scanf("%d", &broj);
  }

  /* Ucitavaju se elementi drugog stabla */
  koren2 = NULL;
  printf("Drugo stablo: ");
  scanf("%d", &broj);
  while (broj != 0) {
    dodaj_u_stablo(&koren2, broj);
    scanf("%d", &broj);
  }

  /* Poziva se funkcija koja ispituje identitet stabala i ispisuje se 
     njen rezultat. */
  if (identitet(koren1, koren2))
    printf("Stabla jesu identicna.\n");
  else
    printf("Stabla nisu identicna.\n");

  /* Oslobadja se memorija zauzeta stablima */
  oslobodi_stablo(&koren1);
  oslobodi_stablo(&koren2);

  return 0;
}
