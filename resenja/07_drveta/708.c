#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija kreira novo stablo identicno stablu koje je dato korenom. 
 */
void kopiraj_stablo(Cvor * koren, Cvor ** duplikat)
{
  /* Izlaz iz rekurzije */
  if (koren == NULL) {
    *duplikat = NULL;
    return;
  }

  /* Duplira se koren stabla i postavlja da bude koren novog stabla */
  *duplikat = napravi_cvor(koren->broj);
  proveri_alokaciju(*duplikat);

  /* Rekurzivno se duplira levo podstablo i njegova adresa se cuva u
     pokazivacu na levo podstablo korena duplikata. */
  kopiraj_stablo(koren->levo, &(*duplikat)->levo);

  /* Rekurzivno se duplira desno podstablo i njegova adresa se cuva u 
     pokazivacu na desno podstablo korena duplikata. */
  kopiraj_stablo(koren->desno, &(*duplikat)->desno);
}

/* Funkcija izracunava uniju dva skupa predstavljena stablima -
   rezultujuci skup tj. stablo se dobija modifikacijom prvog stabla */
void kreiraj_uniju(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako drugo stablo nije prazno */
  if (koren2 != NULL) {
    /* Dodaje se njegov koren u prvo stablo */
    dodaj_u_stablo(adresa_korena1, koren2->broj);

    /* Rekurzivno se racuna unija levog i desnog podstabla drugog
       stabla sa prvim stablom */
    kreiraj_uniju(adresa_korena1, koren2->levo);
    kreiraj_uniju(adresa_korena1, koren2->desno);
  }
}

/* Funkcija izracunava presek dva skupa predstavljana stablima -
   rezultujuci skup tj. stablo se dobija modifikacijom prvog stabla */
void kreiraj_presek(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako je prvo stablo prazno, tada je i rezultat prazno stablo */
  if (*adresa_korena1 == NULL)
    return;

  /* Inace... */
  /* Kreira se presek levog i desnog podstabla sa drugim stablom, tj. 
     iz levog i desnog podstabla prvog stabla brisu se svi oni
     elementi koji ne postoje u drugom stablu */
  kreiraj_presek(&(*adresa_korena1)->levo, koren2);
  kreiraj_presek(&(*adresa_korena1)->desno, koren2);

  /* Ako se koren prvog stabla ne nalazi u drugom stablu tada se on
     uklanja iz prvog stabla */
  if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) == NULL)
    obrisi_element(adresa_korena1, (*adresa_korena1)->broj);
}

/* Funkcija izracunava razliku dva skupa predstavljana stablima -
   rezultujuci skup tj. stablo se dobija modifikacijom prvog stabla */
void kreiraj_razliku(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako je prvo stablo prazno, tada je i rezultat prazno stablo */
  if (*adresa_korena1 == NULL)
    return;

  /* Inace... */
  /* Kreira se razlika levog i desnog podstabla sa drugim stablom,
     tj. iz levog i desnog podstabla prvog stabla se brisu svi oni
     elementi koji postoje i u drugom stablu */
  kreiraj_razliku(&(*adresa_korena1)->levo, koren2);
  kreiraj_razliku(&(*adresa_korena1)->desno, koren2);

  /* Ako se koren prvog stabla nalazi i u drugom stablu tada se isti
     uklanja iz prvog stabla */
  if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) != NULL)
    obrisi_element(adresa_korena1, (*adresa_korena1)->broj);
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
    dodaj_u_stablo(&skup1, n);
  }

  /* Ucitavaju se elementi drugog skupa */
  skup2 = NULL;
  printf("Drugi skup: ");
  while (scanf("%d", &n) != EOF) {
    dodaj_u_stablo(&skup2, n);
  }

  /* Kreira se unija skupova: prvo se napravi kopija prvog skupa kako 
     bi se isti mogao iskoristiti i za preostale operacije */
  kopiraj_stablo(skup1, &pomocni_skup);
  kreiraj_uniju(&pomocni_skup, skup2);
  printf("Unija: ");
  ispisi_stablo_infiksno(pomocni_skup);
  putchar('\n');

  /* Oslobadja se memorija zauzeta pomocnim skupom sa rezultatom
     operacije */
  oslobodi_stablo(&pomocni_skup);

  /* Kreira se presek skupova: prvo se napravi kopija prvog skupa
     kako bi se isti mogao iskoristiti i za preostale operacije */
  kopiraj_stablo(skup1, &pomocni_skup);
  kreiraj_presek(&pomocni_skup, skup2);
  printf("Presek: ");
  ispisi_stablo_infiksno(pomocni_skup);
  putchar('\n');

  /* Oslobadja se memorija zauzeta pomocnim skupom sa rezultatom
     operacije */
  oslobodi_stablo(&pomocni_skup);

  /* Kreira se razlika skupova: prvo se napravi kopija prvog skupa
     kako bi se isti mogao iskoristiti i za preostale operacije */
  kopiraj_stablo(skup1, &pomocni_skup);
  kreiraj_razliku(&pomocni_skup, skup2);
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
