#include<stdio.h>
#include<string.h>

#define MAX_DIM 128

/* Funkcija za sortiranje niza karaktera */
void selectionSort(char s[])
{
  int i, j, min;
  char pom;
  for (i = 0; s[i] != '\0'; i++) {
    min = i;
    for (j = i + 1; s[j] != '\0'; j++)
      if (s[j] < s[min])
        min = j;
    if (min != i) {
      pom = s[i];
      s[i] = s[min];
      s[min] = pom;
    }
  }
}

/* Funkcija vraca 1 ako su argumenti anagrami, a 0 inace. */
int anagrami(char s[], char t[])
{
  int i;

  /* Ako dve niske imaju razlicit broj karaktera onda one nisu
     anagrami */
  if (strlen(s) != strlen(t))
    return 0;

  /* Sortiramo niske */
  selectionSort(s);
  selectionSort(t);

  /* Dve sortirane niske su anagrami ako i samo ako su jednake */
  for (i = 0; s[i] != '\0'; i++)
    if (s[i] != t[i])
      return 0;
  return 1;
}

int main()
{
  char s[MAX_DIM], t[MAX_DIM];

  /* Ucitavanje niski sa ulaza */
  printf("Unesite prvu nisku: ");
  scanf("%s", s);
  printf("Unesite drugu nisku: ");
  scanf("%s", t);

  /* Poziv funkcije */
  if (anagrami(s, t))
    printf("jesu\n");
  else
    printf("nisu\n");

  return 0;
}
