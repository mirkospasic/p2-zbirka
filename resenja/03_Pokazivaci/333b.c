#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struktura koja opisuje jednu pesmu */
typedef struct {
  char *izvodjac;
  char *naslov;
  int broj_gledanja;
} Pesma;

/* Funkcija za uporedjivanje pesama po broju gledanosti (potrebna za
   rad qsort funkcije) */
int uporedi_gledanost(const void *pp1, const void *pp2)
{
  Pesma *p1 = (Pesma *) pp1;
  Pesma *p2 = (Pesma *) pp2;

  return p2->broj_gledanja - p1->broj_gledanja;
}

/* Funkcija za uporedjivanje pesama po naslovu (potrebna za rad qsort 
   funkcije) */
int uporedi_naslove(const void *pp1, const void *pp2)
{
  Pesma *p1 = (Pesma *) pp1;
  Pesma *p2 = (Pesma *) pp2;

  return strcmp(p1->naslov, p2->naslov);
}

/* Funkcija za uporedjivanje pesama po izvodjacu (potrebna za rad
   qsort funkcije) */
int uporedi_izvodjace(const void *pp1, const void *pp2)
{
  Pesma *p1 = (Pesma *) pp1;
  Pesma *p2 = (Pesma *) pp2;

  return strcmp(p1->izvodjac, p2->izvodjac);
}

int main(int argc, char *argv[])
{
  FILE *ulaz;
  Pesma *pesme;
  int i, j, n, alocirano, k;
  int KORAK = 10;
  int c;
  int duzina_naslova;

  /* Pripremamo datoteku za citanje */
  ulaz = fopen("pesme.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke.\n");
    return 0;
  }

  /* citamo informaciju o broju pesama */
  fscanf(ulaz, "%d", &n);

  /* Ucitavamo znak za novi red nakon broja pesama */
  fgetc(ulaz);

  /* Alociramo memoriju za niz pesama */
  pesme = (Pesma *) malloc(n * sizeof(Pesma));
  if (pesme == NULL) {
    fprintf(stderr, "malloc(): Neuspela alokacija\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo informacije o pesmama bez pravljenja pretpostavki o
     maksimalnoj duzini imena izvodjaca i naslova pesme */
  for (i = 0; i < n; i++) {
    /* citamo ime izvodjaca */
    j = 0;
    alocirano = 0;
    pesme[i].izvodjac = NULL;

    /* Sve dok ne stignemo do prve beline u liniji - beline koja se
       nalazi nakon imena izvodjaca, citamo karaktere iz datoteke */
    while ((c = fgetc(ulaz)) != ' ') {
      /* Proveravamo da li imamo dovoljno memorije za smestanje
         procitanog karaktera */
      if (j == alocirano) {
        /* Ako nemamo, alociramo novih KORAK mesta */
        alocirano += KORAK;
        pesme[i].izvodjac = (char *) realloc(pesme[i].izvodjac,
                                             alocirano *
                                             sizeof(char));

        /* Proveravamo da li je nova alokacija uspesna */
        if (pesme[i].izvodjac == NULL) {
          /* Ako nije, ispisujemo poruku o gresci i oslobadjamo svu
             memoriju zauzetu do ovog koraka */
          fprintf(stderr, "realloc(): neuspesna alokacija!\n");
          for (k = 0; k < i; k++) {
            free(pesme[k].izvodjac);
            free(pesme[k].naslov);
          }
          free(pesme);
          /* Prekidamo izvrsavanje programa */
          exit(EXIT_FAILURE);
        }
      }

      /* Ako imamo dovoljno memorije, dodajemo procitani karakter u
         ime izvodjaca */
      pesme[i].izvodjac[j] = c;
      j++;
      /* i nastavljamo dalje sa citanjem */
    }

    /* Upisujemo terminalnu nulu na kraj reci */
    pesme[i].izvodjac[j] = '\0';

    /* citamo karakter '-' */
    fgetc(ulaz);

    /* citamo razmak */
    fgetc(ulaz);

    /* citamo naslov pesme */
    j = 0;
    alocirano = 0;
    pesme[i].naslov = NULL;

    /* Sve dok ne stignemo do zareza koji se nalazi nakon naslova
       pesme citamo karaktere iz datoteke */
    while ((c = fgetc(ulaz)) != ',') {
      /* Proveravamo da li imamo dovoljno memorije za smestanje
         procitanog karaktera */
      if (j == alocirano) {
        /* Ako nemamo, alociramo novih KORAK mesta */
        alocirano += KORAK;
        pesme[i].naslov = (char *) realloc(pesme[i].naslov,
                                           alocirano * sizeof(char));

        /* Proveravamo da li je nova alokacija uspesna */
        if (pesme[i].naslov == NULL) {
          /* Ako nije, ispisujemo poruku o gresci i oslobadjamo svu
             memoriju zauzetu do ovog koraka */
          fprintf(stderr, "realloc(): neuspesna alokacija!\n");
          for (k = 0; k < i; k++) {
            free(pesme[k].izvodjac);
            free(pesme[k].naslov);
          }
          free(pesme[i].izvodjac);
          free(pesme);

          /* Prekidamo izvrsavanje programa */
          exit(EXIT_FAILURE);
        }
      }
      /* Ako imamo dovoljno memorije, dodajemo procitani karakter u
         tekuci naslov pesme */
      pesme[i].naslov[j] = c;
      j++;
      /* i nastavljamo dalje sa citanjem */
    }
    pesme[i].naslov[j] = '\0';

    /* citamo broj gledanja */
    fscanf(ulaz, "%d", &pesme[i].broj_gledanja);

    /* citamo znak za prelazak u novi red */
    fgetc(ulaz);
  }

  /* Zatvaramo datoteku jer nam vise nece trebati */
  fclose(ulaz);

  /* Analiziramo argumente komandne linije */
  if (argc == 1)
    /* Nema dodatnih opcija - sortiramo po broju gledanja */
    qsort(pesme, n, sizeof(Pesma), uporedi_gledanost);
  else if (argc == 2 && strcmp(argv[1], "-n") == 0)
    /* sortiramo po naslovu */
    qsort(pesme, n, sizeof(Pesma), uporedi_naslove);
  else if (argc == 2 && strcmp(argv[1], "-i") == 0)
    /* sortiramo po izvodjacu */
    qsort(pesme, n, sizeof(Pesma), uporedi_izvodjace);
  else {
    fprintf(stderr, "Nedozvoljeni argument komandne linije!\n");
    free(pesme);
    exit(EXIT_FAILURE);
  }

  /* Ispisujemo rezultat */
  for (i = 0; i < n; i++)
    printf("%s - %s, %d\n", pesme[i].izvodjac, pesme[i].naslov,
           pesme[i].broj_gledanja);

  /* Oslobadjamo memoriju */
  free(pesme);

  /* Prekidamo izvrsavanje programa */
  return 0;
}
