#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

Cvor *napravi_cvor(int broj)
{
  /* Alocira se memorija za novi cvor i proverava se uspesnost
     alokacije. */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizuju se polja novog cvora. */
  novi->broj = broj;
  novi->levo = NULL;
  novi->desno = NULL;

  /* Vraca se adresa novog cvora. */
  return novi;
}

void proveri_alokaciju(Cvor * novi_cvor)
{

  /* Ukoliko je cvor neuspesno kreiran */
  if (novi_cvor == NULL) {

    /* Ispisuje se odgovarajuca poruka i prekida izvrsavanje programa 
     */
    fprintf(stderr, "Malloc greska za novi cvor!\n");
    exit(EXIT_FAILURE);
  }
}

void dodaj_u_stablo(Cvor ** adresa_korena, int broj)
{
  /* Ako je stablo prazno */
  if (*adresa_korena == NULL) {

    /* Kreira se novi cvor */
    Cvor *novi = napravi_cvor(broj);
    proveri_alokaciju(novi);

    /* I proglasava se korenom stabla */
    *adresa_korena = novi;
    return;
  }

  /* U suprotnom trazi se odgovarajuca pozicija za zadati broj: */

  /* Ako je zadata vrednost manja od vrednosti korena */
  if (broj < (*adresa_korena)->broj)

    /* Broj se dodaje u levo podstablo */
    dodaj_u_stablo(&(*adresa_korena)->levo, broj);

  else
    /* Inace, broj je veci (ili jednak) od vrednosti u korenu pa se
       dodaje u desno podstablo */
    dodaj_u_stablo(&(*adresa_korena)->desno, broj);
}

Cvor *pretrazi_stablo(Cvor * koren, int broj)
{

  /* Ako je stablo prazno, vrednost se sigurno ne nalazi u njemu */
  if (koren == NULL)
    return NULL;

  /* Ako je trazena vrednost sadrzana u korenu */
  if (koren->broj == broj) {

    /* Prekidamo pretragu */
    return koren;
  }

  /* Inace, ako je broj manji od vrednosti sadrzane u korenu */
  if (broj < koren->broj)

    /* Pretraga se nastavlja u levom podstablu */
    return pretrazi_stablo(koren->levo, broj);

  else
    /* U suprotnom, pretraga se nastavlja u desnom podstablu */
    return pretrazi_stablo(koren->desno, broj);
}

Cvor *pronadji_najmanji(Cvor * koren)
{

  /* Ako je stablo prazno, prekida se pretraga */
  if (koren == NULL)
    return NULL;

  /* Vrednosti koje su manje od vrednosti u korenu stabla nalaze se
     levo od njega */

  /* Ako je koren cvor koji nema levo podstablo, onda on sadrzi
     najmanju vrednost */
  if (koren->levo == NULL)
    return koren;

  /* Inace, pretragu treba nastaviti u levom podstablu */
  return pronadji_najmanji(koren->levo);
}

Cvor *pronadji_najveci(Cvor * koren)
{
  /* Ako je stablo prazno, prekida se pretraga */
  if (koren == NULL)
    return NULL;

  /* Vrednosti koje su vece od vrednosti u korenu stabla nalaze se
     desno od njega */

  /* Ako je koren cvor koji nema desno podstablo, onda on sadrzi
     najvecu vrednost */
  if (koren->desno == NULL)
    return koren;

  /* Inace, pretragu treba nastaviti u desnom podstablu */
  return pronadji_najveci(koren->desno);
}

