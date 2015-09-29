#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Pomocna funkcija koja kreira cvor. Funkcija vrednost novog cvora
   inicijalizuje na broj, dok pokazivac na sledeci cvor u novom cvoru 
   postavlja na NULL. Funkcija vraca pokazivac na novokreirani cvor
   ili NULL ako alokacija nije uspesno izvrsena.  */
Cvor *napravi_cvor(int broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove liste
   ciji se pocetni cvor nalazi na adresi adresa_glave. */
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

/* Funkcija dodaje broj na pocetak liste. Kreira novi cvor
   koriscenjem funkcije napravi_cvor i uvezuje ga na pocetak.
   Funkcija treba da vrati 0 ukoliko je sve bilo u redu, odnosno 1
   ukoliko je doslo do greske prilikom alokacije memorije za nov
   cvor. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreira se nov cvor i proverava se da li je bilo greske pri
     alokaciji */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Novi cvor se uvezuje na pocetak, i tako postaje nova glave
     liste. */
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;

  return 0;
}

/* Funkcija pronalazi i vraca pokazivac na poslednji cvor liste, ili
   NULL ukoliko je lista prazna. */
Cvor *pronadji_poslednji(Cvor * glava)
{
  /* U praznoj listi nema ni poslednjeg cvora i vraca se NULL. */
  if (glava == NULL)
    return NULL;

  /* Sve dok glava ne pokazuje na cvor koji nema sledeceg, pokazivac
     glava se pomera na sledeci cvor. Nakon izlaska iz petlje, glava 
     ce pokazivati na cvor liste koji nema sledeceg, tj, poslednji je 
     cvor liste, vraca se vrednost pokazivaca glava. Pokazivac glava
     je argument funkcije i njegove promene nece se odraziti na
     vrednost pokazivaca glava u pozivajucoj funkciji. */
  while (glava->sledeci != NULL)
    glava = glava->sledeci;

  return glava;
}

/* Funkcija dodaje broj na kraj liste. Ukoliko dodje do greske pri
   alokaciji memorije vratice 1, inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* U slucaju prazne liste, glava nove liste je upravo novi cvor i
     ujedno i cela lista. Azurira se vrednost na koju pokazuje
     adresa_glave i tako se azurira i pokazivacka promenljivu u
     pozivajucoj funkciji. */
  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    return 0;
  }

  /* Ako lista nije prazna, pronalazi se poslednji cvor i novi cvor
     se dodaje na kraj liste kao sledbenik poslednjeg. */
  Cvor *poslednji = pronadji_poslednji(*adresa_glave);
  poslednji->sledeci = novi;

  return 0;
}

/* Pomocna funkcija pronalazi cvor u listi iza koga treba umetnuti
   nov cvor sa vrednoscu broj. */
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
     proveri vrednost njegovog sledeceg cvora, jer u slucaju
     poslednjeg, sledeci ne postoji, pa ni njegova vrednost. */
  while (glava->sledeci != NULL && glava->sledeci->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje se moglo izaci pomeranjem pokazivaca glava do
     poslednjeg cvora ili, ranije, na cvoru ciji sledeci ima vrednost 
     vecu od broj. */
  return glava;
}

/* Funkcija uvezuje cvor novi iza cvora tekuci. */
void dodaj_iza(Cvor * tekuci, Cvor * novi)
{
  /* Novi cvor se dodaje iza tekuceg cvora. */
  novi->sledeci = tekuci->sledeci;
  tekuci->sledeci = novi;
}

/* Funkcija dodaje broj u sortiranu listu tako da lista ostane
   sortirana. Vraca 1 ukoliko je bilo greski pri alokaciji memorije,
   inace vraca 0. */
int dodaj_sortirano(Cvor ** adresa_glave, int broj)
{
  /* U slucaju prazne liste glava nove liste je novi cvor. */
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
     tada se pronalazi cvor liste iza koga treba da se umetne nov
     broj. */
  Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Uvezuje se novi cvor iza pomocnog. */
  dodaj_iza(pomocni, novi);
  return 0;
}

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Vraca pokazivac na cvor liste u kome je sadrzan trazeni broj ili
   NULL u slucaju da takav cvor ne postoji u listi. */
Cvor *pretrazi_listu(Cvor * glava, int broj)
{
  for (; glava != NULL; glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vraca se NULL. */
  return NULL;
}

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Vraca pokazivac na cvor liste u kome je sadrzan trazeni broj ili
   NULL u slucaju da takav cvor ne postoji u listi. Funkcija se u
   pretrazi oslanja na cinjenicu da je lista koja se pretrazuje
   neopadajuce sortirana. */
Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
  /* U uslovu ostanka u petlji, bitan je redosled u konjukciji. */
  for (; glava != NULL && glava->vrednost <= broj;
       glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  return NULL;
}

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Funkcija azurira pokazivac na glavu liste, koji moze biti
   promenjen u slucaju da se obrise stara glava. */
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
         sledeci od ovog cvor koji se brise. */
      tekuci->sledeci = pomocni->sledeci;
      /* Sada treba osloboditi cvor sa vrednoscu broj. */
      free(pomocni);
    } else {
      /* Ne treba brisati sledeceg od tekuceg i pokazivac se pomera
         dalje. */
      tekuci = tekuci->sledeci;
    }
  return;
}

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj,
   oslanjajuci se na cinjenicu da je prosledjena lista sortirana
   neopadajuce. Funkcija azurira pokazivac na glavu liste, koji moze
   biti promenjen ukoliko se obrise stara glava liste. */
void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj)
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

  /* Ako je nakon toga lista ostala prazna, funkcija se prekida.
     Isto se radi i ukoliko glava liste sadrzi vrednost koja je veca
     od broja, jer kako je lista sortirana rastuce nema potrebe broj
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
      /* Ne treba brisati sledeceg od tekuceg, jer je manji od
         trazenog i prelazi se na sledeci. */
      tekuci = tekuci->sledeci;
    }
  return;
}

/* Funkcija prikazuje vrednosti cvorova liste pocev od glave ka kraju 
   liste. Ne salje joj se adresa promenljive koja cuva glavu liste,
   jer ova funkcija nece menjati listu, pa nema ni potrebe da azuriza 
   pokazivac na glavu liste iz pozivajuce funkcije. */
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
