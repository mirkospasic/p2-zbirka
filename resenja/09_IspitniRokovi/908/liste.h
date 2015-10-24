#ifndef __LISTE_H__
#define __LISTE_H__ 1

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

/* Funkcija proverava uspesnost alokacije memorije za cvor novi i
   ukoliko alokacija nije bila uspesna, oslobadja se sva prethodno
   zauzeta memorija za listu cija pocetni cvor se nalazi na adresi
   adresa_glave.  */
void proveri_alokaciju(Cvor ** adresa_glave, Cvor * novi);

/* Funkcija pronalazi i vraca pokazivac na poslednji element liste,
   ili NULL kao je lista prazna */
Cvor *pronadji_poslednji(Cvor * glava);

/* Funkcija dodaje novi cvor na kraj liste. */
void dodaj_na_kraj_liste(Cvor ** adresa_glave, double broj);

/* Funkcija prikazuje elemente liste pocev od glave ka kraju liste. */
void ispisi_listu(Cvor * glava);

/* Funkcija koja dopunjuje listu na nacin opisan u zadatku */
void dopuni_listu(Cvor ** adresa_glave);

#endif