void obrisi_element(Cvor ** adresa_korena, int broj)
{
  Cvor *pomocni_cvor = NULL;

  /* Ako je stablo prazno, brisanje nije primenljivo */
  if (*adresa_korena == NULL)
    return;

  /* Ako je vrednost koju treba obrisati manja od vrednosti u korenu
     stabla, ona se eventualno nalazi u levom podstablu, pa treba
     rekurzivno primeniti postupak na levo podstablo. Koren ovako
     modifikovanog stabla je nepromenjen. */
  if (broj < (*adresa_korena)->broj) {
    obrisi_element(&(*adresa_korena)->levo, broj);
    return;
  }

  /* Ako je vrednost koju treba obrisati veca od vrednosti u korenu
     stabla, ona se eventualno nalazi u desnom podstablu pa treba
     rekurzivno primeniti postupak na desno podstablo. Koren ovako
     modifikovanog stabla je nepromenjen. */
  if ((*adresa_korena)->broj < broj) {
    obrisi_element(&(*adresa_korena)->desno, broj);
    return;
  }

  /* Slede podslucajevi vezani za slucaj kada je vrednost u korenu
     jednaka broju koji se brise (tj. slucaj kada treba obrisati
     koren) */

  /* Ako koren nema sinova, tada se on prosto brise, i rezultat je
     prazno stablo (vraca se NULL) */
  if ((*adresa_korena)->levo == NULL
      && (*adresa_korena)->desno == NULL) {
    free(*adresa_korena);
    *adresa_korena = NULL;
    return;
  }

  /* Ako koren ima samo levog sina, tada se brisanje vrsi tako sto se 
     brise koren, a novi koren postaje levi sin */
  if ((*adresa_korena)->levo != NULL
      && (*adresa_korena)->desno == NULL) {
    pomocni_cvor = (*adresa_korena)->levo;
    free(*adresa_korena);
    *adresa_korena = pomocni_cvor;
    return;
  }

  /* Ako koren ima samo desnog sina, tada se brisanje vrsi tako sto
     se brise koren, a novi koren postaje desni sin */
  if ((*adresa_korena)->desno != NULL
      && (*adresa_korena)->levo == NULL) {
    pomocni_cvor = (*adresa_korena)->desno;
    free(*adresa_korena);
    *adresa_korena = pomocni_cvor;
    return;
  }

  /* Slucaj kada koren ima oba sina - najpre se potrazi sledbenik
     korena (u smislu poretka) u stablu. To je upravo po vrednosti
     najmanji cvor u desnom podstablu. On se moze pronaci npr.
     funkcijom pronadji_najmanji(). Nakon toga se u koren smesti
     vrednost tog cvora, a u taj cvor se smesti vrednost korena (tj.
     broj koji se brise).  Zatim se prosto rekurzivno pozove funkcija 
     za brisanje na desno podstablo. S obzirom da u njemu treba
     obrisati najmanji element, a on zasigurno ima najvise jednog
     potomka, jasno je da ce njegovo brisanje biti obavljeno na jedan 
     od jednostavnijih nacina koji su gore opisani. */
  pomocni_cvor = pronadji_najmanji((*adresa_korena)->desno);
  (*adresa_korena)->broj = pomocni_cvor->broj;
  pomocni_cvor->broj = broj;
  obrisi_element(&(*adresa_korena)->desno, broj);
}

void ispisi_stablo_infiksno(Cvor * koren)
{
  /* Ako stablo nije prazno */
  if (koren != NULL) {

    /* Prvo se ispisuju svi cvorovi levo od korena */
    ispisi_stablo_infiksno(koren->levo);

    /* Zatim se ispisuje vrednost u korenu */
    printf("%d ", koren->broj);

    /* Na kraju se ispisuju cvorovi desno od korena */
    ispisi_stablo_infiksno(koren->desno);
  }
}

void ispisi_stablo_prefiksno(Cvor * koren)
{
  /* Ako stablo nije prazno */
  if (koren != NULL) {

    /* Prvo se ispisuje vrednost u korenu */
    printf("%d ", koren->broj);

    /* Zatim se ispisuju svi cvorovi levo od korena */
    ispisi_stablo_prefiksno(koren->levo);

    /* Na kraju se ispisuju svi cvorovi desno od korena */
    ispisi_stablo_prefiksno(koren->desno);
  }
}

void ispisi_stablo_postfiksno(Cvor * koren)
{

  /* Ako stablo nije prazno */
  if (koren != NULL) {

    /* Prvo se ispisuju svi cvorovi levo od korena */
    ispisi_stablo_postfiksno(koren->levo);

    /* Zatim se ispisuju svi cvorovi desno od korena */
    ispisi_stablo_postfiksno(koren->desno);

    /* Na kraju se ispisuje vrednost u korenu */
    printf("%d ", koren->broj);
  }
}

void oslobodi_stablo(Cvor ** adresa_korena)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*adresa_korena == NULL)
    return;

  /* Inace ... */
  /* Oslobadja se memorija zauzeta levim podstablom */
  oslobodi_stablo(&(*adresa_korena)->levo);

  /* Oslobadja se memorija zauzetu desnim podstablom */
  oslobodi_stablo(&(*adresa_korena)->desno);

  /* Oslobadja se memorija zauzeta korenom */
  free(*adresa_korena);

  /* Proglasava se stablo praznim */
  *adresa_korena = NULL;
}
