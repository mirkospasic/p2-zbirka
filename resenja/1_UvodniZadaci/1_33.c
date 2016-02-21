#include <stdio.h>
#include <stdlib.h>
#define  MAKS_DUZINA_PERMUTACIJE 15

/* Funkcija koja ispisuje elemente niza a duzine n */
void ispisi_niz(int a[], int n)
{
  int i;

  for (i = 1; i <= n; i++)
    printf("%d ", a[i]);
  printf("\n");
}

/* Funkcija koja vraca 1, ako se broj x nalazi u nizu a duzine n,
   inace vraca 0 */
int koriscen(int a[], int n, int x)
{
  int i;

  /* Obilaze se svi elementi niza */
  for (i = 1; i <= n; i++)
    /* Ukoliko se naidje na trazenu vrednost, pretraga se prekida */
    if (a[i] == x)
      return 1;

  /* Zakljucuje se da broj nije pronadjen */
  return 0;
}

/* Funkcija koja ispisuje sve permutacije od skupa {1,2,...,n}
   dobija kao argument niz a[] u koji se smesta permutacija, broj m
   oznacava da se u okviru tog poziva funkcije na m-tu poziciju u
   permutaciji smesta jedan od preostalih celih brojeva, n je
   velicina skupa koji se permutuje. Funkciju se inicijalno poziva
   sa argumentom m = 1, jer formiranje permutacije pocinje od
   pozicije broj 1. Stoga, a[0] se ne koristi. */
void permutacija(int a[], int m, int n)
{
  int i;

  /* Izlaz iz rekurzije: Ako je pozicija na koju treba smestiti broj
     premasila velicinu skupa, onda se svi brojevi vec nalaze u
     permutaciji i ispisuje se permutacija. */
  if (m > n) {
    ispisi_niz(a, n);
    return;
  }

  /* Ideja: pronalazi se prvi broj koji moze da se postavi na m-to
     mesto u nizu (broj koji se do sada nije pojavio u permutaciji).
     Zatim, rekurzivno se pronalaze one permutacije koje odgovaraju
     ovako postavljenom pocetku permutacije. Kada se to zavrsi, vrsi
     se provera da li postoji jos neki broj koji moze da se stavi na
     m-to mesto u nizu (to se radi u petlji). Ako ne postoji,
     funkcija zavrsava sa radom. Ukoliko takav broj postoji, onda se
     ponovo poziva rekurzivno pronalazenje odgovarajucih permutacija, 
     ali sada sa drugacije postavljenim prefiksom. */
  for (i = 1; i <= n; i++) {
    /* Ako se broj i nije do sada pojavio u permutaciji od 1 do m-1
       pozicije, onda se on postavlja na poziciju m i poziva se
       ponovo funkcija da dopuni ostatak permutacije posle
       upisivanja i na poziciju m. Inace, nastavlja se dalje,
       trazeci broj koji se nije pojavio do sada u permutaciji. */
    if (!koriscen(a, m - 1, i)) {
      a[m] = i;
      permutacija(a, m + 1, n);
    }
  }
}

int main(void)
{
  int n;
  int a[MAKS_DUZINA_PERMUTACIJE + 1];

  /* Ucitava se broj n iz odgovarajuceg opsega */
  scanf("%d", &n);
  if (n < 0 || n > MAKS_DUZINA_PERMUTACIJE) {
    fprintf(stderr,
            "Greska: Duzina permutacije mora biti broj iz intervala [0, %d]!\n",
            MAKS_DUZINA_PERMUTACIJE);
    exit(EXIT_FAILURE);
  }

  /* Ispisuju se permutacije duzine n */
  permutacija(a, 1, n);

  exit(EXIT_SUCCESS);
}
