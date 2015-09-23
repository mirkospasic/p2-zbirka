#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

Cvor *napravi_cvor(int broj)
{
  /* Alocira se memorija za novi cvor */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;
  /* Inicijalizuju se polja cvora */
  novi->broj = broj;
  novi->levo = NULL;
  novi->desno = NULL;
  /* Vraca se adresa novog cvora */
  return novi;
}

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

void dodaj_u_stablo(Cvor ** koren, int broj)
{
  /* Ako je stablo prazno */
  if (*koren == NULL) {
    /* Kreira se novi cvor */
    Cvor *novi = napravi_cvor(broj);
    proveri_alokaciju(novi);
    /* I proglasava se korenom stabla */
    *koren = novi;
    return;
  }
  /* U suprotnom se trazi odgovarajuca pozicija za novi broj */
  /* Ako je broj manji od vrednosti sadrzane u korenu, ubacuje se
     u levo podstablo */
  if (broj < (*koren)->broj)
    dodaj_u_stablo(&(*koren)->levo, broj);
  else
    /* Inace, ubacuje se u desno podstablo */
    dodaj_u_stablo(&(*koren)->desno, broj);
}

void oslobodi_stablo(Cvor ** koren)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*koren == NULL)
    return;
  /* Inace ... */
  /* Oslobadja se memorija zauzeta levim podstablom */
  if ((*koren)->levo)
    oslobodi_stablo(&(*koren)->levo);
  /* Oslobadja se memorija zauzetu desnim podstablom */
  if ((*koren)->desno)
    oslobodi_stablo(&(*koren)->desno);
  /* Oslobadja se memorija zauzeta korenom */
  free(*koren);
  /* Proglasava se stablo praznim */
  *koren = NULL;
}

Cvor *pronadji_najmanji(Cvor * koren)
{
  /* ako je stablo prazno, prekida se pretraga */
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
  /* ako je stablo prazno, prekida se pretraga */
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

void obrisi_element(Cvor ** adresa_korena, int n)
{
  Cvor *pomocni = NULL;
  /* Izlaz iz rekurzije */
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
     je prazno stablo (vraca se NULL) */
  if ((*adresa_korena)->levo == NULL
      && (*adresa_korena)->desno == NULL) {
    free(*adresa_korena);
    *adresa_korena = NULL;
    return;
  }
  /* Ako koren ima samo levog sina, tada se brisanje vrsi tako
     sto se obrise koren, a novi koren postaje levi sin */
  if ((*adresa_korena)->levo != NULL
      && (*adresa_korena)->desno == NULL) {
    pomocni = (*adresa_korena)->levo;
    free(*adresa_korena);
    *adresa_korena = pomocni;
    return;
  }
  /* Ako koren ima samo desnog sina, tada se brisanje vrsi tako
     sto se obrise koren, a novi koren postaje desni sin */
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
     korena (tj. broj koji se brise). - Zatim se
     rekurzivno pozove funkcija za brisanje nad desnim podstablom.
     S obzirom da u njemu treba obrisati najmanji element, a on
     definitivno ima najvise jednog potomka, jasno je da ce
     njegovo brisanje biti obavljeno na jedan od jednostavnijih
     nacina koji su gore opisani. */
  pomocni = pronadji_najmanji((*adresa_korena)->desno);
  (*adresa_korena)->broj = pomocni->broj;
  pomocni->broj = n;
  obrisi_element(&(*adresa_korena)->desno, n);
}

void prikazi_stablo(Cvor * koren)
{
  /* Izlaz iz rekurzije */
  if (koren == NULL)
    return;
  prikazi_stablo(koren->levo);
  printf("%d ", koren->broj);
  prikazi_stablo(koren->desno);
}

Cvor *pretrazi_stablo(Cvor * koren, int broj)
{
  /* Ako je stablo prazno, vrednost se sigurno ne nalazi u njemu 
   */
  if (koren == NULL)
    return NULL;
  /* Ako je trazena vrednost sadrazana u korenu */
  if (koren->broj == broj) {
    /* Prekida se pretraga */
    return koren;
  }
  /* Inace, ako je broj manji od vrednosti sadrzane u korenu */
  if (broj < koren->broj)
    /* Pretraga se nastavlja u levom podstablu */
    return pretrazi_stablo(koren->levo, broj);
  else
    /* U suprotnom, pretraga se  nastavlja u desnom podstablu */
    return pretrazi_stablo(koren->desno, broj);
}
