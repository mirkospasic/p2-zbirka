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
   stablo, a zatim kreira novi niz prolazeci kroz stablo sa leva u
   desno.

   Ovaj nacin sortiranja je primer sortiranja koje nije "u mestu" kao 
   sto je to slucaj sa ostalim opisanim algoritmima sortiranja jer se 
   sortiranje vrsi u pomocnoj dinamickoj strukturi, a ne razmenom
   elemenata niza. */
void sortiraj(int a[], int n)
{
  int i;
  Cvor *koren;

  /* Kreira se stablo smestanjem elemenata iz niza u stablo */
  koren = NULL;
  for (i = 0; i < n; i++)
    dodaj_u_stablo(&koren, a[i]);

  /* Infiksnim obilaskom stabla elementi iz stabla se prepisuju u niz 
     a */
  kreiraj_niz(koren, a);

  /* Stablo vise nije potrebno pa se oslobadja memorija koju zauzima */
  oslobodi_stablo(&koren);
}

int main()
{
  int a[MAX];
  int n, i;

  /* Ucitavaju se dimenzija i elementi niza */
  printf("n: ");
  scanf("%d", &n);
  if (n < 0 || n > MAX) {
    printf("Greska: pogresna dimenzija niza!\n");
    return 0;
  }

  printf("a: ");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Poziva se funkcija za sortiranje */
  sortiraj(a, n);

  /* Ispisuje se rezultat */
  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");

  return 0;
}
