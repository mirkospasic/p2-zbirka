#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
/* Funkcija kojom se kreira novi cvor stabla koji sadrzi zadatu
   vrednost */
Cvor *napravi_cvor(int broj)
{
  /* Alociramo memoriju za novi cvor */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;
  /* Inicijalizujemo polja cvora */
  novi->broj = broj;
  novi->levo = NULL;
  novi->desno = NULL;
  /* Vracamo adresu novog cvora */
  return novi;
}

/* Funkcija koja proverava uspesnost kreiranja novog cvora
   stabla */
void proveri_alokaciju(Cvor * novi_cvor)
{
  /* Ukoliko je cvor neuspesno kreiran */
  if (novi_cvor == NULL) {
    /* Ispisuje se odgovarajuca poruka i prekida izvrsavanje
       programa */
    fprintf(stderr, "Malloc greska za novi cvor!\n");
    exit(EXIT_FAILURE);
  }
}

/* Funkcija koja dodaje novi broj u stablo. */
void dodaj_u_stablo(Cvor ** koren, int broj)
{
  /* Ako je stablo prazno */
  if (*koren == NULL) {
    /* Kreiramo novi cvor */
    Cvor *novi = napravi_cvor(broj);
    proveri_alokaciju(novi);
    /* i proglasavamo ga korenom stabla */
    *koren = novi;
    return;
  }
  /* U suprotnom trazimo odgovarajucu poziciju za novi broj */
  /* Ako je broj manji od vrednosti sadrzane u korenu, ubacujemo
     ga u levo podstablo */
  if (broj < (*koren)->broj)
    dodaj_u_stablo(&(*koren)->levo, broj);
  else
    /* Inace, ubacujemo broj u desno podstablo */
    dodaj_u_stablo(&(*koren)->desno, broj);
}

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** koren)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*koren == NULL)
    return;
  /* Inace ... */
  /* Oslobadjamo memoriju zauzetu levom podstablom */
  if ((*koren)->levo)
    oslobodi_stablo(&(*koren)->levo);
  /* Oslobadjamo memoriju zauzetu desnom podstablom */
  if ((*koren)->desno)
    oslobodi_stablo(&(*koren)->desno);
  /* Oslobadjamo memoriju zauzetu korenom */
  free(*koren);
  /* Proglasavamo stablo praznim */
  *koren = NULL;
}

Cvor *pronadji_najmanji(Cvor * koren)
{
  /* ako je stablo prazno, prekidamo pretragu */
  if (koren == NULL)
    return NULL;
  /* vrednosti koje su manje od vrednosti u korenu stabla nalaze 
     se levo od njega */
  /* ako je koren cvor koji nema levo podstablo, onda on sadrzi
     najmanju vrednost */
  if (koren->levo == NULL)
    return koren;
  /* inace, pretragu treba nastaviti u levom podstablu */
  return pronadji_najmanji(koren->levo);
}

Cvor *pronadji_najveci(Cvor * koren)
{
  /* ako je stablo prazno, prekidamo pretragu */
  if (koren == NULL)
    return NULL;
  /* vrednosti koje su vece od vrednosti u korenu stabla nalaze
     se desno od njega */
  /* ako je koren cvor koji nema desno podstablo, onda on sadrzi 
     najvecu vrednost */
  if (koren->desno == NULL)
    return koren;
  /* inace, pretragu treba nastaviti u desnom podstablu */
  return pronadji_najveci(koren->desno);
}

/* Funkcija brise element iz stabla ciji je broj upravo jednak
   broju n. Funkcija azurira koren stabla u pozivajucoj
   funkciji, jer u ovoj funkciji koren moze biti promenjen u
   funkciji. */
