#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX 128

/* Funkcija poredi dva karaktera */
int uporedi_char(const void *pa, const void *pb)
{
  return *(char *) pa - *(char *) pb;
}

/* Funkcija vraca: 1 - ako jesu anagrami 0 - inace */
int anagrami(char s[], char t[], int n_s, int n_t)
{
  /* Ako dve niske imaju razlicitu duzinu => nisu anagrami */
  if (n_s != n_t)
    return 0;

  /* Sortiramo niske */
  qsort(s, strlen(t) / sizeof(char), sizeof(char),
        &uporedi_char);
  qsort(t, strlen(t) / sizeof(char), sizeof(char),
        &uporedi_char);

  /* Ako su niske nakon sortiranja iste => jesu anagrami, u
     suprotnom, nisu */
  return !strcmp(s, t);
}

int main()
{
  char s[MAX], t[MAX];

  /* Unose se dve niske sa ulaza */
  printf("Unesite prvu nisku: ");
  scanf("%s", s);

  printf("Unesite drugu nisku: ");
  scanf("%s", t);

  /* Ispituje se da li su niske anagrami */
  if (anagrami(s, t, strlen(s), strlen(t)))
    printf("jesu\n");
  else
    printf("nisu\n");

  return 0;
}
