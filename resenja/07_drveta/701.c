#include <stdio.h>
#include <stdlib.h>

/* a) Struktura kojom se predstavlja cvor binarnog
   pretrazivackog stabla */
typedef struct cvor {
  int broj;
  struct cvor *levo;
  struct cvor *desno;
} Cvor;

/* b) Funkcija koja alocira memoriju za novi cvor stabla,
   inicijalizuje polja strukture i vraca pokazivac na novi cvor */
Cvor *napravi_cvor(int broj)
{
  /* Alociramo memoriju */
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


/* c) Funkcija koja dodaje zadati broj u stablo */
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

  /* U suprotnom trazi se odgovarajuca pozicija za zadati broj */

  /* Ako je zadata vrednost manja od vrednosti korena */
  if (broj < (*adresa_korena)->broj)

    /* Dodaje se broj u levo podstablo */
    dodaj_u_stablo(&(*adresa_korena)->levo, broj);

  else
    /* Inace, broj je veci (ili jednak) od vrednosti u korenu pa 
       se dodaje u desno podstablo */
    dodaj_u_stablo(&(*adresa_korena)->desno, broj);
}


/* d) Funkcija koja proverava da li se zadati broj nalazi u
   stablu */
Cvor *pretrazi_stablo(Cvor * koren, int broj)
{
  /* Ako je stablo prazno, vrednost se sigurno ne nalazi u njemu 
   */
  if (koren == NULL)
    return NULL;

  /* Ako je trazena vrednost sadrazana u korenu */
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


/* e) Funkcija pronalazi cvor koji sadrzi najmanju vrednost u
   stablu */
Cvor *pronadji_najmanji(Cvor * koren)
{
  /* Ako je stablo prazno, prekida se pretraga */
  if (koren == NULL)
    return NULL;

  /* Vrednosti koje su manje od vrednosti u korenu stabla nalaze 
     se levo od njega */

  /* Ako je koren cvor koji nema levo podstablo, onda on sadrzi
     najmanju vrednost */
  if (koren->levo == NULL)
    return koren;

  /* Inace, pretragu treba nastaviti u levom podstablu */
  return pronadji_najmanji(koren->levo);
}


/* f) Funkcija pronalazi cvor koji sadrzi najvecu vrednost u
   stablu */
Cvor *pronadji_najveci(Cvor * koren)
{
  /* Ako je stablo prazno, prekida se pretraga */
  if (koren == NULL)
    return NULL;

  /* Vrednosti koje su vece od vrednosti u korenu stabla nalaze
     se desno od njega */

  /* Ako je koren cvor koji nema desno podstablo, onda on sadrzi 
     najvecu vrednost */
  if (koren->desno == NULL)
    return koren;

  /* Inace, pretragu treba nastaviti u desnom podstablu */
  return pronadji_najveci(koren->desno);
}


/* g) Funkcija koja brise cvor stabla koji sadrzi zadati broj */
void obrisi_element(Cvor ** adresa_korena, int broj)
{
  Cvor *pomocni_cvor = NULL;

  /* ako je stablo prazno, brisanje nije primenljivo pa se moze
     prekinuti rad funkcije */
  if (*adresa_korena == NULL)
    return;

  /* Ako je vrednost koju treba obrisati manja od vrednosti u
     korenu stabla, ona se eventualno nalazi u levom podstablu,
     pa treba rekurzivno primeniti postupak na levo podstablo.
     Koren ovako modifikovanog stabla je nepromenjen. */
  if (broj < (*adresa_korena)->broj) {
    obrisi_element(&(*adresa_korena)->levo, broj);
    return;
  }

  /* Ako je vrednost koju treba obrisati veca od vrednosti u
     korenu stabla, ona se eventualno nalazi u desnom podstablu
     pa treba rekurzivno primeniti postupak na desno podstablo.
     Koren ovako modifikovanog stabla je nepromenjen. */
  if ((*adresa_korena)->broj < broj) {
    obrisi_element(&(*adresa_korena)->desno, broj);
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
     sto se brise koren, a novi koren postaje levi sin */
  if ((*adresa_korena)->levo != NULL
      && (*adresa_korena)->desno == NULL) {
    pomocni_cvor = (*adresa_korena)->levo;
    free(*adresa_korena);
    *adresa_korena = pomocni_cvor;
    return;
  }

  /* Ako koren ima samo desnog sina, tada se brisanje vrsi tako
     sto se brise koren, a novi koren postaje desni sin */
  if ((*adresa_korena)->desno != NULL
      && (*adresa_korena)->levo == NULL) {
    pomocni_cvor = (*adresa_korena)->desno;
    free(*adresa_korena);
    *adresa_korena = pomocni_cvor;
    return;
  }

  /* Slucaj kada koren ima oba sina. Tada se brisanje vrsi na
     sledeci nacin: - najpre se potrazi sledbenik korena (u
     smislu poretka) u stablu. To je upravo po vrednosti
     najmanji cvor u desnom podstablu. On se moze pronaci npr.
     funkcijom pronadji_najmanji(). Nakon toga se u koren smesti 
     vrednost tog cvora, a u taj cvor se smesti vrednost korena
     (tj. broj koji se brise).  - Zatim se prosto rekurzivno
     pozove funkcija za brisanje na desno podstablo. S obzirom
     da u njemu treba obrisati najmanji element, a on zasigurno
     ima najvise jednog potomka, jasno je da ce njegovo brisanje 
     biti obavljeno na jedan od jednostavnijih nacina koji su
     gore opisani. */
  pomocni_cvor = pronadji_najmanji((*adresa_korena)->desno);
  (*adresa_korena)->broj = pomocni_cvor->broj;
  pomocni_cvor->broj = broj;
  obrisi_element(&(*adresa_korena)->desno, broj);
}


/* h) Funkcija ispisuje stablo u infiksnoj notaciji ( Levo
   postablo - Koren - Desno podstablo ) */
void ispisi_stablo_infiksno(Cvor * koren)
{
  /* Ako stablo nije prazno */
  if (koren != NULL) {

    /* Prvo se ispisuju svi cvorovi levo od korena */
    ispisi_stablo_infiksno(koren->levo);

    /* Ispisuje se vrednost u korenu */
    printf("%d ", koren->broj);

    /* Na kraju se ispisuju cvorovi desno od korena */
    ispisi_stablo_infiksno(koren->desno);
  }
}


/* i) Funkcija ispisuje stablo u prefiksnoj notaciji ( Koren -
   Levo podstablo - Desno podstablo ) */
void ispisi_stablo_prefiksno(Cvor * koren)
{
  /* Ako stablo nije prazno */
  if (koren != NULL) {

    /* Prvo se ispisuje vrednost u korenu */
    printf("%d ", koren->broj);

    /* Ispisuju se svi cvorovi levo od korena */
    ispisi_stablo_prefiksno(koren->levo);

    /* Na kraju se ispisuju svi cvorovi desno od korena */
    ispisi_stablo_prefiksno(koren->desno);
  }
}


/* j) Funkcija ispisuje stablo postfiksnoj notaciji ( Levo
   podstablo - Desno postablo - Koren) */
void ispisi_stablo_postfiksno(Cvor * koren)
{
  /* Ako stablo nije prazno */
  if (koren != NULL) {

    /* Prvo se ispisuju svi cvorovi levo od korena */
    ispisi_stablo_postfiksno(koren->levo);

    /* Ispisuju se svi cvorovi desno od korena */
    ispisi_stablo_postfiksno(koren->desno);

    /* Na kraju se ispisuje vrednost u korenu */
    printf("%d ", koren->broj);
  }
}


/* k) Funkcija koja oslobadja memoriju zauzetu stablom.  */
void oslobodi_stablo(Cvor ** adresa_korena)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*adresa_korena == NULL)
    return;

  /* U suprotnom rekurzivno se oslobadja memorija koju zauzima
     najpre levo, a zatim i desno podstablo */
  oslobodi_stablo(&(*adresa_korena)->levo);
  oslobodi_stablo(&(*adresa_korena)->desno);

  /* Oslobadja se memorija koju zauzima koren */
  free(*adresa_korena);

  /* I proglasava se stablo praznim */
  *adresa_korena = NULL;
}

