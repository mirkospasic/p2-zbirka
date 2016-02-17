#include <stdio.h>
#include <stdlib.h>
#include "dvostruko_povezana_lista.h"

Cvor *napravi_cvor(int broj)
{
  /* Alokacija memorije za novi cvor uz proveru uspesnosti alokacije */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja strukture */
  novi->vrednost = broj;
  novi->sledeci = NULL;

  /* Vracanje adrese novog cvora */
  return novi;
}

void oslobodi_listu(Cvor ** adresa_glave, Cvor ** adresa_kraja)
{
  Cvor *pomocni = NULL;

  /* Ako lista nije prazna, onda treba osloboditi memoriju */
  while (*adresa_glave != NULL) {
    /* Potrebno je prvo zapamtiti adresu sledeceg cvora i onda
       osloboditi memoriju cvora koji predstavlja glavu liste */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    /* Sledeci cvor je nova glava liste */
    *adresa_glave = pomocni;
  }
  /* Nakon izlaska iz petlje lista je prazna. Pokazivac na kraj liste 
     treba postaviti na NULL */
  *adresa_kraja = NULL;
}

int dodaj_na_pocetak_liste(Cvor ** adresa_glave, Cvor **
                           adresa_kraja, int broj)
{
  /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Sledbenik novog cvora je glava stare liste */
  novi->sledeci = *adresa_glave;

  /* Ako stara lista nije bila prazna, onda prethodni cvor glave
     treba da bude novi cvor. Inace, novi cvor je ujedno i pocetni i
     krajnji */
  if (*adresa_glave != NULL)
    (*adresa_glave)->prethodni = novi;
  else
    *adresa_kraja = novi;

  /* Novi cvor je nova glava liste */
  *adresa_glave = novi;

  /* Vracanje indikatora uspesnog dodavanja */
  return 0;
}

int dodaj_na_kraj_liste(Cvor ** adresa_glave, Cvor ** adresa_kraja,
                        int broj)
{
  /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* U slucaju prazne liste, glava nove liste je upravo novi cvor i
     ujedno i cela lista. Azurira se vrednost na koju pokazuju
     adresa_glave i adresa_kraja */
  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    *adresa_kraja = novi;
  } else {
    /* Ako lista nije prazna, novi cvor se dodaje na kraj liste kao
       sledbenik poslednjeg cvora i azurira se samo pokazivac na kraj 
       liste */
    (*adresa_kraja)->sledeci = novi;
    novi->prethodni = (*adresa_kraja);
    *adresa_kraja = novi;
  }

  /* Vracanje indikatora uspesnog dodavanja */
  return 0;
}

Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj)
{
  /* U praznoj listi nema takvog mesta i vraca se NULL */
  if (glava == NULL)
    return NULL;

  /* Pokazivac glava se pomera na sledeci cvor sve dok ne bude
     pokazivala na cvor ciji sledeci cvor ili ne postoji ili ima
     vrednost vecu ili jednaku od vrednosti novog cvora.

     Zbog izracunavanja izraza u C-u prvi deo konjunkcije mora biti
     provera da li se doslo do poslednjeg cvora liste pre nego sto se 
     proveri vrednost u sledecem cvoru jer u slucaju poslednjeg,
     sledeci ne postoji pa ni njegova vrednost. */
  while (glava->sledeci != NULL && glava->sledeci->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje se moglo izaci pomeranjem pokazivaca glava do
     poslednjeg cvora ili, ranije, nailaskom na cvor ciji sledeci ima 
     vrednost vecu od broj */
  return glava;
}

int dodaj_iza(Cvor * tekuci, int broj)
{
  /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  novi->sledeci = tekuci->sledeci;
  novi->prethodni = tekuci;

  /* Ako tekuci ima sledeceg, onda se sledecem dodeljuje prethodnik,
     a potom i tekuci dobija novog sledeceg postavljanjem pokazivaca
     na ispravne adrese */
  if (tekuci->sledeci != NULL)
    tekuci->sledeci->prethodni = novi;
  tekuci->sledeci = novi;

  /* Vracanje indikatora uspesnog dodavanja */
  return 0;
}

int dodaj_sortirano(Cvor ** adresa_glave, Cvor ** adresa_kraja, int
                    broj)
{
  /* Ako je lista prazna, novi cvor je i prvi i poslednji cvor liste */
  if (*adresa_glave == NULL) {
    /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;

    /* Azuriranje vrednosti pocetka i kraja liste */
    *adresa_glave = novi;
    *adresa_kraja = novi;

    /* Vracanje indikatora uspesnog dodavanja */
    return 0;
  }

  /* Ukoliko je vrednost glave liste veca ili jednaka od nove
     vrednosti onda novi cvor treba staviti na pocetak liste */
  if ((*adresa_glave)->vrednost >= broj) {
    return dodaj_na_pocetak_liste(adresa_glave, adresa_kraja, broj);
  }

  /* Nalazenje cvora iza koga treba uvezati novi cvor */
  Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
  /* Dodaje se novi cvor uz proveru uspesnosti dodavanja */
  if (dodaj_iza(pomocni, broj) == 1)
    return 1;
  /* Ako pomocni cvor pokazuje na poslednji element liste, onda je
     novi cvor poslednji u listi. */
  if (pomocni == *adresa_kraja)
    *adresa_kraja = pomocni->sledeci;

  return 0;
}

Cvor *pretrazi_listu(Cvor * glava, int broj)
{
  /* Obilazenje cvorova liste */
  for (; glava != NULL; glava = glava->sledeci)
    /* Ako je vrednost tekuceg cvora jednaka zadatom broju, pretraga
       se obustavlja */
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vraca se NULL */
  return NULL;
}

Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
  /* Obilazenje cvorova liste */
  /* U uslovu ostanka u petlji, bitan je redosled u konjunkciji */
  for (; glava != NULL && glava->vrednost <= broj;
       glava = glava->sledeci)
    /* Ako je vrednost tekuceg cvora jednaka zadatom broju, pretraga
       se obustavlja */
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i bice vraceno NULL */
  return NULL;
}

