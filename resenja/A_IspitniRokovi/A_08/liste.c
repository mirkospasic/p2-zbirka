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

/* Funkcija dodaje novi cvor na kraj liste. Vraca 1 ukoliko je bilo
   greske pri alokaciji memorije, inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, double broj)
{
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;
  if (*adresa_glave == NULL) {
    *adresa_glave = novi;
    return 0;
  }
  Cvor *poslednji = pronadji_poslednji(*adresa_glave);
  poslednji->sledeci = novi;
  return 0;
}

/* Funkcija prikazuje elemente liste pocev od glave ka kraju liste. */
void ispisi_listu(Cvor * glava)
{
  for (; glava != NULL; glava = glava->sledeci)
    printf("%.2lf ", glava->vrednost);
  putchar('\n');

}
