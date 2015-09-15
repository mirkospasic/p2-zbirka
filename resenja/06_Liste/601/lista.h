#ifndef _LISTA_H
#define _LISTA_H

/* Struktura kojom je predstavljen cvor liste */
typedef struct cvor {
  /* Podatak koji cvor sadrzi */
  int vrednost;
  /* Pokazivac na sledeci cvor liste */
  struct cvor *sledeci;
} Cvor;

Cvor* napravi_cvor(int broj);

void oslobodi_listu(Cvor** adresa_glave) ;

void proveri_alokaciju(Cvor** adresa_glave, Cvor* novi) ;

void dodaj_na_pocetak_liste(Cvor** adresa_glave, int broj);

Cvor * pronadji_poslednji (Cvor * glava);

void dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj);

Cvor * pronadji_mesto_umetanja(Cvor * glava, int broj ) ;

void dodaj_iza(Cvor * tekuci, Cvor * novi) ;

void dodaj_sortirano(Cvor ** adresa_glave, int broj) ;

Cvor * pretrazi_listu(Cvor * glava, int broj) ;

Cvor * pretrazi_sortiranu_listu(Cvor * glava, int broj);

void obrisi_element(Cvor ** adresa_glave, int broj);

void obrisi_element_sortirane_liste(Cvor ** adresa_glave, int
broj);

void ispisi_listu(Cvor * glava);

#endif
