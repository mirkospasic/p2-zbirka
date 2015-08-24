#include<stdio.h>
#include<string.h>

#define MAX_DIM 128

/* Funkcija za sortiranje niza */
void selectionSort(char s[], int n)
{
  int i, j, min;
  char pom;
  for (i = 0; i < n; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (s[j] < s[min])
        min = j;
    if (min != i) {
      pom = s[i];
      s[i] = s[min];
      s[min] = pom;
    }
  }
}

/* Funkcija vraca: 1 - ako jesu anagrami; 0 - inace.
   pretpostavlja se da su niske s i t sortirane */
int anagrami(char s[], char t[], int n_s, int n_t)
{
  int i, n;

  /* Ako dve niske imaju razlicit broj elemenata onda nisu
     anagrami */
  if (n_s != n_t)
    return 0;

  n = n_s;

  /* Dve sortirane niske su anagrami akko su jednake */
  for (i = 0; i < n; i++)
    if (s[i] != t[i])
      return 0;
  return 1;
}

int main()
{
  char s[MAX_DIM], t[MAX_DIM];
  int n_s, n_t;

  /* Ucitavamo dve niske sa ulaza */
  printf("Unesite prvu nisku: ");
  scanf("%s", s);
  printf("Unesite drugu nisku: ");
  scanf("%s", t);

  /* Odredjujemo duzinu niski */
  n_s = strlen(s);
  n_t = strlen(t);

  /* Sortiramo niske */
  selectionSort(s, n_s);
  selectionSort(t, n_t);

  /* Proveravamo da li su niske anagrami */
  if (anagrami(s, t, n_s, n_t))
    printf("jesu\n");
  else
    printf("nisu\n");
  return 0;
}
