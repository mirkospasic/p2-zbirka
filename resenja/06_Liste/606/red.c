#include "red.h"

/* Funkcija kreira novi cvor, inicijalizuje polje nalog na
   zahtev sa poslate adrese i vraca adresu novog cvora ili NULL
   ako je doslo do greske pri alokaciji. Ako je doslo do greske,
   trebalo bi osloboditi ceo red. To je ostavljeno da to uradi
   funkcija koja je pozvala funkciju napravi_cvor, a gresku ce
   biti signalizirana vracanjem NULL. Funkciji se prosledjuje
   pokazivac na zahtev koji treba smestiti u nov cvor zbog
   smestanja manjeg podatka na sistemski stek. Pokazivac na
   strukturu Zahtev je manje velicine u bajtovima(B) u odnosu na
   strukturu Zahtev. */
Cvor *napravi_cvor(Zahtev * zahtev)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->nalog = *zahtev;
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija prazni red */
void oslobodi_red(Cvor ** pocetak, Cvor ** kraj)
{
  Cvor *pomocni = NULL;

  while (*pocetak != NULL) {
    pomocni = *pocetak;
    *pocetak = (*pocetak)->sledeci;
    free(pomocni);
  }
  *kraj = NULL;
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi
   i ukoliko alokacija nije bila uspesna, oslobadja se sva
   prethodno zauzeta memorija za listu cija pocetni cvor se
   nalazi na adresi adresa_pocetka. */
void proveri_alokaciju(Cvor ** adresa_pocetka,
                       Cvor ** adresa_kraja, Cvor * novi)
{
  if (novi == NULL) {
    fprintf(stderr, "Neuspela alokacija za nov cvor\n");
    oslobodi_red(adresa_pocetka, adresa_kraja);
    exit(EXIT_FAILURE);
  }
}

/* Funkcija dodaje na kraj reda novi fajl. */
void dodaj_u_red(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                 Zahtev * zahtev)
{
  Cvor *novi = napravi_cvor(zahtev);
  proveri_alokaciju(adresa_pocetka, adresa_kraja, novi);

  /* U red se uvek dodaje na kraj, ali zbog postojanja
     pokazivaca na kraj, dodavanje na kraj je podjednako
     efikasno kao dodavanje na pocetak. */
  if (*adresa_kraja != NULL) {
    (*adresa_kraja)->sledeci = novi;
    *adresa_kraja = novi;
  } else {
    /* Ako je red bio ranije prazan */
    *adresa_pocetka = novi;
    *adresa_kraja = novi;
  }
}

/* Funkcija skida sa pocetka reda zahtev. Ako je poslednji
   argument pokazivac razlicit od NULL, tada se u strukturu na
   koju on pokazuje upisuje zahtev koji je upravo skinut sa reda
   dok u suprotnom ne upisuje nista. Funkcija vraca 0 ako je red
   bio prazan ili 1 u suprotnom. */
int skini_sa_reda(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                  Zahtev * zahtev)
{
  Cvor *pomocni = NULL;

  if (*adresa_pocetka == NULL)
    return 0;

  if (zahtev != NULL)
    *zahtev = (*adresa_pocetka)->nalog;

  pomocni = *adresa_pocetka;
  *adresa_pocetka = (*adresa_pocetka)->sledeci;
  free(pomocni);

  if (*adresa_pocetka == NULL)
    *adresa_kraja = NULL;

  return 1;
}

/* Funkcija vraca pokazivac na strukturu koji sadrzi zahtev
   korisnika na pocetku reda. Ukoliko je red prazan, vraca NULL. 
 */
Zahtev *pocetak_reda(Cvor * pocetak)
{
  if (pocetak == NULL)
    return NULL;

  return &(pocetak->nalog);
}

/* Funkcija prikazuje red. */
void prikazi_red(Cvor * pocetak)
{
  for (; pocetak != NULL; pocetak = pocetak->sledeci)
    printf("%s %s\n",
           (pocetak->nalog).jmbg, (pocetak->nalog).opis);

  printf("\n");
}
