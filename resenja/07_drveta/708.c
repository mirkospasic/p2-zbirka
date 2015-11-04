#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija kreira novo stablo identicno stablu koje je dato korenom. 
   Povratna vrednost funkcije je 0 ukoliko je kopiranje uspesno,
   odnosno 1 ukoliko je doslo do greske */
int kopiraj_stablo(Cvor * koren, Cvor ** duplikat)
{
  /* Izlaz iz rekurzije */
  if (koren == NULL) {
    *duplikat = NULL;
    return 0;
  }

  /* Duplira se koren stabla i postavlja da bude koren novog stabla */
  *duplikat = napravi_cvor(koren->broj);
  if (*duplikat == NULL) {
    return 1;
  }

  /* Rekurzivno se duplirju levo i desno podstablo i njihove adrese
     se cuvaju redom u pokazivacima na levo i desno podstablo korena
     duplikata */
  int kopija_levo = kopiraj_stablo(koren->levo, &(*duplikat)->levo);
  int kopija_desno =
      kopiraj_stablo(koren->desno, &(*duplikat)->desno);
  if (kopija_levo == 0 && kopija_desno == 0)
    return 0;
  else
    return 1;

}

/* Funkcija izracunava uniju dva skupa predstavljena stablima -
   rezultujuci skup tj. stablo se dobija modifikacijom prvog stabla */
int kreiraj_uniju(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako drugo stablo nije prazno */
  if (koren2 != NULL) {
    /* Dodaje se njegov koren u prvo stablo */
    if (dodaj_u_stablo(adresa_korena1, koren2->broj) == 1) {
      return 1;
    }

    /* Rekurzivno se racuna unija levog i desnog podstabla drugog
       stabla sa prvim stablom */
    int unija_levo = kreiraj_uniju(adresa_korena1, koren2->levo);
    int unija_desno = kreiraj_uniju(adresa_korena1, koren2->desno);

    if (unija_levo == 0 && unija_desno == 0)
      return 0;
    else
      return 1;
  }

  return 0;
}

/* Funkcija izracunava presek dva skupa predstavljana stablima -
   rezultujuci skup tj. stablo se dobija modifikacijom prvog stabla */
int kreiraj_presek(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako je prvo stablo prazno, tada je i rezultat prazno stablo */
  if (*adresa_korena1 == NULL)
    return 0;

  /* Inace... */
  /* Kreira se presek levog i desnog podstabla sa drugim stablom, tj. 
     iz levog i desnog podstabla prvog stabla brisu se svi oni
     elementi koji ne postoje u drugom stablu */
  if (kreiraj_presek(&(*adresa_korena1)->levo, koren2) == 0 &&
      kreiraj_presek(&(*adresa_korena1)->desno, koren2) == 0) {

    /* Ako se koren prvog stabla ne nalazi u drugom stablu tada se on
       uklanja iz prvog stabla */
    if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) == NULL)
      obrisi_element(adresa_korena1, (*adresa_korena1)->broj);

    return 0;
  } else
    return 1;
}

/* Funkcija izracunava razliku dva skupa predstavljana stablima -
   rezultujuci skup tj. stablo se dobija modifikacijom prvog stabla */
int kreiraj_razliku(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako je prvo stablo prazno, tada je i rezultat prazno stablo */
  if (*adresa_korena1 == NULL)
    return 0;

  /* Inace... */
  /* Kreira se razlika levog i desnog podstabla sa drugim stablom,
     tj. iz levog i desnog podstabla prvog stabla se brisu svi oni
     elementi koji postoje i u drugom stablu */
  if (kreiraj_razliku(&(*adresa_korena1)->levo, koren2) == 0 &&
      kreiraj_razliku(&(*adresa_korena1)->desno, koren2) == 0) {

    /* Ako se koren prvog stabla nalazi i u drugom stablu tada se
       isti uklanja iz prvog stabla */
    if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) != NULL)
      obrisi_element(adresa_korena1, (*adresa_korena1)->broj);

    return 0;
  } else
    return 1;
}

int main()
{
  Cvor *skup1;
  Cvor *skup2;
  Cvor *pomocni_skup = NULL;
  int n;

  /* Ucitavaju se elementi prvog skupa */
  skup1 = NULL;
  printf("Prvi skup: ");
  while (scanf("%d", &n) != EOF) {
    if (dodaj_u_stablo(&skup1, n) == 1) {
      fprintf(stderr, "Neuspelo dodavanje broja %d\n", n);
      oslobodi_stablo(&skup1);
      return 0;
    }
  }

  /* Ucitavaju se elementi drugog skupa */
  skup2 = NULL;
  printf("Drugi skup: ");
  while (scanf("%d", &n) != EOF) {
    if (dodaj_u_stablo(&skup2, n) == 1) {
      fprintf(stderr, "Neuspelo dodavanje broja %d\n", n);
      oslobodi_stablo(&skup2);
      return 0;
    }
  }

  /* Kreira se unija skupova: prvo se napravi kopija prvog skupa kako 
     bi se isti mogao iskoristiti i za preostale operacije */
  if (kopiraj_stablo(skup1, &pomocni_skup) == 1) {
    oslobodi_stablo(&skup1);
    oslobodi_stablo(&pomocni_skup);
    return 0;
  }
  if (kreiraj_uniju(&pomocni_skup, skup2) == 1) {
    oslobodi_stablo(&pomocni_skup);
    oslobodi_stablo(&skup2);
    return 0;
  }
  printf("Unija: ");
  ispisi_stablo_infiksno(pomocni_skup);
  putchar('\n');

  /* Oslobadja se memorija zauzeta pomocnim skupom sa rezultatom
     operacije */
  oslobodi_stablo(&pomocni_skup);

  /* Kreira se presek skupova: prvo se napravi kopija prvog skupa
     kako bi se isti mogao iskoristiti i za preostale operacije */
  if (kopiraj_stablo(skup1, &pomocni_skup) == 1) {
    oslobodi_stablo(&skup1);
    oslobodi_stablo(&pomocni_skup);
    return 0;
  }
  if (kreiraj_presek(&pomocni_skup, skup2) == 1) {
    oslobodi_stablo(&pomocni_skup);
    oslobodi_stablo(&skup2);
    return 0;
  }
  printf("Presek: ");
  ispisi_stablo_infiksno(pomocni_skup);
  putchar('\n');

  /* Oslobadja se memorija zauzeta pomocnim skupom sa rezultatom
     operacije */
  oslobodi_stablo(&pomocni_skup);

  /* Kreira se razlika skupova: prvo se napravi kopija prvog skupa
     kako bi se isti mogao iskoristiti i za preostale operacije */
  if (kopiraj_stablo(skup1, &pomocni_skup) == 1) {
    oslobodi_stablo(&skup1);
    oslobodi_stablo(&pomocni_skup);
    return 0;
  }
  if (kreiraj_razliku(&pomocni_skup, skup2) == 1) {
    oslobodi_stablo(&pomocni_skup);
    oslobodi_stablo(&skup2);
    return 0;
  }
  printf("Razlika: ");
  ispisi_stablo_infiksno(pomocni_skup);
  putchar('\n');

  /* Oslobadja se memorija zauzeta pomocnim skupom sa rezultatom
     operacije */
  oslobodi_stablo(&pomocni_skup);

  /* Oslobadja se memorija zauzeta polaznim skupovima */
  oslobodi_stablo(&skup1);
  oslobodi_stablo(&skup2);

  return 0;
}
