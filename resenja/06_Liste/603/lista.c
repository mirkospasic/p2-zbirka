#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Pomocna funkcija koja kreira cvor. Funkcija vrednost novog
   cvora inicijalizuje na broj, dok pokazivac na sledeci cvor u
   novom cvoru postavlja na NULL. Funkcija vraca pokazivac na
   novokreirani cvor ili NULL ako alokacija nije uspesno
   izvrsena. */
Cvor *napravi_cvor(int broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove
   liste ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave)
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
}

/* Funkcija dodaje novi cvor na pocetak liste. Kreira novi cvor
   koriscenjem funkcije napravi_cvor() i uvezuje ga na pocetak.
   Vraca 1 ukoliko je bilo greski pri alokaciji memorije, inace
   vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Sledbenik novog cvora je glava stare liste */
  novi->sledeci = *adresa_glave;
  /* Ako stara lista nije bila prazna, onda prethodni od glave
     treba da bude nov cvor. */
  if (*adresa_glave != NULL)
    (*adresa_glave)->prethodni = novi;
  /* Novi cvor je nova glava liste. */
  *adresa_glave = novi;

  return 0;
}

/* Funkcija pronalazi i vraca pokazivac na poslednji cvor liste, 
   ili NULL ukoliko je lista prazna. */
Cvor *pronadji_poslednji(Cvor * glava)
{
  /* U praznoj listi nema ni poslednjeg cvora i vraca se NULL. */
  if (glava == NULL)
    return NULL;

  /* Sve dok glava ne pokazuje na cvor koji nema sledeceg,
     pokazivac glava se pomera na sledeci cvor. Nakon izlaska iz 
     petlje, glava ce pokazivati na cvor liste koji nema
     sledeceg, tj, poslednji je cvor liste, vraca se vrednost
     pokazivaca glava. Pokazivac glava je argument funkcije i
     njegove promene nece se odraziti na vrednost pokazivaca
     glava u pozivajucoj funkciji. */
  while (glava->sledeci != NULL)
    glava = glava->sledeci;

  return glava;
}

/* Funkcija dodaje broj na kraj liste. Ukoliko dodje do greske
   pri alokaciji memorije vratice 1, inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* U slucaju prazne liste, glava nove liste je upravo novi
     cvor i ujedno i cela lista. Azurira se vrednost na koju
     pokazuje adresa_glave i tako se azurira i pokazivacka
     promenljivu u pozivajucoj funkciji. */
  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    return 0;
  }

  /* Kako lista nije prazna, pronalazi se poslednji cvor i novi
     cvor se dodaje na kraj liste kao sledbenik poslednjeg. */
  Cvor *poslednji = pronadji_poslednji(*adresa_glave);
  poslednji->sledeci = novi;
  novi->prethodni = poslednji;

  return 0;
}

