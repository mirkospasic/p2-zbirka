#include<stdio.h>
#include<stdlib.h>

typedef struct cvor {
  char zagrada;
  struct cvor *sledeci;
} Cvor;

int main()
{
  Cvor *stek = NULL;
  FILE *ulaz = NULL;
  char c;
  Cvor *pomocni = NULL;

  ulaz = fopen("dat.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke dat.txt!\n");
    exit(EXIT_FAILURE);
  }

  while ((c = fgetc(ulaz)) != EOF) {
    /* Ako je ucitana otvorena zagrada, stavlja se na stek. */
    if (c == '(' || c == '{' || c == '[') {
      pomocni = (Cvor *) malloc(sizeof(Cvor));
      if (pomocni == NULL) {
        fprintf(stderr, "Greska prilikom alokacije memorije!\n");
        return 1;
      }
      pomocni->zagrada = c;
      pomocni->sledeci = stek;
      stek = pomocni;
    }
    /* Ako je ucitana zatvorena zagrada, proverava se da li je
       stek je prazan i ako nije, da li se na vrhu steka nalazi
       odgovarajuca otvorena zagrada. */
    else {
      if (c == ')' || c == '}' || c == ']') {
        if (stek != NULL && ((stek->zagrada == '(' && c == ')')
                             || (stek->zagrada == '{' && c
                                 == '}')
                             || (stek->zagrada == '[' && c
                                 == ']'))) {
          /* Sa vrha steka se uklanja otvorena zagrada */
          pomocni = stek->sledeci;
          free(stek);
          stek = pomocni;
        } else {
          /* Zagrade u izrazu nisu ispravno uparene. */
          break;
        }
      }
    }
  }

  /* Ako je na kraju stek prazan i procitana je cela datoteka,
     zagrade su ispravno uparene, u suprotnom, nisu. */
  if (stek == NULL && c == EOF)
    printf("Zagrade su ispravno uparene.\n");
  else {
    printf("Zagrade nisu ispravno uparene.\n");

    while (stek != NULL) {
      /* U slucaju neispravnog uparivanja treba osloboditi
         memoriju koja je ostala zauzeta stekom. */
      pomocni = stek->sledeci;
      free(stek);
      stek = pomocni;
    }
  }

  fclose(ulaz);
  return 0;
}
