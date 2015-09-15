#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Pomocna funkcija koja kreira cvor. Funkcija vrednost
   novog cvora inicijalizuje na broj, dok pokazivac na
   sledeci cvor u novom cvoru postavlja na NULL.
   Funkcija vraca pokazivac na novokreirani cvor ili NULL
   ako alokacija nije uspesno izvrsena.  */
Cvor * napravi_cvor(int broj) 
{
  Cvor * novi = (Cvor *) malloc(sizeof(Cvor));
  if( novi == NULL )
    return NULL;

  /* Inicijalizacija polja u novom cvoru */
  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente 
   liste ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave) 
{
  Cvor *pomocni = NULL;

  /* Ako lista nije prazna, onda treba osloboditi memoriju. */
  while (*adresa_glave != NULL)
    {
      /* Potrebno je prvo zapamtiti adresu sledeceg elementa i
         onda osloboditi element koji predstavlja glavu liste */
      pomocni = (*adresa_glave)->sledeci;
      free(*adresa_glave);
      /* Sledeci element je nova glava liste */
      *adresa_glave = pomocni;
    }
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi 
   i ukoliko alokacija nije bila uspesna, oslobadja se sva
   prethodno zauzeta memorija za listu ciji pocetni cvor se
   nalazi na adresi adresa_glave.*/
void proveri_alokaciju(Cvor ** adresa_glave, Cvor * novi) 
{
  /* Ukoliko je novi NULL */
  if ( novi == NULL )
    {
      fprintf(stderr, "Neuspela alokacija za nov cvor\n");

      /* Oslobadjamo dinamicki alociranu memoriju i
         prekidamo program */
      oslobodi_listu(adresa_glave);
      exit(EXIT_FAILURE);
    }
}

/* Funkcija dodaje novi cvor na pocetak liste. 
   Kreira novi cvor koriscenjem funkcije napravi_cvor i uvezuje
   ga na pocetak */
void dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreiramo nov cvor i proveravamo da li je bilo greske pri
     alokaciji */
  Cvor *novi = napravi_cvor(broj);
  proveri_alokaciju(adresa_glave, novi);

  /* Uvezujemo novi cvor na pocetak */
  novi->sledeci = *adresa_glave;
  /* Nov cvor je sada nova glava liste */
  *adresa_glave = novi;
}



/* Funkcija pronalazi i vraca pokazivac na poslednji element 
   liste, ili NULL ukoliko je lista prazna. */
Cvor * pronadji_poslednji (Cvor * glava) 
{
  /* Prazna lista nema ni poslednji cvor i u tom slucaju
     vracamo NULL.*/
  if( glava == NULL)
    return NULL;

  /* Sve dok glava ne pokazuje na cvor koji nema sledeceg,
     pomeramo pokazivac glava na taj sledeci element. Kada
     izadjemo iz petlje, glava ce pokazivati na element liste
     koji nema sledeceg, tj, poslednji element liste je. Zato
     vracamo vrednost pokazivaca glava.
     Pokazivac glava je argument funkcije i njegove promene nece
     se odraziti na vrednost pokazivaca glava u pozivajucoj
     funkciji. */
  while (glava->sledeci != NULL)
    glava = glava->sledeci;

  return glava;
}

/* Funkcija dodaje novi cvor na kraj liste. */
void dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *novi = napravi_cvor(broj);
  proveri_alokaciju(adresa_glave, novi);

  /* U slucaju prazne liste  */
  if (*adresa_glave == NULL)
    {
      /* Glava nove liste je upravo novi cvor i ujedno i cela
       lista. Azuriramo vrednost na koju pokazuje adresa_glave i
       tako azuriramo i pokazivacku promenljivu u pozivajucoj
       funkciji. */
      *adresa_glave = novi;
      return;
    }

  /* Ako lista nije prazna, pronalazimo poslednji element */
  Cvor * poslednji = pronadji_poslednji(*adresa_glave);

  /* Dodajemo novi cvor na kraj preusmeravanjem pokazivaca */
  poslednji->sledeci = novi;
}


/* Pomocna funkcija pronalazi cvor u listi iza koga treba
   umetnuti nov element sa vrednoscu broj.*/
