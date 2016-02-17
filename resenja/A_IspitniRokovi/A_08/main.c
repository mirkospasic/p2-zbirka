#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/* Funkcija umece novi cvor iza tekuceg u listi */
void dodaj_iza(Cvor * tekuci, Cvor * novi)
{
  /* Novi cvor se dodaje iza tekuceg cvora. */
  novi->sledeci = tekuci->sledeci;
  tekuci->sledeci = novi;
}


/* Funkcija koja dopunjuje listu na nacin opisan u tekstu zadatka.
   Vraca 1 ukoliko je bilo greske pri alokaciji memorije, inace vraca
   0. */
int dopuni_listu(Cvor ** adresa_glave)
{
  Cvor *tekuci;
  Cvor *novi;
  double aritmeticka_sredina;
  /* U slucaju prazne ili jednoclane liste, funkcija vraca 1 */
  if (*adresa_glave == NULL || (*adresa_glave)->sledeci == NULL)
    return 1;
  /* Promenljiva tekuci se inicijalizacuje da pokazuje na pocetni
     cvor */
  tekuci = *adresa_glave;
  /* Sve dok ima cvorova u listi racuna se aritmeticka sredina
     vrednosti u susednim cvorovims i kreira cvor sa tom vrednoscu. U 
     slucaju neupele alokacije novog cvora, funkcija vraca 1. Inace, 
     novi cvor se umece izmedju dva cvora za koje racunata
     aritmeticka sredina */
  while (tekuci->sledeci != NULL) {
    aritmeticka_sredina =
        ((tekuci)->vrednost + ((tekuci)->sledeci)->vrednost) / 2;
    novi = napravi_cvor(aritmeticka_sredina);
    if (novi == NULL)
      return 1;
    /* Poziva se funkcija koja umece novi cvor iza tekuceg cvora */
    dodaj_iza(tekuci, novi);
    /* Tekuci cvor se pomera na narednog u listi (to je novoumetnuti
       cvor), a zatim jos jednom da bi pokazivao na naredni cvor iz
       polazne liste */
    tekuci = tekuci->sledeci;
    tekuci = tekuci->sledeci;
  }
  return 0;
}

int main()
{
  Cvor *glava = NULL;
  double broj;

  /* Dok se ne stigne do kraja ulaza, ucitavaju se elementi i dodaju 
     se na kraj liste */
  while (scanf("%lf", &broj) > 0) {
    /* Ako je funkcija vratila 1, onda je bilo greske pri alokaciji
       memorije za nov cvor. Memoriju alociranu za cvorove liste
       treba osloboditi. */
    if (dodaj_na_kraj_liste(&glava, broj) == 1) {
      fprintf(stderr, "Greska: Neuspela alokacija za cvor %lf.\n", broj);
      oslobodi_listu(&glava);
      exit(EXIT_FAILURE);
    }
  }

  /* Poziva se funkcija da dopuni listu. Ako je funkcija vratila 1,
     onda je bilo greske pri alokaciji memorije za nov cvor. Memoriju
     alociranu za cvorove liste treba osloboditi. */
  if (dopuni_listu(&glava) == 1) {
    fprintf(stderr, "Greska: Neuspela alokacija za cvor %lf.\n", broj);
    oslobodi_listu(&glava);
    exit(EXIT_FAILURE);
  }

  /* Ispisuju se elementi liste */
  ispisi_listu(glava);

  /* Oslobadja se memorija rezervisana za listu */
  oslobodi_listu(&glava);

  exit(EXIT_SUCCESS);
}
