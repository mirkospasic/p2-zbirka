#include <stdio.h>
#include <stdlib.h>
#include "dvostruko_povezana_lista.h"

Cvor *napravi_cvor(int broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

void oslobodi_listu(Cvor ** adresa_glave, Cvor ** adresa_kraja)
{
  Cvor *pomocni = NULL;

  /* Ako lista nije prazna, onda treba osloboditi memoriju. */
  while (*adresa_glave != NULL) {
    /* Potrebno je prvo zapamtiti adresu sledeceg cvora i onda
       osloboditi memoriju cvora koji predstavlja glavu liste. */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    /* Sledeci cvor je nova glava liste. */
    *adresa_glave = pomocni;
  }
  *adresa_kraja = NULL;
}

int dodaj_na_pocetak_liste(Cvor ** adresa_glave, Cvor **
                           adresa_kraja, int broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Sledbenik novog cvora je glava stare liste */
  novi->sledeci = *adresa_glave;
  /* Ako stara lista nije bila prazna, onda prethodni od glave treba
     da bude nov cvor. Inace, nov cvor je ujedno pocetni i krajnji. */
  if (*adresa_glave != NULL)
    (*adresa_glave)->prethodni = novi;
  else
    *adresa_kraja = novi;
  /* Novi cvor je nova glava liste. */
  *adresa_glave = novi;

  return 0;
}

int dodaj_na_kraj_liste(Cvor ** adresa_glave, Cvor ** adresa_kraja,
                        int broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* U slucaju prazne liste, glava nove liste je upravo novi cvor i
     ujedno i cela lista. Azurira se vrednost na koju pokazuju
     adresa_glave i adresa_kraja tako se azurira i pokazivacka
     promenljiva u pozivajucoj funkciji. */
  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    *adresa_kraja = novi;
    return 0;
  }

  /* Kako lista nije prazna, novi cvor se dodaje na kraj liste kao
     sledbenik poslednjeg i azurira se pokazivac na kraj u
     pozivajucoj funkciji. */
  (*adresa_kraja)->sledeci = novi;
  novi->prethodni = (*adresa_kraja);
  *adresa_kraja = novi;

  return 0;
}

Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj)
{
  /* U praznoj listi nema takvog mesta i vraca se NULL. */
  if (glava == NULL)
    return NULL;

  /* Pokazivac glava se pomera na sledeci cvor sve dok ne bude
     pokazivala na cvor ciji je sledeci ili ne postoji ili ima
     vrednost vecu ili jednaku vrednosti novog cvora.

     Zbog izracunavanja izraza u C-u prvi deo konjukcije mora biti
     provera da li se doslo do poslednjeg cvora liste pre nego sto se 
     proveri vrednost u sledecem cvoru, jer u slucaju poslednjeg,
     sledeci ne postoji, pa ni njegova vrednost. */
  while (glava->sledeci != NULL && glava->sledeci->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje se moglo izaci pomeranjem pokazivaca glava do
     poslednjeg cvora ili, ranije, na cvoru ciji sledeci ima vrednost 
     vecu od broj. */
  return glava;
}

void dodaj_iza(Cvor * tekuci, Cvor * novi)
{
  novi->sledeci = tekuci->sledeci;
  novi->prethodni = tekuci;

  /* Ako tekuci ima sledeceg, onda se sledecem dodeljuje prethodnik,
     a potom i tekuci dobija novog sledeceg postavljanjem pokazivaca
     na ispravne adrese. */
  if (tekuci->sledeci != NULL)
    tekuci->sledeci->prethodni = novi;
  tekuci->sledeci = novi;
}

int dodaj_sortirano(Cvor ** adresa_glave, Cvor ** adresa_kraja, int
                    broj)
{
  /* Ako je lista prazna, nov cvor je i prvi i poslednji cvor liste. */
  if (*adresa_glave == NULL) {
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;
    *adresa_glave = novi;
    *adresa_kraja = novi;
    return 0;
  }

  /* Ukoliko je vrednost glave liste veca ili jednaka od nove
     vrednosti onda nov cvor treba staviti na pocetak liste. */
  if ((*adresa_glave)->vrednost >= broj) {
    dodaj_na_pocetak_liste(adresa_glave, adresa_kraja, broj);
    return 0;
  }

  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Pronazi se cvor iza koga treba uvezati nov cvor. */
  Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
  dodaj_iza(pomocni, novi);
  /* Ako pomocni pokazuje na poslednji element onda je novi cvor
     poslednji u listi. */
  if (pomocni == *adresa_kraja)
    *adresa_kraja = novi;

  return 0;
}

Cvor *pretrazi_listu(Cvor * glava, int broj)
{
  for (; glava != NULL; glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vraca se NULL. */
  return NULL;
}

Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
  /* U uslovu ostanka u petlji, bitan je redosled u konjukciji. */
  for (; glava != NULL && glava->vrednost <= broj;
       glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i bice vraceno NULL. */
  return NULL;
}

/* Kod dvostruko povezane liste brisanje cvora na koji pokazuje
   tekuci moze se lako uraditi jer sadrzi pokazivace na svog
   sledbenika i prethodnika u listi. */
void obrisi_tekuci(Cvor ** adresa_glave, Cvor ** adresa_kraja, Cvor *
                   tekuci)
{
  /* Ako je tekuci NULL pokazivac, nema sta da se brise. */
  if (tekuci == NULL)
    return;

  /* Ako postoji prethodnik od tekuceg, onda se postavlja da njegov
     sledeci bude sledeci od tekuceg. */
  if (tekuci->prethodni != NULL)
    tekuci->prethodni->sledeci = tekuci->sledeci;

  /* Ako postoji sledbenik tekuceg, onda njegov prethodnik treba da
     bude prethodnik tekuceg. */
  if (tekuci->sledeci != NULL)
    tekuci->sledeci->prethodni = tekuci->prethodni;

  /* Ako je glava cvor koji se brise, nova glava liste bice sledbenik 
     stare glave. */
  if (tekuci == *adresa_glave)
    *adresa_glave = tekuci->sledeci;

  /* Ako je cvor koji se brise, poslednji u listi, azurira se i
     pokazivac na kraj liste u pozivajucoj funkciji. */
  if (tekuci == *adresa_kraja)
    *adresa_kraja = tekuci->prethodni;

  /* Oslobadja se dinamicki alociran prostor za cvor tekuci. */
  free(tekuci);
}

void obrisi_cvor(Cvor ** adresa_glave, Cvor ** adresa_kraja, int broj)
{
  Cvor *tekuci = *adresa_glave;

  while ((tekuci = pretrazi_listu(*adresa_glave, broj)) != NULL)
    obrisi_tekuci(adresa_glave, adresa_kraja, tekuci);
}

void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, Cvor **
                                 adresa_kraja, int broj)
{
  Cvor *tekuci = *adresa_glave;

  while ((tekuci =
          pretrazi_sortiranu_listu(*adresa_glave, broj)) != NULL)
    obrisi_tekuci(adresa_glave, adresa_kraja, tekuci);
}

void ispisi_listu(Cvor * glava)
{
  /* Funkciji se ne salje adresa promenljive koja cuva glavu liste,
     jer nece menjati listu, pa nema ni potrebe da azuriza pokazivac
     na glavu liste iz pozivajuce funkcije. */
  putchar('[');
  for (; glava != NULL; glava = glava->sledeci) {
    printf("%d", glava->vrednost);
    if (glava->sledeci != NULL)
      printf(", ");
  }

  printf("]\n");
}

void ispisi_listu_unazad(Cvor * kraj)
{
  putchar('[');
  if (kraj == NULL) {
    printf("]\n");
    return;
  }

  for (; kraj != NULL; kraj = kraj->prethodni) {
    printf("%d", kraj->vrednost);
    if (kraj->prethodni != NULL)
      printf(", ");
  }
  printf("]\n");
}