int main()
{
  Cvor *koren;
  int n;
  Cvor *trazeni_cvor;

  /* Proglasava se stablo praznim */
  koren = NULL;

  /* Dodaju se vrednosti u stablo */
  printf("Unesite brojeve (CTRL+D za kraj unosa): ");
  while (scanf("%d", &n) != EOF) {
    dodaj_u_stablo(&koren, n);
  }

  /* Trazeni ispisi: */
  printf("\nInfiksni ispis: ");
  ispisi_stablo_infiksno(koren);
  printf("\nPrefiksni ispis: ");
  ispisi_stablo_prefiksno(koren);
  printf("\nPostfiksni ispis: ");
  ispisi_stablo_postfiksno(koren);

  /* Demonstrira se rad funkcije za pretragu */
  printf("\nTrazi se broj: ");
  scanf("%d", &n);
  trazeni_cvor = pretrazi_stablo(koren, n);
  if (trazeni_cvor == NULL)
    printf("Broj se ne nalazi u stablu!\n");
  else
    printf("Broj se nalazi u stablu!\n");

  /* Demonstrira se rad funkcije za brisanje */
  printf("Brise se broj: ");
  scanf("%d", &n);
  obrisi_element(&koren, n);
  printf("Rezultujuce stablo: ");
  ispisi_stablo_infiksno(koren);
  printf("\n");

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
