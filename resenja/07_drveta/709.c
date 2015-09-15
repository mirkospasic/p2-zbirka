#include <stdio.h>
#include <stdlib.h>

/* Ukljucujemo biblioteku za rad sa stablima */
#include "stabla.h"

#define MAX 50

/* Funkcija koja obilazi stablo sa leva na desno i smesta
   vrednosti cvorova u niz. Povratna vrednost funkcije je broj
   vrednosti koje su smestene u niz. */

int kreiraj_niz(Cvor * koren, int a[])
{
  int r, s;

  /* Stablo je prazno - u niz je smesteno 0 elemenata */
  if (koren == NULL)
    return 0;

  /* Dodajemo u niz elemente iz levog podstabla */
  r = kreiraj_niz(koren->levo, a);

  /* Tekuca vrednost promenljive r je broj elemenata koji su
     upisani u niz i na osnovu nje mozemo odrediti indeks novog
     elementa */

  /* Smestamo vrednost iz korena */
  a[r] = koren->broj;

  /* Dodajemo elemente iz desnog podstabla */
  s = kreiraj_niz(koren->desno, a + r + 1);

  /* Racunamo indeks na koji treba smestiti naredni element */
  return r + s + 1;
}


/* Funkcija sortira niz tako sto najpre elemente niza smesti u
   stablo, a zatim kreira novi niz prolazeci kroz stablo sa leva 
   u desno.

   Ovaj nacin sortiranja primer sortiranja koje nije "u mestu "
   kao sto je to slucaj sa ostalim prethodno opisanim
   algoritmima sortiranja, jer se sortiranje vrsi u pomocnoj
   dinamickoj strukturi, a ne razmenom elemenata niza. */

void sortiraj(int a[], int n)
{
  int i;
  Cvor *koren;

  /* Kreiramo stablo smestanjem elemenata iz niza u stablo */
  koren = NULL;
  for (i = 0; i < n; i++)
    dodaj_u_stablo(&koren, a[i]);

  /* Infiksnim obilaskom stabla elemente iz stabla prepisujemo u
     niz a */
  kreiraj_niz(koren, a);

  /* Vise nam stablo nije potrebno i oslobadjamo memoriju */
  oslobodi_stablo(&koren);
}


int main()
{
  int a[MAX];
  int n, i;

  /* Ucitavamo dimenziju i elemente niza */
  printf("n: ");
  scanf("%d", &n);
  if (n < 0 || n > MAX) {
    printf("Greska: pogresna dimenzija niza!\n");
    return 0;
  }

  printf("a: ");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Pozivamo funkciju za sortiranje */
  sortiraj(a, n);

  /* Ispisujemo rezultat */
  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");

  /* Prekidamo sa programom */
  return 0;
}
