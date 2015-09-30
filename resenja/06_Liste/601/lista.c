#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Cvor *napravi_cvor(int broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

void oslobodi_listu(Cvor ** adresa_glave)
{
  Cvor *pomocni = NULL;

  /* Ako lista nije prazna, onda treba osloboditi memoriju. */
  while (*adresa_glave != NULL) {
    /* Potrebno je prvo zapamtiti adresu sledeceg cvora i onda
       osloboditi cvor koji predstavlja glavu liste */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    /* Sledeci cvor je nova glava liste. */
    *adresa_glave = pomocni;
  }
}

int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreira se nov cvor i proverava se da li je bilo greske pri
     alokaciji. */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Novi cvor se uvezuje na pocetak i postaje nova glave liste. */
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;

  return 0;
}

Cvor *pronadji_poslednji(Cvor * glava)
{
  /* U praznoj listi nema ni poslednjeg cvora i vraca se NULL. */
  if (glava == NULL)
    return NULL;

  /* Sve dok glava pokazuje na cvor koji ima sledeceg, pokazivac
     glava se pomera na sledeci cvor. Nakon izlaska iz petlje, glava
     ce pokazivati na cvor liste koji nema sledeceg, tj. na poslednji
     cvor liste i vraca se vrednost pokazivaca glava.

     Pokazivac glava je argument funkcije i njegove promene nece se
     odraziti na vrednost pokazivaca glava u pozivajucoj funkciji. */
  while (glava->sledeci != NULL)
    glava = glava->sledeci;

  return glava;
}

int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* U slucaju prazne liste, glava nove liste je upravo novi cvor i
     ujedno i cela lista. Azurira se vrednost na koju pokazuje
     adresa_glave i tako se azurira i pokazivacka promenljiva u
     pozivajucoj funkciji. */
  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    return 0;
  }

  /* Kako lista nije prazna, pronalazi se poslednji cvor i novi cvor
     se dodaje na kraj liste kao sledbenik poslednjeg. */
  Cvor *poslednji = pronadji_poslednji(*adresa_glave);
  poslednji->sledeci = novi;

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
  /* Novi cvor se dodaje iza tekuceg cvora. */
  novi->sledeci = tekuci->sledeci;
  tekuci->sledeci = novi;
}

int dodaj_sortirano(Cvor ** adresa_glave, int broj)
{
  /* U slucaju prazne liste glava nove liste je novi cvor. Ukoliko je 
     doslo do greske pri alokaciji memorije vraća se 1. */
  if (*adresa_glave == NULL) {
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;
    *adresa_glave = novi;
    return 0;
  }

  /* Lista nije prazna. */
  /* Ako je broj manji ili jednak vrednosti u glavi liste, onda ga
     treba dodati na pocetak liste. */
  if ((*adresa_glave)->vrednost >= broj) {
    return dodaj_na_pocetak_liste(adresa_glave, broj);
  }

  /* U slucaju da je glava liste cvor sa vrednoscu manjom od broj,
     tada se pronalazi cvor liste iza koga treba uvezati nov cvor. */
  Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Uvezuje se novi cvor iza pomocnog. */
  dodaj_iza(pomocni, novi);
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

  return NULL;
}

void obrisi_cvor(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = NULL;
  Cvor *pomocni = NULL;

  /* Sa pocetka liste se brisu svi cvorovi koji su jednaki datom
     broju, i azurira se pokazivac na glavu liste. */
  while (*adresa_glave != NULL && (*adresa_glave)->vrednost == broj) {
    /* Adresu repa liste treba sacuvati pre oslobadjanja cvora na
       adresi adresa_glave. */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }

  /* Ako je nakon toga lista ostala prazna, izlazi se iz funkcije. */
  if (*adresa_glave == NULL)
    return;

  /* Od ovog trenutka, u svakoj iteraciji petlje tekuci pokazuje na
     cvor cija vrednost je razlicita od trazenog broja. Isto vazi i
     za sve cvorove levo od tekuceg. Poredi se vrednost sledeceg
     cvora (ako postoji) sa trazenim brojem. Cvor se brise ako je
     jednak, ili, ako je razlicit, prelazi se na sledeci cvor. Ovaj
     postupak se ponavlja dok se ne dodje do poslednjeg cvora. */
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL)
    if (tekuci->sledeci->vrednost == broj) {
      /* tekuci->sledeci treba obrisati, zbog toga se njegova adresa
         prvo cuva u pomocni. */
      pomocni = tekuci->sledeci;
      /* Tekucem se preusmerava pokazivac sledeci, preskakanjem
         njegovog trenutnog sledeceg. Njegov novi sledeci ce biti
         sledeci od cvora koji se brise. */
      tekuci->sledeci = pomocni->sledeci;
      /* Sada treba osloboditi cvor sa vrednoscu broj. */
      free(pomocni);
    } else {
      /* Inace, ne treba brisati sledeceg od tekuceg i pokazivac se
         pomera na sledeci. */
      tekuci = tekuci->sledeci;
    }
  return;
}

void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = NULL;
  Cvor *pomocni = NULL;

  /* Sa pocetka liste se brisu svi cvorovi koji su jednaki datom
     broju i azurira se pokazivac na glavu liste. */
  while (*adresa_glave != NULL && (*adresa_glave)->vrednost == broj) {
    /* Adresu repa liste treba sacuvati pre oslobadjanja cvora na
       adresi adresa_glave. */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }

  /* Ako je nakon toga lista ostala prazna, funkcija se prekida. Isto 
     se radi i ukoliko glava liste sadrzi vrednost koja je veca od
     broja, jer kako je lista sortirana rastuce nema potrebe broj
     traziti u repu liste. */
  if (*adresa_glave == NULL || (*adresa_glave)->vrednost > broj)
    return;

  /* Od ovog trenutka se u svakoj iteraciji pokazivac tekuci pokazuje 
     na cvor cija vrednost je manja od trazenog broja, kao i svim
     cvorovima levo od njega. Cvor se brise ako je jednak, ili, ako
     je razlicit, prelazi se na sledeci cvor. Ovaj postupak se
     ponavlja dok se ne dodje do poslednjeg cvora ili prvog cvora
     cija vrednost je veca od trazenog broja. */
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL && tekuci->sledeci->vrednost <= broj)
    if (tekuci->sledeci->vrednost == broj) {
      pomocni = tekuci->sledeci;
      tekuci->sledeci = tekuci->sledeci->sledeci;
      free(pomocni);
    } else {
      /* Ne treba brisati sledeceg od tekuceg jer je manji od
         trazenog i tekuci se pomera na sledeci cvor. */
      tekuci = tekuci->sledeci;
    }
  return;
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
