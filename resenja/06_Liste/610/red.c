#include "red.h"

Cvor *napravi_cvor(Zahtev * zahtev)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->nalog = *zahtev;
  novi->sledeci = NULL;
  return novi;
}

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

int dodaj_u_red(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                Zahtev * zahtev)
{
  Cvor *novi = napravi_cvor(zahtev);
  if (novi == NULL)
    return 1;
  /* U red se uvek dodaje na kraj. Zbog postojanja pokazivaca na
     kraj, to je podjednako efikasno kao dodavanje na pocetak liste */
  if (*adresa_kraja != NULL) {
    (*adresa_kraja)->sledeci = novi;
    *adresa_kraja = novi;
  } else {
    /* Ako je red bio ranije prazan */
    *adresa_pocetka = novi;
    *adresa_kraja = novi;
  }
  return 0;
}

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

Zahtev *pocetak_reda(Cvor * pocetak)
{
  if (pocetak == NULL)
    return NULL;

  return &(pocetak->nalog);
}

void prikazi_red(Cvor * pocetak)
{
  for (; pocetak != NULL; pocetak = pocetak->sledeci)
    printf("%s %s\n", (pocetak->nalog).jmbg, (pocetak->nalog).opis);

  printf("\n");
}
