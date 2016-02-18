#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

/* Funkcija dinamicki kreira niz karaktera u koji smesta rezultat
   nadovezivanja niski. Adresa kreiranog niza se vraca kao povratna
   vrednost. */
char *nadovezi(char *s, char *t)
{
  char *p = (char *) malloc((strlen(s) + strlen(t) + 1)
                            * sizeof(char));

  /* Proverava se da li je memorija uspesno alocirana */
  if (p == NULL) {
    fprintf(stderr, "Greska: Neuspesna alokacija memorije.\n");
    exit(EXIT_FAILURE);
  }

  /* Kopiraju se i nadovezuju niske karaktera */
  strcpy(p, s);
  strcat(p, t);

  return p;
}

int main()
{
  char *s = NULL;
  char s1[MAX], s2[MAX];

  printf("Unesite dve niske karaktera:\n");
  scanf("%s", s1);
  scanf("%s", s2);

  /* Poziva se funkcija koja nadovezuje niske */
  s = nadovezi(s1, s2);

  /* Prikazuje se rezultat */
  printf("Nadovezane niske: %s\n", s);

  /* Oslobadja se memorija alocirana u funkciji nadovezi() */
  free(s);

  exit(EXIT_SUCCESS);
}
