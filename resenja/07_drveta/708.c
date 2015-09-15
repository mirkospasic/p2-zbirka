#include <stdio.h>
#include <stdlib.h>

/* Uklucujemo biblioteku za rad sa stablima */
#include "stabla.h"

/* Funkcija kreira novo stablo identicno stablu koje je dato
   korenom. */
void kopiraj_stablo(Cvor * koren, Cvor ** duplikat)
{
  /* Izlaz iz rekurzije: ako je stablo prazno nema sta da se
     kopira */
  if (koren == NULL) {
    *duplikat = NULL;
    return;
  }

  /* Dupliramo koren stabla i postavljamo ga da bude koren novog 
     stabla */
  *duplikat = napravi_cvor(koren->broj);
  proveri_alokaciju(*duplikat);

  /* Rekurzivno dupliramo levo podstablo i njegovu adresu cuvamo 
     u pokazivacu na levo podstablo korena duplikata. */
  kopiraj_stablo(koren->levo, &(*duplikat)->levo);

  /* Rekurzivno dupliramo desno podstablo i njegovu adresu
     cuvamo u pokazivacu na desno podstablo korena duplikata. */
  kopiraj_stablo(koren->desno, &(*duplikat)->desno);
}

/* Funkcija izracunava uniju dva stabla - rezultujuce stablo se
   dobija modifikacijom prvog stabla */
void kreiraj_uniju(Cvor ** adresa_korena1, Cvor * koren2)
{
  /* Ako drugo stablo nije prazno */
  if (koren2 != NULL) {
    /* dodajemo njegov koren u prvo stablo */
    dodaj_u_stablo(adresa_korena1, koren2->broj);

    /* rekurzivno racunamo uniju levog i desnog podstabla drugog 
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

  /* Kreiramo presek levog i desnog podstabla sa drugim stablom, 
     tj. iz levog i desnog podstabla prvog stabla brisemo sve
     one elemente koji ne postoje u drugom stablu */
  kreiraj_presek(&(*adresa_korena1)->levo, koren2);
  kreiraj_presek(&(*adresa_korena1)->desno, koren2);

  /* Ako se koren prvog stabla ne nalazi u drugom stablu tada ga 
     uklanjamo iz prvog stabla */
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

  /* Kreiramo razliku levog i desnog podstabla sa drugim
     stablom, tj. iz levog i desnog podstabla prvog stabla
     brisemo sve one elemente koji postoje i u drugom stablu */
  kreiraj_razliku(&(*adresa_korena1)->levo, koren2);
  kreiraj_razliku(&(*adresa_korena1)->desno, koren2);

  /* Ako se koren prvog stabla nalazi i u drugom stablu tada ga
     uklanjamo iz prvog stabla */
  if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) != NULL)
    obrisi_element(adresa_korena1, (*adresa_korena1)->broj);
}

int main()
{
  Cvor *koren1;
  Cvor *koren2;
  Cvor *pomocni = NULL;
  int n;

  /* Ucitavamo elemente prvog stabla: */
  koren1 = NULL;
  printf("Prvo stablo: ");
  while (scanf("%d", &n) != EOF) {
    dodaj_u_stablo(&koren1, n);
  }

  /* Ucitavamo elemente drugog stabla: */
  koren2 = NULL;
  printf("Drugo stablo: ");
  while (scanf("%d", &n) != EOF) {
    dodaj_u_stablo(&koren2, n);
  }

  /* Kreiramo uniju stabala: prvo napravimo kopiju prvog stabla
     kako bi mogli da ga iskoristimo i za preostale operacije */
  kopiraj_stablo(koren1, &pomocni);
  kreiraj_uniju(&pomocni, koren2);
  printf("Unija: ");
  prikazi_stablo(pomocni);
  putchar('\n');

  /* Oslobadjamo stablo za rezultatom operacije */
  oslobodi_stablo(&pomocni);

  /* Kreiramo presek stabala: prvo napravimo kopiju prvog stabla 
     kako bi mogli da ga iskoristimo i za preostale operacije; */
  kopiraj_stablo(koren1, &pomocni);
  kreiraj_presek(&pomocni, koren2);
  printf("Presek: ");
  prikazi_stablo(pomocni);
  putchar('\n');

  /* Oslobadjamo stablo za rezultatom operacije */
  oslobodi_stablo(&pomocni);

  /* Kreiramo razliku stabala: prvo napravimo kopiju prvog
     stabla kako bi mogli da ga iskoristimo i za preostale
     operacije; */
  kopiraj_stablo(koren1, &pomocni);
  kreiraj_razliku(&pomocni, koren2);
  printf("Razlika: ");
  prikazi_stablo(pomocni);
  putchar('\n');

  /* Oslobadjamo stablo za rezultatom operacije */
  oslobodi_stablo(&pomocni);

  /* Oslobadjamo i polazna stabla */
  oslobodi_stablo(&koren2);
  oslobodi_stablo(&koren1);

  /* Zavrsavamo sa programom */
  return 0;
}
