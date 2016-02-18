#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 128

/* Funkcija poredi dva karaktera */
int uporedi_char(const void *pa, const void *pb)
{
  return *(char *) pa - *(char *) pb;
}

/* Funkcija vraca 1 ako su argumenti anagrami, a 0 inace */
int anagrami(char s[], char t[])
{
  /* Ako dve niske imaju razlicitu duzinu onda one nisu anagrami */
  if (strlen(s) != strlen(t))
    return 0;

  /* Sortiraju se karakteri u niskama */
  qsort(s, strlen(s) / sizeof(char), sizeof(char), &uporedi_char);
  qsort(t, strlen(t) / sizeof(char), sizeof(char), &uporedi_char);

  /* Ako su niske nakon sortiranja iste onda one jesu anagrami, u
     suprotnom, nisu */
  return !strcmp(s, t);
}

int main()
{
  char s[MAX], t[MAX];

  /* Unose se niske */
  printf("Unesite prvu nisku: ");
  scanf("%s", s);
  printf("Unesite drugu nisku: ");
  scanf("%s", t);

  /* Ispituje se da li su niske anagrami */
  if (anagrami(s, t))
    printf("jesu\n");
  else
    printf("nisu\n");

  return 0;
}