void obrisi_element(Cvor ** adresa_korena, int n)
{
  Cvor *pomocni = NULL;
  /* Izlaz iz rekurzije: ako je stablo prazno, nema sta da se
     brise */
  if (*adresa_korena == NULL)
    return;
  /* Ako je vrednost broja veca od vrednosti u korenu stablua,
     tada se broj eventualno nalazi u desnom podstablu, pa treba 
     rekurzivno primeniti postupak na desno podstablo. Koren
     ovako modifikovanog stabla je nepromenjen. */
  if ((*adresa_korena)->broj < n) {
    obrisi_element(&(*adresa_korena)->desno, n);
    return;
  }
  /* Ako je vrednost broja manja od vrednosti korena, tada se
     broj eventualno nalazi u levom podstablu, pa treba
     rekurzivno primeniti postupak na levo podstablo. Koren
     ovako modifikovanog stabla je nepromenjen. */
  if ((*adresa_korena)->broj > n) {
    obrisi_element(&(*adresa_korena)->levo, n);
    return;
  }
  /* Slede podslucajevi vezani za slucaj kada je vrednost u
     korenu jednaka broju koji se brise (tj. slucaj kada treba
     obrisati koren) */
  /* Ako koren nema sinova, tada se on prosto brise, i rezultat
     je prazno stablo (vracamo NULL) */
  if ((*adresa_korena)->levo == NULL
      && (*adresa_korena)->desno == NULL) {
    free(*adresa_korena);
    *adresa_korena = NULL;
    return;
  }
  /* Ako koren ima samo levog sina, tada se brisanje vrsi tako
     sto obrisemo koren, a novi koren postaje levo sin */
  if ((*adresa_korena)->levo != NULL
      && (*adresa_korena)->desno == NULL) {
    pomocni = (*adresa_korena)->levo;
    free(*adresa_korena);
    *adresa_korena = pomocni;
    return;
  }
  /* Ako koren ima samo desnog sina, tada se brisanje vrsi tako
     sto obrisemo koren, a novi koren postaje desno sin */
  if ((*adresa_korena)->desno != NULL
      && (*adresa_korena)->levo == NULL) {
    pomocni = (*adresa_korena)->desno;
    free(*adresa_korena);
    *adresa_korena = pomocni;
    return;
  }
  /* Slucaj kada koren ima oba sina. Tada se brisanje vrsi na
     sledeci nacin: - najpre se potrazi sledbenik korena (u
     smislu poretka) u stablu. To je upravo po vrednosti
     najmanji cvor u desnom podstablu. On se moze pronaci npr.
     funkcijom pronadji_najmanji(). - Nakon toga se u koren
     smesti vrednost tog cvora, a u taj cvor se smesti vrednost
     korena (tj. broj koji se brise). - Onda se prosto
     rekurzivno pozove funkcija za brisanje na desno podstablo.
     S obzirom da u njemu treba obrisati najmanji element, a on
     definitivno ima najvise jednog potomka, jasno je da ce
     njegovo brisanje biti obavljeno na jedan od jednostavnijih
     nacina koji su gore opisani. */
  pomocni = pronadji_najmanji((*adresa_korena)->desno);
  (*adresa_korena)->broj = pomocni->broj;
  pomocni->broj = n;
  obrisi_element(&(*adresa_korena)->desno, n);
}

/* Funkcija prikazuje stablo s leva u desno (tj. prikazuje
   elemente u rastucem poretku) */
void prikazi_stablo(Cvor * koren)
{
  /* izlaz iz rekurzije */
  if (koren == NULL)
    return;
  prikazi_stablo(koren->levo);
  printf("%d ", koren->broj);
  prikazi_stablo(koren->desno);
}

Cvor *pretrazi_stablo(Cvor * koren, int broj)
{
  /* ako je stablo prazno, vrednost se sigurno ne nalazi u njemu 
   */
  if (koren == NULL)
    return NULL;
  /* ako je trazena vrednost sadrazana u korenu */
  if (koren->broj == broj) {
    /* prekidamo pretragu */
    return koren;
  }
  /* inace, ako je broj manji od vrednosti sadrzane u korenu */
  if (broj < koren->broj)
    /* pretragu nastavljamo u levom podstablu */
    return pretrazi_stablo(koren->levo, broj);
  else
    /* u suprotnom, pretragu nastavljamo u desnom podstablu */
    return pretrazi_stablo(koren->desno, broj);
}
