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

/* Funkcija za uporedjivanje pesama po naslovu (potrebna za rad
   qsort funkcije) */
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

/* Funkcija koja oslobadja memoriju zauzetu dinamickim nizom pesme
   dimenzije n */
void oslobodi(Pesma * pesme, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    free(pesme[i].izvodjac);
    free(pesme[i].naslov);
  }
  free(pesme);
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
  int j;
  char c;
  int alocirano;                /* Broj mesta alociranih za
                                   propratne informacije o pesmama */
  int broj_gledanja;

  /* Priprema se datoteka za citanje */
  ulaz = fopen("pesme.txt", "r");
  if (ulaz == NULL) {
    fprintf(stderr,
            "Greska: Neuspesno otvaranje ulazne datoteke!\n");
    exit(EXIT_FAILURE);
  }

  /* Citaju se informacije o pesmama */
  pesme = NULL;
  alocirano_za_pesme = 0;
  i = 0;

  while (1) {
    /* Proverava se da li je dostignut kraj datoteke */
    c = fgetc(ulaz);
    if (c == EOF) {
      /* Nema vise sadrzaja za citanje */
      break;
    } else {
      /* Inace, vraca se procitani karakter nazad */
      ungetc(c, ulaz);
    }

    /* Proverava se da li postoji dovoljno vec alocirane memorije za
       citanje nove pesme */
    if (alocirano_za_pesme == i) {
      /* Ako ne, ako je potrosena sva alocirana memorija, alocira se
         novih KORAK mesta */
      alocirano_za_pesme += KORAK;
      pesme =
          (Pesma *) realloc(pesme,
                            alocirano_za_pesme * sizeof(Pesma));

      /* Proverava se da li je nova memorija uspesno realocirana */
      if (pesme == NULL) {
        /* Ako nije ispisuje se obavestenje */
        fprintf(stderr, "Greska: Problem sa alokacijom memorije!\n");
        /* I oslobadja sva memorija zauzeta do ovog koraka */
        oslobodi(pesme, i);
        exit(EXIT_FAILURE);
      }
    }

    /* Ako jeste, nastavlja se sa citanjem pesama ... */
    /* Cita se ime izvodjaca */
    j = 0;                      /* Pozicija na koju treba smestiti
                                   procitani karakter */
    alocirano = 0;              /* Broj alociranih mesta */
    pesme[i].izvodjac = NULL;   /* Memorija za smestanje procitanih
                                   karaktera */

    /* Sve do prve beline u liniji (beline koja se nalazi nakon
       imena izvodjaca) citaju se karakteri iz datoteke */
    while ((c = fgetc(ulaz)) != ' ') {
      /* Provera da li postoji dovoljno memorije za smestanje
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
          oslobodi(pesme, i);
          /* I prekida sa izvrsavanjem programa */
          exit(EXIT_FAILURE);
        }
      }
      /* Ako postoji dovoljno alocirane memorije, smesta se vec
         procitani karakter */
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
          free(pesme[i].izvodjac);
          oslobodi(pesme, i);
          /* I prekida izvrsavanje programa */
          exit(EXIT_FAILURE);
        }
      }
      /* Smesta se procitani karakter */
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

    /* Sve do znaka za novi red (kraja linije) citaju se karakteri
       iz datoteke */
    while ((c = fgetc(ulaz)) != '\n') {
      broj_gledanja = broj_gledanja * 10 + (c - '0');
    }
    pesme[i].broj_gledanja = broj_gledanja;

    /* Prelazi se na citanje sledece pesme */
    i++;
  }

  /* Informacija o broju procitanih pesama */
  n = i;
  /* Zatvara se datoteka */
  fclose(ulaz);

  /* Analiza argumenta komandne linije */
  if (argc == 1) {
    /* Nema dodatnih opcija => sortiranje po broju gledanja */
    qsort(pesme, n, sizeof(Pesma), &uporedi_gledanost);
  } else {
    if (argc == 2 && strcmp(argv[1], "-n") == 0) {
      /* Sortira se po naslovu */
      qsort(pesme, n, sizeof(Pesma), &uporedi_naslove);
    } else {
      if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        /* Sortira se po izvodjacu */
        qsort(pesme, n, sizeof(Pesma), &uporedi_izvodjace);
      } else {
        fprintf(stderr, "Greska: Nedozvoljeni argumenti!\n");
        free(pesme);
        exit(EXIT_FAILURE);
      }
    }
  }

  /* Ispis rezultata */
  for (i = 0; i < n; i++) {
    printf("%s - %s, %d\n", pesme[i].izvodjac, pesme[i].naslov,
           pesme[i].broj_gledanja);
  }

  /* Oslobadja se memorija */
  oslobodi(pesme, n);

  exit(EXIT_SUCCESS);
}