/* Pomocna funkcija pronalazi cvor u listi iza koga treba
   umetnuti nov cvor sa vrednoscu broj. */
Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj)
{
  /* U praznoj listi nema takvog mesta i vraca se NULL. */
  if (glava == NULL)
    return NULL;

  /* Pokazivac glava se pomera na sledeci cvor sve dok ne bude
     pokazivala na cvor ciji je sledeci ili ne postoji ili ima
     vrednost vecu ili jednaku vrednosti novog cvora.

     Zbog izracunavanja izraza u C-u prvi deo konjukcije mora
     biti provera da li se doslo do poslednjeg cvora liste pre
     nego sto se proveri vrednost njegovog sledeceg cvora, jer u 
     slucaju poslednjeg, sledeci ne postoji, pa ni njegova
     vrednost. */
  while (glava->sledeci != NULL
         && glava->sledeci->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje se moglo izaci pomeranjem pokazivaca glava do
     poslednjeg cvora ili, ranije, na cvoru ciji sledeci ima
     vrednost vecu od broj. */
  return glava;
}

/* Funkcija uvezuje cvor novi iza cvora tekuci. */
void dodaj_iza(Cvor * tekuci, Cvor * novi)
{
  novi->sledeci = tekuci->sledeci;
  novi->prethodni = tekuci;

  /* Ako tekuci ima sledeceg, onda se sledecem dodeljuje
     prethodnik i tekuci dobija novog sledeceg postavljanjem
     pokazivaca na ispravne adrese. */
  if (tekuci->sledeci != NULL)
    tekuci->sledeci->prethodni = novi;
  tekuci->sledeci = novi;
}

/* Fukcija dodaje u listu nov cvor na odgovarajuce mesto, tako
   sto pronalazi cvor u listi iza kod treba uvezati nov cvor.
   Ukoliko dodje do greske pri alokaciji memorije vratice 1,
   inace vraca 0. */
int dodaj_sortirano(Cvor ** adresa_glave, int broj)
{
  /* Ako je lista prazna, glava nove liste je novi cvor. */
  if (*adresa_glave == NULL) {
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;
    *adresa_glave = novi;
    return 0;
  }

  /* Ukoliko je vrednost glave liste veca ili jednaka od nove
     vrednosti onda nov cvor treba staviti na pocetak liste. */
  if ((*adresa_glave)->vrednost >= broj) {
    dodaj_na_pocetak_liste(adresa_glave, broj);
    return 0;
  }

  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Pronazi se cvor iza koga treba uvezti nov cvor. */
  Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
  dodaj_iza(pomocni, novi);

  return 0;
}

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom
   broju. Vraca pokazivac na cvor liste u kome je sadrzan
   trazeni broj ili NULL u slucaju da takav cvor ne postoji u
   listi. */
Cvor *pretrazi_listu(Cvor * glava, int broj)
{
  for (; glava != NULL; glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vraca se NULL. */
  return NULL;
}

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom
   broju. Funkcija se u pretrazi oslanja na cinjenicu da je
   lista koja se pretrazuje neopadajuce sortirana. Vraca
   pokazivac na cvor liste u kome je sadrzan trazeni broj ili
   NULL u slucaju da takav cvor ne postoji u listi.  */
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

/* Funkcija brise u listi na koju pokazuje pokazivac glava onaj
   cvor na koji pokazuje pokazivac tekuci. Obratiti paznju da je
   kod dvostruke liste ovo mnogo lakse uraditi jer cvor tekuci
   sadrzi pokazivace na svog sledbenika i prethodnika u listi. */
void obrisi_tekuci(Cvor ** adresa_glave, Cvor * tekuci)
{
  /* Ako je tekuci NULL pokazivac, nema sta da se brise. */
  if (tekuci == NULL)
    return;

  /* Ako postoji prethodnik od tekuceg, onda se postavlja da
     njegov sledeci bude sledeci od tekuceg. */
  if (tekuci->prethodni != NULL)
    tekuci->prethodni->sledeci = tekuci->sledeci;

  /* Ako postoji sledbenik tekuceg (cvora koji se brise), onda
     njegov prethodnik treba da bude prethodnik tekuceg. */
  if (tekuci->sledeci != NULL)
    tekuci->sledeci->prethodni = tekuci->prethodni;

  /* Ako je glava cvor koji se brise, glava nove liste ce biti
     sledbenik od stare glave. */
  if (tekuci == *adresa_glave)
    *adresa_glave = tekuci->sledeci;

  /* Oslobadja se dinamicki alociran prostor za cvor tekuci. */
  free(tekuci);
}

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Funkcija azurira pokazivac na glavu liste, koji moze biti
   promenjen u slucaju da se obrise stara glava. */
void obrisi_cvor(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = *adresa_glave;

  while ((tekuci = pretrazi_listu(*adresa_glave, broj)) != NULL)
    obrisi_tekuci(adresa_glave, tekuci);
}

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj,
   oslanjajuci se na cinjenicu da je prosledjena lista
   neopadajuce sortirana. Funkcija azurira pokazivac na glavu
   liste, koji moze biti promenjen ukoliko se obrise stara glava 
   liste. */
void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = *adresa_glave;

  while ((tekuci =
          pretrazi_sortiranu_listu(*adresa_glave, broj)) != NULL)
    obrisi_tekuci(adresa_glave, tekuci);
}

/* Funkcija prikazuje cvorove liste pocev od glave ka kraju
   liste. Ne salje joj se adresa promenljive koja cuva glavu
   liste, jer ova funkcija nece menjati listu, pa nema ni
   potrebe da azuriza pokazivac na glavu liste iz pozivajuce
   funkcije. */
void ispisi_listu(Cvor * glava)
{
  putchar('[');
  for (; glava != NULL; glava = glava->sledeci) {
    printf("%d", glava->vrednost);
    if (glava->sledeci != NULL)
      printf(", ");
  }

  printf("]\n");
}

/* Funkcija prikazuje cvorove liste pocev od kraja ka glavi
   liste. */
void ispisi_listu_u_nazad(Cvor * glava)
{
  putchar('[');
  if (glava == NULL) {
    printf("]\n");
    return;
  }

  glava = pronadji_poslednji(glava);

  for (; glava != NULL; glava = glava->prethodni) {
    printf("%d", glava->vrednost);
    if (glava->prethodni != NULL)
      printf(", ");
  }
  printf("]\n");
}
