#include <stdio.h>
#include <stdlib.h>

/* Uklucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija kreira novo stablo identicno stablu koje je dato
   korenom. */
void kopiraj_stablo(Cvor * koren, Cvor ** duplikat)
{
  /* Izlaz iz rekurzije */
  if (koren == NULL) {
    *duplikat = NULL;
    return;
  }

  /* Duplira se koren stabla i postavlja da bude koren novog 
     stabla */
  *duplikat = napravi_cvor(koren->broj);
  proveri_alokaciju(*duplikat);

  /* Rekurzivno se duplira levo podstablo i njegova adresa se cuva 
     u pokazivacu na levo podstablo korena duplikata. */
  kopiraj_stablo(koren->levo, &(*duplikat)->levo);

  /* Rekurzivno se duplira desno podstablo i njegova adresa se cuva
     u pokazivacu na desno podstablo korena duplikata. */
  kopiraj_stablo(koren->desno, &(*duplikat)->desno);
}

/* Funkcija izracunava uniju dva stabla - rezultujuce stablo se
   dobija modifikacijom prvog stabla */
void kreiraj_uniju(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako drugo stablo nije prazno */
  if (koren2 != NULL) {
    /* dodaje se njegov koren u prvo stablo */
    dodaj_u_stablo(adresa_korena1, koren2->broj);

    /* rekurzivno se racuna unija levog i desnog podstabla drugog 
       stabla sa prvim stablom */
    kreiraj_uniju(adresa_korena1, koren2->levo);
    kreiraj_uniju(adresa_korena1, koren2->desno);
  }
}

/* Funkcija izracunava presek dva stabla - rezultujuce stablo se 
   dobija modifikacijom prvog stabla */
void kreiraj_presek(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako je prvo stablo prazno, tada je i rezultat prazno stablo 
   */
  if (*adresa_korena1 == NULL)
    return;

  /* Kreira se presek levog i desnog podstabla sa drugim stablom, 
     tj. iz levog i desnog podstabla prvog stabla brisu se svi
     oni elementi koji ne postoje u drugom stablu */
  kreiraj_presek(&(*adresa_korena1)->levo, koren2);
  kreiraj_presek(&(*adresa_korena1)->desno, koren2);

  /* Ako se koren prvog stabla ne nalazi u drugom stablu tada se
     on uklanja iz prvog stabla */
  if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) == NULL)
    obrisi_element(adresa_korena1, (*adresa_korena1)->broj);
}

/* Funkcija izracunava razliku dva stabla - rezultujuce stablo
   se dobija modifikacijom prvog stabla */
void kreiraj_razliku(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako je prvo stablo prazno, tada je i rezultat prazno stablo 
   */
  if (*adresa_korena1 == NULL)
    return;

  /* Kreira se razlika levog i desnog podstabla sa drugim
     stablom, tj. iz levog i desnog podstabla prvog stabla
     se brisu svi oni elementi koji postoje i u drugom stablu */
  kreiraj_razliku(&(*adresa_korena1)->levo, koren2);
  kreiraj_razliku(&(*adresa_korena1)->desno, koren2);

  /* Ako se koren prvog stabla nalazi i u drugom stablu tada se isti
     uklanja iz prvog stabla */
  if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) != NULL)
    obrisi_element(adresa_korena1, (*adresa_korena1)->broj);
}

int main()
{
  Cvor *koren1;
  Cvor *koren2;
  Cvor *pomocni = NULL;
  int n;

  /* Ucitavanje elemenata prvog stabla: */
  koren1 = NULL;
  printf("Prvo stablo: ");
  while (scanf("%d", &n) != EOF) {
    dodaj_u_stablo(&koren1, n);
  }

  /* Ucitavanje elemenata drugog stabla: */
  koren2 = NULL;
  printf("Drugo stablo: ");
  while (scanf("%d", &n) != EOF) {
    dodaj_u_stablo(&koren2, n);
  }

  /* Kreira se unija stabala: prvo se napravi kopija prvog stabla
     kako bi se isto moglo iskoristiti i za preostale operacije */
  kopiraj_stablo(koren1, &pomocni);
  kreiraj_uniju(&pomocni, koren2);
  printf("Unija: ");
  prikazi_stablo(pomocni);
  putchar('\n');

  /* Oslobadja se stablo za rezultatom operacije */
  oslobodi_stablo(&pomocni);

  /* Kreira se presek stabala: prvo se napravi kopija prvog stabla 
     kako bi se isto moglo iskoristiti i za preostale operacije; */
  kopiraj_stablo(koren1, &pomocni);
  kreiraj_presek(&pomocni, koren2);
  printf("Presek: ");
  prikazi_stablo(pomocni);
  putchar('\n');

  /* Oslobadja se stablo za rezultatom operacije */
  oslobodi_stablo(&pomocni);

  /* Kreira se razlika stabala: prvo se napravi kopija prvog
     stabla kako bi se isto moglo iskoristiti i za preostale
     operacije; */
  kopiraj_stablo(koren1, &pomocni);
  kreiraj_razliku(&pomocni, koren2);
  printf("Razlika: ");
  prikazi_stablo(pomocni);
  putchar('\n');

  /* Oslobadja se stablo za rezultatom operacije */
  oslobodi_stablo(&pomocni);

  /* Oslobadjaju se i polazna stabla */
  oslobodi_stablo(&koren2);
  oslobodi_stablo(&koren1);

  return 0;
}
