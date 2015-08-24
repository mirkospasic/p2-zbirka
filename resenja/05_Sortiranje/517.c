#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <search.h>

#define MAX 100

/* Program demonstrira upotrebu funkcija qsort() i bsearch().
   Ove funkcije su definisane u standardnoj biblioteci i za
   njihovo koriscenje dovoljno je ukljuciti zaglavlje stdlib.h.
   Funkcija qsort() vrsi sortiranje niza metodom sortiranja
   razdvajanjem. Deklaracija ove funkcije je sledeca:

   void qsort(void *b, int n, int s, int(*comp)(const void *,
   const void *));

   Prvi argument je adresa pocetka niza koji se sortira. S
   obzirom da se ne zna tacan tip elemenata niza, koristi se
   genericki pokazivac (void *).  Drugi argument je broj
   elemenata niza, a treci velicina svakog od elemenata niza.
   Poslednji argument je pokazivac na funkciju poredjenja. Ova
   funkcija treba da prihvata adrese elemenata niza koji se
   porede, i da vraca >0 ako je prvi element veci, <0 ako je
   prvi element manji, a vraca 0 ako su elementi koji se porede
   jednaki. Na ovaj nacin se moze sortirati bilo koji niz,
   dovoljno je da je na neki nacin funkcijom poredjenja
   definisan potpuni poredak medju elementima niza. Argumenti
   funkcije poredjenja su takodje genericki pokazivaci, opet
   zato sto ne znamo tacno kog su tipa elementi niza. Ovi
   pokazivaci su jos kvalifikovani kljucnom recju const.

   Funkcija bsearch() vrsi pretrazivanje sortiranog niza metodom
   binarne pretrage. Funkcija ima sledecu deklaraciju:

   void *bsearch(const void *x, const void *b, int n, int s, int
   (*comp)(const void *, const void *));

   Prvi argument je pokazivac na podatak koji se trazi u nizu.
   Drugi argument je adresa pocetka niza, treci velicina niza, a
   cetvrti velicina elementa niza.  Poslednji argument je
   pokazivac na funkciju poredjenja koja definise poredak u
   skladu sa kojim je sortiran niz. Funkcija vraca adresu
   elementa u nizu koji je jednak trazenom elementu, ili NULL
   ukoliko element nije pronadjen.

   Osim ovih funkcija, postoji funkcija za linearnu pretragu.

   void *lfind(const void *x, void *b, int *n, int s, int
   (*comp)(const void *, const void *));

   ima potpuno iste argumente kao i bsearch() -- jedina razlika
   je u tome sto se kao treci argument ne predaje duzina niza vec 
   adresa celobrojne promenljive u kojoj se nalazi duzina niza.
   Funkcija za uporedjivanja elemenata na koju pokazuje pokazivac 
   comp treba da zadovoljava ista pravila kao i kod prethodnih
   funkcija. Medjutim, s obzirom da se kod linearne pretrage
   koristi iskljucivo poredjenje na jednakost, dovoljno je da
   funkcija za uporedjivanje vraca 0, ako su objekti koji se
   uporedjuju jednaki, a razlicitu vrednost od nule u suprotnom.
   Funkcija vraca pokazivac na pronadjeni element ili NULL u
   slucaju neuspesne pretrage. */

/* NAPOMENA: Pokazivac na void je pokazivac koji moze sadrzati
   adresu bilo kog podatka u memoriji. Svaki pokazivac se moze
   bez konverzije dodeliti ovom pokazivacu, kao i obrnuto. Moze
   se koristiti za cuvanje adrese podatka za koji unapred ne
   znamo kog ce biti tipa. Njegova glavna karakteristika je da
   se ne moze dereferencirati, zato sto se ne zna kog je tipa
   ono na sta on pokazuje. Programer mora na drugi nacin da
   utvrdi kog je tipa podatak na toj adresi, pa da najpre
   konvertuje void pokazivac u odgovarajuci tip pokazivaca, a
   zatim da ga tako konvertovanog dereferencira. */

/* Funkcija poredi dva cela broja */
int compare_int(const void *a, const void *b)
{
  /* Konvertujemo void pokazivace u int pokazivace koje zatim
     dereferenciramo, dobijamo int-ove koje oduzimamo i razliku
     vracamo. */

  /* Zbog moguceg prekoracenja opsega celih brojeva necemo ih
     oduzimati return *((int *)a) - *((int *)b); */

  int b1 = *((int *) a);
  int b2 = *((int *) b);

  if (b1 > b2)
    return 1;
  else if (b1 < b2)
    /* Ovo uredjenje favorizujemo jer zelimo rastuci poredak */
    return -1;
  else
    return 0;
}

int compare_int_desc(const void *a, const void *b)
{
  /* Za obrnuti poredak mozemo samo oduzimati a od b */
  /* return *((int *)b) - *((int *)a); */

  /* Ili samo promeniti znak vrednosti koju koju vraca prethodna
     funkcija */
  return -compare_int(a, b);
}

/* Test program */
int main()
{
  size_t n;
  int i, x;
  int a[MAX], *p = NULL;

  /* Unosimo dimenziju */
  printf("Uneti dimenziju niza: ");
  scanf("%ld", &n);
  if (n > MAX)
    n = MAX;

  /* Unosimo elemente niza */
  printf("Uneti elemente niza:\n");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Sortiramo niz celih brojeva */
  qsort(a, n, sizeof(int), &compare_int);

  /* Prikazujemo sortirani niz */
  printf("Sortirani niz u rastucem poretku:\n");
  for (i = 0; i < n; i++)
    printf("%d ", a[i]);
  putchar('\n');

  /* Pretrazivanje niza */
  /* Vrednost koju cemo traziti u nizu */
  printf("Uneti element koji se trazi u nizu: ");
  scanf("%d", &x);

  printf("Binarna pretraga: \n");
  p = bsearch(&x, a, n, sizeof(int), &compare_int);

  if (p == NULL)
    printf("Elementa nema u nizu!\n");
  else
    printf("Element je nadjen na poziciji %ld\n", p - a);

  printf("Linearna pretraga (lfind): \n");
  p = lfind(&x, a, &n, sizeof(int), &compare_int);
  if (p == NULL)
    printf("Elementa nema u nizu!\n");
  else
    printf("Element je nadjen na poziciji %ld\n", p - a);

  return 0;
}
