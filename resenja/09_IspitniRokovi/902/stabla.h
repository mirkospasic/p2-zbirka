#ifndef __STABLA_H__
#define __STABLA_H__ 1

/* Struktura kojom se predstavlja Cvor stabla */
typedef struct dcvor {
  int broj;
  struct dcvor *levo, *desno;
} Cvor;

/* Funkcija alocira prostor za novi Cvor stabla, inicijalizuje polja
   strukture i vraca pokazivac na nov Cvor */
Cvor *napravi_cvor(int b);

/* Funkcija oslobadja dinamicki alociran prostor za stablo Nakon
   oslobadjanja se u pozivajucoj funkciji koren postavljana NULL, jer 
   je stablo prazno */
void oslobodi_stablo(Cvor ** adresa_korena);

/* Funkcija proverava da li je novi Cvor ispravno alociran, i nakon
   toga prekida program */
void proveri_alokaciju(Cvor * novi);

/* Funkcija dodaje nov Cvor u stablo i azurira vrednost korena stabla 
   u pozivajucoj funkciji. */
void dodaj_u_stablo(Cvor ** adresa_korena, int broj);

#endif
