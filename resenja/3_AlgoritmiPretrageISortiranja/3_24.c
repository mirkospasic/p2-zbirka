#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KORAK 10

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
  Pesma *pesme;                 /* Pokazivac na deo memorije za
                                   cuvanje pesama */
  int alocirano_za_pesme;       /* Broj mesta alociranih za pesme */
  int i;                        /* Redni broj pesme cije se
                                   informacije citaju */
  int n;                        /* Ukupan broj pesama */
  int j, k;
  char c;
  int alocirano;                /* Broj mesta alociranih za propratne 
                                   informacije o pesmama */
  int broj_gledanja;

  /* Priprema datoteke za citanje */
  ulaz = fopen("pesme_bez_pretpostavki.txt", "r");
  if (ulaz == NULL) {
    printf("Greska pri otvaranju ulazne datoteke!\n");
    return 0;
  }

  /* Citanje informacija o pesmama */
  pesme = NULL;
  alocirano_za_pesme = 0;
  i = 0;

  while (1) {

    /* Proverava da li je dostignut kraj datoteke */
    c = fgetc(ulaz);
    if (c == EOF) {
      /* Nema vise sadrzaja za citanje */
      break;
    } else {
      /* Inace, vracamo procitani karakter nazad */
      ungetc(c, ulaz);
    }

    /* Provera da li postoji dovoljno memorije za citanje nove pesme */
    if (alocirano_za_pesme == i) {

      /* Ako ne, ako je potrosena sva alocirana memorija, alocira se
         novih KORAK mesta */
      alocirano_za_pesme += KORAK;
      pesme =
          (Pesma *) realloc(pesme,
                            alocirano_za_pesme * sizeof(Pesma));

      /* Proverava da li je nova memorija uspesno realocirana */
      if (pesme == NULL) {
        /* Ako nije ispisuje se obavestenje */
        printf("Problem sa alokacijom memorije!\n");
        /* I oslobadja sva memorija zauzeta do ovog koraka */
        for (k = 0; k < i; k++) {
          free(pesme[k].izvodjac);
          free(pesme[k].naslov);
        }
        free(pesme);
        return 0;
      }
    }

    /* Ako jeste, nastavlja se sa citanjem pesama ... */
    /* Cita se ime izvodjaca */
    j = 0;                      /* Pozicija na koju treba smestiti
                                   procitani karakter */
    alocirano = 0;              /* Broj alociranih mesta */
    pesme[i].izvodjac = NULL;   /* Memorija za smestanje procitanih
                                   karaktera */

    /* Sve do prve beline u liniji (beline koja se nalazi nakon imena 
       izvodjaca) citaju se karakteri iz datoteke */
    while ((c = fgetc(ulaz)) != ' ') {
      /* Proverav da li postoji dovoljno memorije za smestanje
         procitanog karaktera */
      if (j == alocirano) {

        /* Ako ne, ako je potrosena sva alocirana memorija, alocira
           se novih KORAK mesta */
        alocirano += KORAK;
        pesme[i].izvodjac =
            (char *) realloc(pesme[i].izvodjac,
                             alocirano * sizeof(char));

        /* Provera da li je nova alokacija uspesna */
        if (pesme[i].izvodjac == NULL) {
          /* Ako nije oslobadja se sva memorija zauzeta do ovog
             koraka */
          for (k = 0; k < i; k++) {
            free(pesme[k].izvodjac);
            free(pesme[k].naslov);
          }
          free(pesme);
          /* I prekida sa izvrsavanjem programa */
          return 0;
        }

      }
      /* Ako postoji dovoljno memorije, smestamo procitani karakter */
      pesme[i].izvodjac[j] = c;
      j++;
      /* I nastavlja se sa citanjem */
    }

    /* Upis terminirajuce nule na kraj reci */
    pesme[i].izvodjac[j] = '\0';

    /* Preskace se karakter - */
    fgetc(ulaz);

    /* Preskace se razmak */
    fgetc(ulaz);

    /* Cita se naslov pesme */
    j = 0;                      /* Pozicija na koju treba smestiti
                                   procitani karakter */
    alocirano = 0;              /* Broj alociranih mesta */
    pesme[i].naslov = NULL;     /* Memorija za smestanje procitanih
                                   karaktera */

    /* Sve do zareza (koji se nalazi nakon naslova pesme) citaju se
       karakteri iz datoteke */
    while ((c = fgetc(ulaz)) != ',') {
      /* Provera da li postoji dovoljno memorije za smestanje
         procitanog karaktera */
      if (j == alocirano) {
        /* Ako ne, ako je potrosena sva alocirana memorija, alocira
           se novih KORAK mesta */
        alocirano += KORAK;
        pesme[i].naslov =
            (char *) realloc(pesme[i].naslov,
                             alocirano * sizeof(char));

        /* Provera da li je nova alokacija uspesna */
        if (pesme[i].naslov == NULL) {
          /* Ako nije, oslobadja se sva memorija zauzeta do ovog
             koraka */
          for (k = 0; k < i; k++) {
            free(pesme[k].izvodjac);
            free(pesme[k].naslov);
          }
          free(pesme[i].izvodjac);
          free(pesme);

          /* I prekida izvrsavanje programa */
          return 0;
        }
      }
      /* Ako postoji dovoljno memorije, smesta se procitani karakter */
      pesme[i].naslov[j] = c;
      j++;
      /* I nastavlja dalje sa citanjem */
    }
    /* Upisuje se terminirajuca nula na kraj reci */
    pesme[i].naslov[j] = '\0';

    /* Preskace se razmak */
    fgetc(ulaz);

    /* Cita se broj gledanja */
    broj_gledanja = 0;

    /* Sve do znaka za novi red (kraja linije) citaju se karakteri iz 
       datoteke */
    while ((c = fgetc(ulaz)) != '\n') {
      broj_gledanja = broj_gledanja * 10 + (c - '0');
    }
    pesme[i].broj_gledanja = broj_gledanja;

    /* Prelazi se na citanje sledece pesme */
    i++;
  }

  /* Informacija o broju procitanih pesama */
  n = i;
  /* Zatvaranje nepotrebne datoteke */
  fclose(ulaz);

  /* Analiza argumenta komandne linije */
  if (argc == 1) {
    /* Nema dodatnih opcija => sortiranje po broju gledanja */
    qsort(pesme, n, sizeof(Pesma), &uporedi_gledanost);
  } else {
    if (argc == 2 && strcmp(argv[1], "-n") == 0) {
      /* Sortiranje po naslovu */
      qsort(pesme, n, sizeof(Pesma), &uporedi_naslove);
    } else {
      if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        /* Sortirnje po izvodjacu */
        qsort(pesme, n, sizeof(Pesma), &uporedi_izvodjace);
      } else {
        printf("Nedozvoljeni argumenti!\n");
        free(pesme);
        return 0;
      }
    }
  }

  /* Ispis rezultata */
  for (i = 0; i < n; i++) {
    printf("%s - %s, %d\n", pesme[i].izvodjac, pesme[i].naslov,
           pesme[i].broj_gledanja);
  }

  /* Oslobadjanje memorije */
  for (i = 0; i < n; i++) {
    free(pesme[i].izvodjac);
    free(pesme[i].naslov);
  }
  free(pesme);

  return 0;
}