#include <stdio.h>
#include <stdlib.h>

/* Struktura kojom je predstavljen cvor liste sadrzi karakter zagrade 
   i pokazivac na sledeci cvor liste. */
typedef struct cvor {
  char zagrada;
  struct cvor *sledeci;
} Cvor;

/* Glavni program */
int main()
{
  /* Stek je na pocetku prazan. */
  Cvor *stek = NULL;
  FILE *ulaz = NULL;
  char c;
  Cvor *pomocni = NULL;

  /* Otvaranje datotoke za citanje izraza */
  ulaz = fopen("izraz.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke izraz.txt!\n");
    exit(EXIT_FAILURE);
  }

  /* Cita je karakter po karakter iz datoteke dok se ne dodje do
     kraja. */
  while ((c = fgetc(ulaz)) != EOF) {
    /* Ako je ucitana otvorena zagrada, stavlja se na stek. */
    if (c == '(' || c == '{' || c == '[') {
      /* Alocira se memorija za novi cvor liste i proverava uspesnost 
         alokacije */
      pomocni = (Cvor *) malloc(sizeof(Cvor));
      if (pomocni == NULL) {
        fprintf(stderr, "Greska prilikom alokacije memorije!\n");
        return 1;
      }

      /* Inicijalizacija polja strukture */
      pomocni->zagrada = c;
      pomocni->sledeci = stek;
      stek = pomocni;
    }
    /* Ako je ucitana zatvorena zagrada, proverava se da li je stek
       prazan i ako nije, da li se na vrhu steka nalazi odgovarajuca
       otvorena zagrada. */
    else {
      if (c == ')' || c == '}' || c == ']') {
        if (stek != NULL && ((stek->zagrada == '(' && c == ')')
                             || (stek->zagrada == '{' && c == '}')
                             || (stek->zagrada == '[' && c == ']'))) {
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

  /* Procitana je cela datoteka i treba je zatvoriti. */
  fclose(ulaz);

  /* Ako je stek prazan i procitana je cela datoteka, zagrade su
     ispravno uparene, u suprotnom, nisu. */
  if (stek == NULL && c == EOF)
    printf("Zagrade su ispravno uparene.\n");
  else {
    printf("Zagrade nisu ispravno uparene.\n");
    /* U slucaju neispravnog uparivanja treba osloboditi memoriju
       koja je ostala zauzeta stekom. */
    while (stek != NULL) {
      pomocni = stek->sledeci;
      free(stek);
      stek = pomocni;
    }
  }

  return 0;
}