Cvor * pronadji_mesto_umetanja(Cvor * glava, int broj ) 
{
  /*Ako je lista prazna onda nema takvog mesta i vracamo NULL */
  if(glava == NULL)
    return NULL;

  /* Krecemo se kroz listu sve dok se ne dodje do elementa ciji
     je sledeci element veci ili jednak od novog elementa, ili
     dok se ne dodje do poslednjeg elementa.

     Zbog lenjog izracunavanja izraza u C-u prvi deo konjukcije
     mora biti provera da li smo dosli do poslednjeg elementa
     liste pre nego sto proverimo vrednost njegovog sledeceg
     elementa, jer u slucaju poslednjeg, sledeci ne postoji,
     pa ni vrednost.*/
  while (glava->sledeci != NULL
         && glava->sledeci->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje smo mogli izaci jer smo dosli do poslednjeg
     elementa ili smo se zaustavili ranije na elementu ciji
     sledeci ima vrednost vecu od broj */
  return glava;
}


void dodaj_iza(Cvor * tekuci, Cvor * novi) 
{ 
  /* Novi element dodajemo iza tekuceg elementa */
  novi->sledeci = tekuci->sledeci;
  tekuci->sledeci = novi;
}

/* Funkcija dodaje novi element u sortiranu listu 
   tako da nova lista ostane sortirana.*/
void dodaj_sortirano(Cvor ** adresa_glave, int broj) 
{    
  /* U slucaju prazne liste glava nove liste je novi cvor */
  if ( *adresa_glave == NULL ) {
      Cvor *novi = napravi_cvor(broj);
      /* Proveravamo da li je doslo do greske prilikom
         alokacije memorije */
      proveri_alokaciju(adresa_glave, novi);
      *adresa_glave = novi;
      return;
    }

  /* Lista nije prazna*/
  /* Ako je broj manji ili jednak vrednosti u glavi liste,
       onda ga dodajemo na pocetak liste  */
  if ( (*adresa_glave)->vrednost >= broj ) {
      dodaj_na_pocetak_liste(adresa_glave, broj);
      return;
    }

  /* U slucaju da je glava liste element manji od novog elementa,
     tada pronalazimo element liste iza koga treba da se umetne
     nov broj */
  Cvor * pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);

  Cvor *novi = napravi_cvor(broj);
  proveri_alokaciju(adresa_glave, novi);

  /* Uvezujemo novi cvor iza pomocnog */
  dodaj_iza(pomocni, novi);
}

/* Funkcija trazi u listi element cija je vrednost jednaka datom 
   broju. Vraca pokazivac na cvor liste u kome je sadrzan trazeni
   broj ili NULL u slucaju da takav element ne postoji u listi.*/
Cvor * pretrazi_listu(Cvor * glava, int broj) 
{
  for ( ; glava != NULL; glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vracamo NULL*/
  return NULL;
}


/* Funkcija trazi u listi element cija je vrednost jednaka datom
   broju. Vraca pokazivac na cvor liste u kome je sadrzan trazeni
   broj ili NULL u slucaju da takav element ne postoji u listi. 
   Funkcija se u pretrazi oslanja na cinjenicu da je lista koja 
   se pretrazuje neopadajuce sortirana. */
Cvor * pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
  /* U konjukciji koja cini uslov ostanka u petlji,
     bitan je redosled! */
  for ( ; glava != NULL && glava->vrednost <= broj ;
        glava = glava->sledeci)
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vracamo NULL*/
  return NULL;
}


/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Funkcija azurira pokazivac na glavu liste, koji moze biti
   promenjen u slucaju da se obrise stara glava. */
