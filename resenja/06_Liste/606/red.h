#ifndef _RED_H
#define _RED_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define JMBG_DUZINA 14

/* Struktura predstavlja zahtev korisnika. Obuhvata JMBG korisnika i
   opis njegovog zahteva. */
typedef struct {
  char jmbg[JMBG_DUZINA];
  char opis[MAX];
} Zahtev;

/* Struktura kojom je predstavljen cvor liste, obuhvata zahtev
   korisnika i pokazivac na sledeci cvor liste. */
typedef struct cvor {
  Zahtev nalog;
  struct cvor *sledeci;
} Cvor;

Cvor *napravi_cvor(Zahtev * zahtev);

void oslobodi_red(Cvor ** pocetak, Cvor ** kraj);

void proveri_alokaciju(Cvor ** adresa_pocetka,
                       Cvor ** adresa_kraja, Cvor * novi);

void dodaj_u_red(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                 Zahtev * zahtev);

int skini_sa_reda(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                  Zahtev * zahtev);

Zahtev *pocetak_reda(Cvor * pocetak);

void prikazi_red(Cvor * pocetak);

#endif
