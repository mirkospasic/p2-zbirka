#ifndef _LISTE_H_
#define _LISTE_H_ 1

/* Struktura koja predstavlja cvor liste */
typedef struct cvor {
  double vrednost;
  struct cvor *sledeci;
} Cvor;

/* Pomocna funkcija koja kreira cvor. */
Cvor *napravi_cvor(double broj);

/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente liste
   ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave);

/* Funkcija pronalazi i vraca pokazivac na poslednji element liste,
   ili NULL kao je lista prazna */
Cvor *pronadji_poslednji(Cvor * glava);

/* Funkcija dodaje novi cvor na kraj liste. Vraca 1 ukoliko je bilo
   greske pri alokaciji memorije,inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, double broj);

/* Funkcija prikazuje sve elemente liste pocev od glave ka kraju
   liste. */
void ispisi_listu(Cvor * glava);

#endif
