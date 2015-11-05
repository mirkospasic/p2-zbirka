#ifndef _STABLA_H_
#define _STABLA_H_ 1

/* Struktura koja predstavlja cvor stabla, sadrzi vrednost koja se
   cuva i pokazivace na levo i desno podstablo. */
typedef struct cvor {
  int vrednost;
  struct cvor *levi;
  struct cvor *desni;
} Cvor;

/* Pomocna funkcija za kreiranje cvora. Cvor se kreira dinamicki,
   funkcijom malloc(). Povratna vrednost funkcije je NULL ukoliko
   dodje do greske, a ukoliko je alokoacija uspesna, cvor se
   inicijalizuje datim brojem i pokazivaci na podstabla se
   postavljaju na NULL. Funkcija vraca adresu novokreiranog cvora */
Cvor *napravi_cvor(int broj);

/* Funkcija dodaje novi cvor u stablo sa datim korenom. Ukoliko je
   dodavanje uspesno, povratna vrednost funkcije je 1, dok je u
   suprotnom povratna vrednost 0 */
int dodaj_u_stablo(Cvor ** koren, int broj);

/* Funkcija prikazuje stablo s leva u desno (tj. prikazuje elemente u 
   rastucem poretku) */
void prikazi_stablo(Cvor * koren);

/* Funkcija ucitava stablo sa standardnog ulaza do kraja ulaza.
   Povratna vrednost funkcije je 0 ukoliko je stablo uspesno
   kreirano, odnosno 1 ako je doslo do greske */
int ucitaj_stablo(Cvor ** koren);

/* Funkcija oslobadja prostor koji je alociran za cvorove stabla. */
void oslobodi_stablo(Cvor ** koren);

#endif
