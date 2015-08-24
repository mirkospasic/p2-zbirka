#include <stdio.h>
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
  /* Obilazimo karakter po karakter zadate niske */
  for (i = 0; s[i]; i++) {
    /* Ako je u pitanju slovo */
    if (isalpha(s[i])) {
      /* Pretvaramo ga u veliko da bismo mogli da pokrijemo
         slucaj i malih i velikih suglasnika */
      c = toupper(s[i]);
      /* Ukoliko slovo nije samoglasnik */
      if (c != 'A' && c != 'E' && c != 'I' && c != 'O'
          && c != 'U') {
        /* Uvecavamo broj suglasnika */
        suglasnici++;
      }
    }
  }
  /* Vracamo izracunatu vrednost */
  return suglasnici;
}

/* Funkcija koja sortira reci po zadatom kriterijumu - OPREZ:
   informacija o duzini reci se mora proslediti zbog pravilnog
   upravljanja memorijom */
void sortiraj_reci(char reci[][MAX_DUZINA_RECI], int n)
{
  int min, i, j, broj_suglasnika_j, broj_suglasnika_min,
      duzina_j, duzina_min;
  char tmp[MAX_DUZINA_RECI];
  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i; j < n; j++) {
      /* Prvo uporedjujemo broj suglasnika */
      broj_suglasnika_j = broj_suglasnika(reci[j]);
      broj_suglasnika_min = broj_suglasnika(reci[min]);
      if (broj_suglasnika_j < broj_suglasnika_min)
        min = j;
      else if (broj_suglasnika_j == broj_suglasnika_min) {
        /* Zatim, reci imaju isti broj suglasnika uporedjujemo
           duzine */
        duzina_j = strlen(reci[j]);
        duzina_min = strlen(reci[min]);

        if (duzina_j < duzina_min)
          min = j;
        else
          /* A ako reci imaju i isti broj suglasnika i iste
             duzine, uporedjujemo ih leksikografski */
        if (duzina_j == duzina_min
              && strcmp(reci[j], reci[min]) < 0)
          min = j;
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

  /* Niz u kojem ce biti smestane reci. Prvi broj oznacava broj
     reci, a drugi maksimalnu duzinu pojedinacne reci */
  char reci[MAX_BR_RECI][MAX_DUZINA_RECI];

  /* Otvaramo datoteku niske.txt za citanje */
  ulaz = fopen("niske.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke niske.txt!\n");
    return 0;
  }

  /* Sve dok mozemo da procitamo sledecu rec */
  while (fscanf(ulaz, "%s", reci[i]) != EOF) {
    /* Proveravamo da li smo ucitali najvise dozvoljenih reci i
       ako jesmo, prekidamo ucitavanje */
    if (i == MAX_BR_RECI)
      break;
    /* Pripremamo brojac za narednu iteraciju */
    i++;
  }

  /* n je duzina naseg niza reci i predstavlja poslednju
     vrednost koriscenog brojaca */
  n = i;
  /* Pozivamo funkciju za sortiranje reci - OPREZ: nacin
     prosledjivanja niza reci */
  sortiraj_reci(reci, n);

  /* Ispisujemo sortirani niz reci */
  for (i = 0; i < n; i++) {
    printf("%s ", reci[i]);
  }
  printf("\n");

  /* Zatvaramo datoteku */
  fclose(ulaz);

  /* I zavrsavamo sa programom */
  return 0;
}
