#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Funkcija obrce elemente niza koriscenjem indekse sintakse */
void obrni_niz_v1(int a[], int n)
{
  int i, j;

  for (i = 0, j = n - 1; i < j; i++, j--) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
}

/* Funkcija obrce elemente niza koriscenjem pokazivacke sintakse */
void obrni_niz_v2(int *a, int n)
{
  /* Pokazivaci na elemente niza */
  int *prvi, *poslednji;

  /* Vrsi se obrtanje niza */
  for (prvi = a, poslednji = a + n - 1; prvi < poslednji;) {
    int t = *prvi;

    /* Na adresu na koju pokazuje pokazivac "prvi" postavlja se
       vrednost koja se nalazi na adresi na koju pokazuje pokazivac
       "poslednji". Nakon toga se pokazivac "prvi" uvecava za jedan
       sto za posledicu ima da "prvi" pokazuje na sledeci element u
       nizu */
    *prvi++ = *poslednji;

    /* Vrednost promenljive "t" se postavlja na adresu na koju
       pokazuje pokazivac "poslednji". Ovaj pokazivac se zatim
       umanjuje za jedan, cime pokazivac "poslednji" pokazuje na
       element koji mu prethodi u nizu */
    *poslednji-- = t;
  }

  /******************************************************************
    Drugi nacin za obrtanje niza

    for (prvi = a, poslednji = a + n - 1; prvi < poslednji;
                                          prvi++, poslednji--) {
      int t = *prvi;
      *prvi = *poslednji;
      *poslednji = t;
    }
   ******************************************************************/
}

int main()
{
  /* Deklarise se niz od najvise MAX elemenata */
  int a[MAX];

  /* Broj elemenata niza a */
  int n;

  /* Pokazivac na elemente niza */
  int *p;

  printf("Unesite dimenziju niza: ");
  scanf("%d", &n);

  /* Proverava se da li je doslo do prekoracenja ogranicenja
     dimenzije */
  if (n <= 0 || n > MAX) {
    fprintf(stderr, "Greska: Neodgovarajuca dimenzija niza.\n");
    exit(EXIT_FAILURE);
  }

  printf("Unesite elemente niza:\n");
  for (p = a; p - a < n; p++)
    scanf("%d", p);

  obrni_niz_v1(a, n);

  printf("Nakon obrtanja elemenata, niz je:\n");

  for (p = a; p - a < n; p++)
    printf("%d ", *p);
  printf("\n");

  obrni_niz_v2(a, n);

  printf("Nakon ponovnog obrtanja elemenata, niz je:\n");

  for (p = a; p - a < n; p++)
    printf("%d ", *p);
  printf("\n");

  exit(EXIT_SUCCESS);
}
