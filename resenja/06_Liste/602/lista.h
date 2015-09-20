#ifndef _LISTA_H
#define _LISTA_H

/* Struktura kojom je predstavljen cvor liste sadrzi celobrojni
   podatak vrednost i pokazivac na sledeci cvor liste. */
typedef struct cvor {
  int vrednost;
  struct cvor *sledeci;
} Cvor;

Cvor *napravi_cvor(int broj);

void oslobodi_listu(Cvor ** adresa_glave);

int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj);

Cvor *pronadji_poslednji(Cvor * glava);

int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj);

Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj);

void dodaj_iza(Cvor * tekuci, Cvor * novi);

int dodaj_sortirano(Cvor ** adresa_glave, int broj);

Cvor *pretrazi_listu(Cvor * glava, int broj);

Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj);

void obrisi_cvor(Cvor ** adresa_glave, int broj);

void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj);

void ispisi_vrednosti(Cvor * glava);

void ispisi_listu(Cvor * glava);

#endif
