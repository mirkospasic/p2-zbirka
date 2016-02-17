#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BR_RECI 128
#define MAX_DUZINA_RECI 32

/* Funkcija koja izracunava broj suglasnika u reci */
int broj_suglasnika(char s[])
{
  char c;
  int i;
  int suglasnici = 0;
  /* Prolaz karakter po karakter kroz zadatu nisku */
  for (i = 0; s[i]; i++) {
    /* Ako je u pitanju slovo, konvertuje se u veliko da bi bio
       pokriven slucaj i malih i velikih suglasnika. */
    if (isalpha(s[i])) {
      c = toupper(s[i]);
      /* Ukoliko slovo nije samoglasnik uvecava se brojac. */
      if (c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U')
        suglasnici++;
    }
  }
  /* Vraca se izracunata vrednost */
  return suglasnici;
}

/* Funkcija koja sortira reci po zadatom kriterijumu. Informacija o
   duzini reci se mora proslediti zbog pravilnog upravljanja
   memorijom */
void sortiraj_reci(char reci[][MAX_DUZINA_RECI], int n)
{
  int min, i, j, broj_suglasnika_j, broj_suglasnika_min,
      duzina_j, duzina_min;
  char tmp[MAX_DUZINA_RECI];
  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i; j < n; j++) {
      /* Prvo se uporedjuje broj suglasnika */
      broj_suglasnika_j = broj_suglasnika(reci[j]);
      broj_suglasnika_min = broj_suglasnika(reci[min]);
      if (broj_suglasnika_j < broj_suglasnika_min)
        min = j;
      else if (broj_suglasnika_j == broj_suglasnika_min) {
        /* Zatim, recima koje imaju isti broj suglasnika uporedjuju
           se duzine */
        duzina_j = strlen(reci[j]);
        duzina_min = strlen(reci[min]);

        if (duzina_j < duzina_min)
          min = j;
        else {
          /* Ako reci imaju i isti broj suglasnika i iste duzine,
             uporedjuju se leksikografski */
          if (duzina_j == duzina_min
              && strcmp(reci[j], reci[min]) < 0)
            min = j;
        }
      }
    }
    if (min != i) {
      strcpy(tmp, reci[min]);
      strcpy(reci[min], reci[i]);
      strcpy(reci[i], tmp);
    }
  }
}

int main()
{
  FILE *ulaz;
  int i = 0, n;

  /* Niz u koji ce biti smestane reci. Prvi broj oznacava broj reci,
     a drugi maksimalnu duzinu pojedinacne reci */
  char reci[MAX_BR_RECI][MAX_DUZINA_RECI];

  /* Otvaranje datoteke niske.txt za citanje */
  ulaz = fopen("niske.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr,
            "Greska: Neuspesno otvaranje datoteke niske.txt!\n");
    exit(EXIT_FAILURE);
  }

  /* Sve dok se moze procitati sledeca rec */
  while (fscanf(ulaz, "%s", reci[i]) != EOF) {
    /* Proverava se da li ucitan maksimalan broj reci, i ako jeste,
       prekida se ucitavanje */
    if (i == MAX_BR_RECI)
      break;
    /* Priprema brojaca za narednu iteraciju */
    i++;
  }

  /* n je duzina niza reci i predstavlja poslednju vrednost
     koriscenog brojaca */
  n = i;
  /* Poziv funkcije za sortiranje reci */
  sortiraj_reci(reci, n);

  /* Ispis sortiranog niza reci */
  for (i = 0; i < n; i++) {
    printf("%s ", reci[i]);
  }
  printf("\n");

  /* Zatvaranje datoteke */
  fclose(ulaz);

  exit(EXIT_SUCCESS);
}
