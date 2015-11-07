#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/* Funkcija koja dopunjuje listu na nacin opisan u tekstu zadatka.   Vraca 1 ukoliko je bilo greske pri alokaciji memorije, inace vraca   0. */ 
int dopuni_listu(Cvor ** adresa_glave) 
{
  Cvor * tekuci;
  Cvor * novi;
  double aritmeticka_sredina;
  if (*adresa_glave == NULL || (*adresa_glave)->sledeci == NULL)
    return 1;
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL) {
    aritmeticka_sredina = 
        ((tekuci)->vrednost + ((tekuci)->sledeci)->vrednost) / 2;
    novi = napravi_cvor(aritmeticka_sredina);
    if (novi == NULL)
      return 1;
    novi->sledeci = tekuci->sledeci;
    tekuci->sledeci = novi;
    tekuci = tekuci->sledeci;
    tekuci = tekuci->sledeci;  
  }
  return 0;
}
int main() 
{   Cvor * glava = NULL;
  double broj;
  
  /* Ucitavanje se vrsi do kraja ulaza. Elementi se dodaju na kraj      liste! */ 
  while (scanf("%lf", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji       memorije za nov cvor. Memoriju alociranu za cvorove liste        treba osloboditi. */ 
    if (dodaj_na_kraj_liste(&glava, broj) == 1) {
      fprintf(stderr, "Neuspela alokacija za cvor %d\n", broj);
      oslobodi_listu(&glava);
      exit(EXIT_FAILURE);
    }
  }
  
  /* Pozivanje funkcije da dopuni listu. Ako je funkcija vratila 1,      onda je bilo greske pri alokaciji memorije za nov cvor. Memoriju     alociranu za cvorove liste treba osloboditi. */ 
  if (dopuni_listu(&glava) == 1) {
    fprintf(stderr, "Neuspela alokacija za cvor %d\n", broj);
    oslobodi_listu(&glava);
    exit(EXIT_FAILURE);
  }
    /* Ispisivanje liste */ 
  ispisi_listu(glava);
    /* Oslobadjanje liste */ 
  oslobodi_listu(&glava);
  
  return 0;}


