#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

#define MAX 50

/* Funkcija koja obilazi stablo sa leva na desno i smesta vrednosti
   cvorova u niz. Povratna vrednost funkcije je broj vrednosti koje
   su smestene u niz. */
int kreiraj_niz(Cvor * koren, int a[])
{
  int r, s;

  /* Stablo je prazno - u niz je smesteno 0 elemenata */
  if (koren == NULL)
    return 0;

  /* Dodaju se u niz elementi iz levog podstabla */
  r = kreiraj_niz(koren->levo, a);

  /* Tekuca vrednost promenljive r je broj elemenata koji su upisani
     u niz i na osnovu nje se moze odrediti indeks novog elementa */

  /* Smesta se vrednost iz korena */
  a[r] = koren->broj;

  /* Dodaju se elementi iz desnog podstabla */
  s = kreiraj_niz(koren->desno, a + r + 1);

  /* Racuna se indeks na koji treba smestiti naredni element */
  return r + s + 1;
}

/* Funkcija sortira niz tako sto najpre elemente niza smesti u
   stablo, a zatim kreira novi niz prolazeci kroz stablo sa leva na
   desno. Povratna vrednost funkcije je 0 ukoliko je niz uspesno
   kreiran i sortiran, a 1 ukoliko je doslo do greske.

   Ovaj nacin sortiranja je primer sortiranja koje nije "u mestu"
   kao sto je to slucaj sa ostalim opisanim algoritmima sortiranja
   jer se sortiranje vrsi u pomocnoj dinamickoj strukturi, a ne
   razmenom elemenata niza. */
int sortiraj(int a[], int n)
{
  int i;
  Cvor *koren;

  /* Kreira se stablo smestanjem elemenata iz niza u stablo */
  koren = NULL;
  for (i = 0; i < n; i++) {
    if (dodaj_u_stablo(&koren, a[i]) == 1) {
      oslobodi_stablo(&koren);
      return 1;
    }
  }
  /* Infiksnim obilaskom stabla elementi iz stabla se prepisuju u
     niz a */
  kreiraj_niz(koren, a);

  /* Stablo vise nije potrebno pa se oslobadja zauzeta memorija */
  oslobodi_stablo(&koren);

  /* Vraca se indikator uspesnog sortiranja */
  return 0;
}

int main()
{
  int a[MAX];
  int n, i;

  /* Ucitavaju se dimenzija i elementi niza */
  printf("n: ");
  scanf("%d", &n);
  if (n < 0 || n > MAX) {
    printf("Greska: Pogresna dimenzija niza!\n");
    exit(EXIT_FAILURE);
  }

  printf("a: ");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Poziva se funkcija za sortiranje */
  if (sortiraj(a, n) == 0) {
    /* Ako je niz uspesno sortiran, ispisuje se rezultujuci niz */
    for (i = 0; i < n; i++)
      printf("%d ", a[i]);
    printf("\n");
  } else {
    /* Inace, obavestava se korisnik da je doslo do greske */
    printf("Greska: Problem prilikom sortiranja niza!\n");
  }

  exit(EXIT_SUCCESS);
}
