#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NISKI 1000
#define MAX_DUZINA 33

void sort_leksikografski(char niske[][MAX_DUZINA], int n)
{
  int i, j;
  int max;
  char pom[MAX_DUZINA];

  for (i = 0; i < n - 1; i++) {
    max = i;
    for (j = i + 1; j < n; j++)
      if (strcmp(niske[j], niske[max]) > 0)
        max = j;

    if (max != i) {
      strcpy(pom, niske[i]);
      strcpy(niske[i], niske[max]);
      strcpy(niske[max], pom);
    }
  }
}

int main()
{
  int i, n;

  /* Deklarisemo niz niski koji moze imati najvise MAX_NISKI elementa 
     od kojih je svaka niska duzine najvise MAX_DUZINA karaktera */
  char niske[MAX_NISKI][MAX_DUZINA];
  FILE *fp;

  /* Otvaramo datoteku za citanje */
  fp = fopen("niske.txt", "r");
  if (fp == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke.\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; fscanf(fp, "%s", niske[i]) != EOF && i < MAX_NISKI;
       i++);

  fclose(fp);
  n = i;

  /* Leksikografski sortiramo niz niski */
  sort_leksikografski(niske, n);

  /* Ispisujemo leksikografski sortirane niske */
  for (i = 0; i < n; i++)
    printf("%s\n", niske[i]);
  exit(EXIT_SUCCESS);
}
