/* liste.c */

#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/* Pomocna funkcija koja kreira cvor. */
Cvor *napravi_cvor(double broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* inicijalizacija polja u novom cvoru */
  novi->vrednost = broj;
  novi->sledeci = NULL;

  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente liste
   ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave)
{
  Cvor *pomocni = NULL;

  while (*adresa_glave != NULL) {
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi i
   ukoliko alokacija nije bila uspesna, oslobadja se sva prethodno
   zauzeta memorija za listu cija pocetni cvor se nalazi na adresi
   adresa_glave.  */
void proveri_alokaciju(Cvor ** adresa_glave, Cvor * novi)
{
  /* Ukoliko je novi NULL */
  if (novi == NULL) {
    fprintf(stderr, "Neuspela alokacija za nov cvor\n");
    oslobodi_listu(adresa_glave);
    exit(EXIT_FAILURE);
  }
}

/* Funkcija pronalazi i vraca pokazivac na poslednji element liste,
   ili NULL kao je lista prazna */
Cvor *pronadji_poslednji(Cvor * glava)
{
  /* Ako je lista prazna, nema ni poslednjeg cvor i u tom slucaju
     funkcija vraca NULL. */
  if (glava == NULL)
    return NULL;

  while (glava->sledeci != NULL)
    glava = glava->sledeci;

  return glava;
}

/* Funkcija dodaje novi cvor na kraj liste. */
void dodaj_na_kraj_liste(Cvor ** adresa_glave, double broj)
{
  Cvor *novi = napravi_cvor(broj);
  proveri_alokaciju(adresa_glave, novi);

  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    return;
  }

  Cvor *poslednji = pronadji_poslednji(*adresa_glave);
  poslednji->sledeci = novi;
}

/* Funkcija prikazuje elemente liste pocev od glave ka kraju liste. */
void ispisi_listu(Cvor * glava)
{
  for (; glava != NULL; glava = glava->sledeci)
    printf("%.2lf ", glava->vrednost);

  putchar('\n');
}

/* Funkcija koja dopunjuje listu na nacin opisan u tekstu zadatka */
void dopuni_listu(Cvor ** adresa_glave)
{
  Cvor *tekuci;
  Cvor *novi;
  double aritmeticka_sredina;
  if (*adresa_glave == NULL || (*adresa_glave)->sledeci == NULL)
    return;

  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL) {
    aritmeticka_sredina =
        ((tekuci)->vrednost + ((tekuci)->sledeci)->vrednost) / 2;
    novi = napravi_cvor(aritmeticka_sredina);
    proveri_alokaciju(adresa_glave, novi);

    novi->sledeci = tekuci->sledeci;
    tekuci->sledeci = novi;
    tekuci = tekuci->sledeci;
    tekuci = tekuci->sledeci;
  }

  return;
}
