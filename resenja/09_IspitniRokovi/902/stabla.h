#ifndef _STABLA_H_
#define _STABLA_H_ 1

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

/* Funkcija dodaje novi broj u stablo i azurira vrednost korena
   stabla u pozivajucoj funkciji. Povratna vrednost funkcije je 0
   ako je dodavanje uspesno, odnosno 1 ukoliko je doslo do greske */
int dodaj_u_stablo(Cvor ** adresa_korena, int broj);

#endif