void obrisi_element(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = NULL;
  Cvor *pomocni = NULL;

  /* Brisemo sa pocetka liste sve cvorove koji su jednaki datom
     broju, i azuriramo pokazivac na glavu */
  while (*adresa_glave != NULL
         && (*adresa_glave)->vrednost == broj)
    {
      /* Sacuvamo adresu repa liste pre oslobadjanja glave */
      pomocni = (*adresa_glave)->sledeci;
      free(*adresa_glave);
      *adresa_glave = pomocni;
    }

  /* Ako je nakon toga lista ostala prazna prekidamo funkciju */
  if ( *adresa_glave == NULL)
    return;

  /* Od ovog trenutka se u svakom koraku nalazimo
     na tekucem cvoru koji je razlicit od trazenog
     broja (kao i svi levo od njega). Poredimo
     vrednost sledeceg cvora (ako postoji) sa trazenim
     brojem i brisemo ga ako je jednak, a prelazimo na
     sledeci cvor ako je razlicit. Ovaj postupak ponavljamo
     dok ne dodjemo do poslednjeg cvora. */
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL)
    if (tekuci->sledeci->vrednost == broj)
      {
        /* tekuci->sledeci treba obrisati,
           zbog toga sacuvamo njegovu adresu u pomocni */
        pomocni = tekuci->sledeci;
        /* Tekucem preusmerimo pokazivac sledeci
           tako sto preskacemo njegovog trenutnog sledeceg.
           Njegov novi sledeci ce biti sledeci od ovog koga
           brisemo. */
        tekuci->sledeci = pomocni->sledeci;
        /* Sada mozemo da oslobodimo cvor sa vrednoscu broj. */
        free(pomocni);
      }
    else
      {
        /* Ne treba brisati sledeceg. Prelazimo na sledeci. */
        tekuci = tekuci->sledeci;
      }
  return;
}


/* Funkcija brise iz liste sve cvorove koji sadrze dati broj, 
   oslanjajuci se na cinjenicu da je prosledjena lista sortirana
   neopadajuce. Funkcija azurira pokazivac na glavu liste, koji
   moze biti promenjen ukoliko se obrise stara glava liste. */
void obrisi_element_sortirane_liste(Cvor ** adresa_glave, int 
broj)
{
  Cvor *tekuci = NULL ;
  Cvor *pomocni = NULL ;

  /* Brisemo sa pocetka liste sve eventualne cvorove koji su
     jednaki datom broju, i azuriramo pokazivac na glavu */
  while (*adresa_glave != NULL
         && (*adresa_glave)->vrednost == broj)
    {
      /* Sacuvamo adresu repa liste pre oslobadjanja glave */
      pomocni = (*adresa_glave)->sledeci;
      free(*adresa_glave);
      *adresa_glave = pomocni;
    }

  /* Ako je nakon toga lista ostala prazna ili glava liste sadrzi
     vrednost koja je veca od broja, kako je lista sortirana
     rastuce nema potrebe broj traziti u repu liste i zato
     prekidamo funkciju */
  if ( *adresa_glave == NULL || (*adresa_glave)->vrednost > broj)
    return;

  /* Od ovog trenutka se u svakom koraku nalazimo u tekucem cvoru
     cija vrednost je manja od trazenog broja kao i svi levo od
     njega. Poredimo vrednost sledeceg cvora, ako postoji, sa
     trazenim brojem i brisemo ga ako je jednak, a prelazimo na
     sledeci cvor ako je razlicit. Ovaj postupak ponavljamo dok
     ne dodjemo do poslednjeg cvora ili prvog cvora cija vrednost
     je veca od trazenog broja. */
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL
         && tekuci->sledeci->vrednost <= broj)
    if (tekuci->sledeci->vrednost == broj)
      {
        /* tekuci->sledeci treba obrisati, zbog toga cuvamo
           njegovu adresu u pomocni */
        pomocni = tekuci->sledeci;
        /* Tekucem preusmerimo pokazivac sledeci tako sto
           preskacemo njegovog trenutnog sledeceg. Njegov novi
           sledeci ce biti sledeci od ovog koga brisemo. */
        tekuci->sledeci = tekuci->sledeci->sledeci;
        /* Sada mozemo da oslobodimo cvor sa vrednoscu broj */
        free(pomocni);
      }
    else
      {
        /* Ne treba brisati sledeceg, jer je manji od trazenog i
           prelazimo na sledeci */
        tekuci = tekuci->sledeci;
      }
  return;
}


/* Funkcija prikazuje elemente liste pocev od glave ka kraju 
   liste. Ne saljemo joj adresu promenljive koja cuva glavu
   liste, jer ova funkcija nece menjati listu, pa nema ni
   potrebe da azuriza pokazivac na glavu liste iz pozivajuce
   funkcije. */
void ispisi_listu(Cvor * glava)
{
  putchar('[');
  for ( ; glava != NULL; glava = glava->sledeci)
    {
      printf("%d", glava->vrednost);
      if( glava->sledeci != NULL )
        printf(", ");
    }

  printf("]\n");
}
