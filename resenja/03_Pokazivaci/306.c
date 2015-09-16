#include<stdio.h>
#include<stdlib.h>

#define MAX_KARAKTERA 100

/* Funkcija strlen() iz standardne biblioteke */
int duzina(char *s)
{
  int i;
  for (i = 0; *(s + i); i++);
  return i;
}

int main(int argc, char **argv)
{
  char rec[MAX_KARAKTERA];
  int br = 0, n;
  FILE *in;

  /* Ako korisnik nije uneo trazene argumente, prijavljujemo
     gresku */
  if (argc < 3) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s ime_dat br_karaktera.\n",
           argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaramo datoteku sa imenom koje se zadaje kao prvi
     argument komandne linije. */
  in = fopen(*(argv + 1), "r");
  if (in == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke %s.\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  n = atoi(*(argv + 2));

  /* Broje se reci cija je duzina jednaka broju zadatom drugim
     argumentom komandne linije */
  while (fscanf(in, "%s", rec) != EOF)
    if (duzina(rec) == n)
      br++;

  printf("%d\n", br);

  /* Zatvaramo datoteku */
  fclose(in);
  return 0;
}
