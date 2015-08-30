#ifndef __STABLA_H__
#define __STABLA_H__ 1

/* Struktura koja predstavlja cvor stabla */
typedef struct cvor {
    int vrednost;		/* Vrednost koja se cuva */
    struct cvor *levi;		/* Pokazivac na levo podstablo */
    struct cvor *desni;		/* Pokazivac na desno podstablo */
} Cvor;

/* Pomocna funkcija za kreiranje cvora. Cvor se kreira
   dinamicki, funkcijom malloc(). U slucaju greske program
   se prekida i ispisuje se poruka o gresci. U slucaju 
   uspeha inicijalizuje se vrednost datim brojem, a pokazivaci
   na podstabla se inicijalizuju na NULL. Funkcija vraca 
   adresu novokreiranog cvora */
Cvor *napravi_cvor(int broj);

/* Funkcija dodaje novi cvor u stablo sa datim korenom.
   Ukoliko broj vec postoji u stablu, ne radi nista.
   Cvor se kreira funkcijom napravi_cvor(). */
void dodaj_u_stablo(Cvor **koren, int broj);

/* Funkcija prikazuje stablo s leva u desno (tj. 
   prikazuje elemente u rastucem poretku) */
void prikazi_stablo(Cvor * koren);

/* Funkcija ucitava stablo sa standardnog ulaza do kraja ulaza i vraca
   pokazican na njegov koren */
Cvor* ucitaj_stablo();

/* Funkcija oslobadja prostor koji je alociran za 
   cvorove stabla. */
void oslobodi_stablo(Cvor **koren);

#endif
