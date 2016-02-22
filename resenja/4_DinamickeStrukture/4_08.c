#include <stdio.h>
#include <stdlib.h>

/* Struktura kojom je predstavljen cvor liste sadrzi karakter koji
   predstavlja vidjenu zagradu i pokazivac na sledeci cvor liste */
typedef struct cvor {
  char zagrada;
  struct cvor *sledeci;
} Cvor;

/* Funkcija koja oslobadja memoriju zauzetu stekom */
void oslobodi_stek(Cvor ** stek)
{
  Cvor *tekuci;
  Cvor *pomocni;

  /* Oslobadja se cvor po cvor steka */
  tekuci = *stek;
  while (tekuci != NULL) {
    pomocni = tekuci->sledeci;
    free(tekuci);
    tekuci = pomocni;
  }

  /* Stek se proglasava praznim */
  *stek = NULL;
}

/* Glavni program */
int main()
{
  /* Stek je na pocetku prazan */
  Cvor *stek = NULL;
  FILE *ulaz = NULL;
  char c;
  Cvor *pomocni = NULL;

  /* Otvaranje datotoke za citanje izraza */
  ulaz = fopen("izraz.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr,
            "Greska: Neuspesno otvaranje datoteke izraz.txt!\n");
    exit(EXIT_FAILURE);
  }

  /* Cita karakter po karakter iz datoteke */
  while ((c = fgetc(ulaz)) != EOF) {
    /* Ako je ucitana otvorena zagrada, stavlja se na stek */
    if (c == '(' || c == '{' || c == '[') {
      /* Alocira se memorija za novi cvor liste i proverava se
         uspesnost alokacije */
      pomocni = (Cvor *) malloc(sizeof(Cvor));
      if (pomocni == NULL) {
        fprintf(stderr, "Greska: Neuspesna alokacija memorije!\n");
        /* Oslobadjanje memorije zauzete stekom */
        oslobodi_stek(&stek);
        /* Prekid izvrsavanja programa */
        exit(EXIT_FAILURE);
      }

      /* Inicijalizacija polja strukture */
      pomocni->zagrada = c;

      /* Promena vrha steka */
      pomocni->sledeci = stek;
      stek = pomocni;
    }
    /* Ako je ucitana zatvorena zagrada, proverava se da li je stek
       prazan i ako nije, da li se na vrhu steka nalazi odgovarajuca
       otvorena zagrada */
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
          /* Dakle, zagrade u izrazu nisu ispravno uparene */
          break;
        }
      }
    }
  }

  /* Procitana je cela datoteka i treba je zatvoriti. */
  fclose(ulaz);

  /* Ako je stek prazan i procitana je cela datoteka, zagrade su
     ispravno uparene. */
  if (stek == NULL && c == EOF)
    printf("Zagrade su ispravno uparene.\n");
  else {
    /* U suprotnom se zakljucuje da zagrade nisu ispravno uparene. */
    printf("Zagrade nisu ispravno uparene.\n");
    /* Oslobadja se memorija koja je ostala zauzeta stekom. */
    oslobodi_stek(&stek);
  }

  exit(EXIT_SUCCESS);
}
