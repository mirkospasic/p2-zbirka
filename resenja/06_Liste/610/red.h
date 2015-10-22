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

/* Funkcija kreira novi cvor, inicijalizuje polje nalog na zahtev sa
   poslate adrese i vraca adresu novog cvora ili NULL ako je doslo do 
   greske pri alokaciji. Prosledjuje joj se pokazivac na zahtev koji
   treba smestiti u nov cvor zbog smestanja manjeg podatka na
   sistemski stek. Pokazivac na strukturu Zahtev je manje velicine u
   bajtovima(B) u odnosu na strukturu Zahtev. */
Cvor *napravi_cvor(Zahtev * zahtev);

/* Funkcija prazni red, oslobadjajuci memoriju koji je red zauzeo. */
void oslobodi_red(Cvor ** pocetak, Cvor ** kraj);

/* Funkcija dodaje na kraj reda novi zahtev. Vraca 1 ako je doslo do
   greske pri alokaciji memorije za nov cvor, inace vraca 0. */
int dodaj_u_red(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                Zahtev * zahtev);

/* Funkcija skida sa pocetka reda zahtev. Ako je poslednji argument
   pokazivac razlicit od NULL, tada se u strukturu na koju on
   pokazuje upisuje zahtev koji je upravo skinut sa reda dok u
   suprotnom ne upisuje nista. Vraca 0, ako je red bio prazan ili 1 u 
   suprotnom. */
int skini_sa_reda(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                  Zahtev * zahtev);

/* Funkcija vraca pokazivac na strukturu koji sadrzi zahtev korisnika 
   na pocetku reda. Ukoliko je red prazan, vraca NULL. */
Zahtev *pocetak_reda(Cvor * pocetak);

/* Funkcija prikazuje sadrzaj reda. */
void prikazi_red(Cvor * pocetak);

#endif
