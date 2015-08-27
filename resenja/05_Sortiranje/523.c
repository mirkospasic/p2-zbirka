#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define MAX_DUZINA 32

/* Funkcija poredi dve niske (stringove) */
int uporedi_niske(const void *pa, const void *pb)
{
  return strcmp((char *) pa, (char *) pb);
}

int main()
{
  int i, n;
  char S[MAX][MAX_DUZINA];

  /* Unos broja niski */
  printf("Unesite broj niski:");
  scanf("%d", &n);

  /* Unos niza niski */
  printf("Unesite niske:\n");
  for (i = 0; i < n; i++)
    scanf("%s", S[i]);

  /* Sortiramo niz niski */
  qsort(S, n, MAX_DUZINA * sizeof(char), &uporedi_niske);

  /******************************************************
    Ovaj deo je iskomentarisan jer se u zadatku ne trazi ispis
    sortiranih niski. Koriscen je samo u fazi testiranja programa.

    printf("Sortirane niske su:\n");
    for(i = 0; i < n; i++)
      printf("%s ", S[i]);
  *******************************************************/

  /* Ako postoje dve iste niske u nizu, onda ce one nakon
     sortiranja niza biti jedna do druge */
  for (i = 0; i < n - 1; i++)
    if (strcmp(S[i], S[i + 1]) == 0) {
      printf("ima\n");
      return 0;
    }

  printf("nema\n");
  return 0;
}
