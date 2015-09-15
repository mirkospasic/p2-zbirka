#include<stdio.h>
#include<stdlib.h>

typedef struct cvor {
  char z;
  struct cvor *sledeci;
} Cvor;

int main()
{
  Cvor *stek = NULL;
  FILE *in = NULL;
  char pom;
  Cvor *tmp = NULL;

  in = fopen("dat.txt", "r");
  if (in == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke dat.txt!\n");
    exit(EXIT_FAILURE);
  }

  while ((pom = fgetc(in)) != EOF) {
    /* Ako je ucitana otvorena zagrada stavljamo je na stek */
    if (pom == '(' || pom == '{' || pom == '[') {
      Cvor *tmp = (Cvor *) malloc(sizeof(Cvor));
      if (tmp == NULL) {
        fprintf(stderr, "Greska prilikom alokacije memorije!\n");
        return 1;
      }
      tmp->z = pom;
      tmp->sledeci = stek;
      stek = tmp;
    }
    /* Ako je ucitana zatvorena zagrada proveravamo da stek nije 
       prazan i da li se na vrhu steka nalazi njegova
       odgovarajuca otvorena zagrada. */
    else {
      if (pom == ')' || pom == '}' || pom == ']') {
        if (stek != NULL && ((stek->z == '(' && pom == ')')
                             || (stek->z == '{' && pom == '}')
                             || (stek->z == '[' && pom == ']'))) {
          /* Sa vrha steka uklanjamo otvorenu zagradu. */
          Cvor *tmp = stek->sledeci;
          free(stek);
          stek = tmp;
        } else {
          /* Zagrade u aritmetickom izrazu nisu ispravno
             uparene. */
          break;
        }
      }
    }
  }

  /* Ako je na kraju stek prazan i procitali smo datoteku,
     zagrade su ispravno uparene, u suprotnom, nisu. */
  if (stek == NULL && pom == EOF)
    printf("Zagrade su ispravno uparene.\n");
  else {
    printf("Zagrade nisu ispravno uparene.\n");

    while (stek != NULL) {
      /* Oslobadjamo memoriju koja je ostala na steku, u slucaju 
         neispravnog uparivanja. */
      Cvor *tmp = stek->sledeci;
      free(stek);
      stek = tmp;
    }
  }

  fclose(in);
  return 0;
}
