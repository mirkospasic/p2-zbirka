#ifndef _LISTA_H
#define _LISTA_H

/* Biblioteka rekurzivnih funkcije za rad 
   sa jednostruko povezanom listom celih brojeva */

/* Struktura kojom je predstavljen cvor liste */
typedef struct cvor {
  /* Podatak koji cvor sadrzi */
  int vrednost;
  /* Pokazivac na sledeci cvor liste */
  struct cvor *sledeci;
} Cvor;

Cvor* napravi_cvor(int broj);

void oslobodi_listu(Cvor** adresa_glave) ;

int dodaj_na_pocetak_liste(Cvor** adresa_glave, int broj);

int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj);

int dodaj_sortirano(Cvor ** adresa_glave, int broj) ;

Cvor * pretrazi_listu(Cvor * glava, int broj) ;

Cvor * pretrazi_sortiranu_listu(Cvor * glava, int broj);

void obrisi_element(Cvor ** adresa_glave, int broj);

void obrisi_element_sortirane_liste(Cvor ** adresa_glave, int
broj);

void ispisi_listu(Cvor * glava);

void ispisi_elemente(Cvor * glava);

#endif