/* Kod dvostruko povezane liste brisanje odredjenog cvora se moze
   lako realizovati jer on sadrzi pokazivace na svog sledbenika i
   prethodnika u listi. U funkciji se bise cvor zadat argumentom
   tekuci */
void obrisi_tekuci(Cvor ** adresa_glave, Cvor ** adresa_kraja, Cvor *
                   tekuci)
{
  /* Ako je tekuci NULL pokazivac, nema potrebe za brisanjem */
  if (tekuci == NULL)
    return;

  /* Ako postoji prethodnik tekuceg cvora, onda se postavlja da
     njegov sledbenik bude sledbenik tekuceg cvora */
  if (tekuci->prethodni != NULL)
    tekuci->prethodni->sledeci = tekuci->sledeci;

  /* Ako postoji sledbenik tekuceg cvora, onda njegov prethodnik
     treba da bude prethodnik tekuceg cvora */
  if (tekuci->sledeci != NULL)
    tekuci->sledeci->prethodni = tekuci->prethodni;

  /* Ako je glava cvor koji se brise, nova glava liste ce biti
     sledbenik stare glave */
  if (tekuci == *adresa_glave)
    *adresa_glave = tekuci->sledeci;

  /* Ako je cvor koji se brise poslednji u listi, azurira se i
     pokazivac na kraj liste */
  if (tekuci == *adresa_kraja)
    *adresa_kraja = tekuci->prethodni;

  /* Oslobadjanje dinamicki alociranog prostora za cvor tekuci */
  free(tekuci);
}

void obrisi_cvor(Cvor ** adresa_glave, Cvor ** adresa_kraja, int broj)
{
  Cvor *tekuci = *adresa_glave;

  /* Sve dok ima cvorova cija je vrednost jednaka zadatom broju,
     takvi cvorovi se brisu iz liste. */
  while ((tekuci = pretrazi_listu(*adresa_glave, broj)) != NULL)
    obrisi_tekuci(adresa_glave, adresa_kraja, tekuci);
}

void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, Cvor **
                                 adresa_kraja, int broj)
{
  Cvor *tekuci = *adresa_glave;

  /* Sve dok ima cvorova cija je vrednost jednaka zadatom broju,
     takvi cvorovi se brisu iz liste. */
  while ((tekuci =
          pretrazi_sortiranu_listu(*adresa_glave, broj)) != NULL)
    obrisi_tekuci(adresa_glave, adresa_kraja, tekuci);
}

void ispisi_listu(Cvor * glava)
{
  putchar('[');
  /* Ispisivanje vrednosti u cvorovima liste od pocetka prema kraju
     liste, unutar zagrada */
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
  /* Ispisivanje vrednosti u cvorovima liste od kraja prema pocetku
     liste, unutar zagrada */
  for (; kraj != NULL; kraj = kraj->prethodni) {
    printf("%d", kraj->vrednost);
    if (kraj->prethodni != NULL)
      printf(", ");
  }
  printf("]\n");
}
