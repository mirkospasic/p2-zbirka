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

/* Funkcija za uporedjivanje pesama po broju gledanosti
   (potrebna za rad qsort funkcije) */
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

/* Funkcija za uporedjivanje pesama po izvodjacu (potrebna za
   rad qsort funkcije) */
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
  int alocirano_za_pesme;       /* Broj mesta alociranih za
                                   pesme */
  int i;                        /* Redni broj pesme cije se
                                   informacije citaju */
  int n;                        /* Ukupan broj pesama */
  int j, k;
  char c;
  int alocirano;                /* Broj mesta alociranih za
                                   propratne informacije o
                                   pesmama */
  int broj_gledanja;

  /* Pripremamo datoteku za citanje */
  ulaz = fopen("pesme_bez_pretpostavki.txt", "r");
  if (ulaz == NULL) {
    printf("Greska pri otvaranju ulazne datoteke!\n");
    return 0;
  }

  /* Citamo informacije o pesmama */
  pesme = NULL;
  alocirano_za_pesme = 0;
  i = 0;

  while (1) {

    /* Proveravamo da li smo stigli do kraja datoteke */
    c = fgetc(ulaz);
    if (c == EOF) {
      /* Ako smo dobili kao rezultat EOF, jesmo, nema vise
         sadrzaja za citanje */
      break;
    } else {
      /* Ako nismo, vracamo procitani karakter nazad */
      ungetc(c, ulaz);
    }


    /* Proveravamo da li imamo dovoljno memorije za citanje nove 
       pesme */
    if (alocirano_za_pesme == i) {

      /* Ako nemamo, ako smo potrosili svu alociranu memoriju,
         alociramo novih KORAK mesta */
      alocirano_za_pesme += KORAK;
      pesme =
          (Pesma *) realloc(pesme,
                            alocirano_za_pesme * sizeof(Pesma));

      /* Proveravamo da li je nova memorija uspesno realocirana */
      if (pesme == NULL) {
        /* Ako nije ... */
        /* Ispisujemo obavestenje */
        printf("Problem sa alokacijom memorije!\n");

        /* I oslobadjamo svu memoriju zauzetu do ovog koraka */
        for (k = 0; k < i; k++) {
          free(pesme[k].izvodjac);
          free(pesme[k].naslov);
        }
        free(pesme);
        return 0;
      }

    }

    /* Ako jeste, nastavljamo sa citanjem pesama ... */
    /* Citamo ime izvodjaca */

    j = 0;                      /* Oznacava poziciju na koju
                                   treba smestiti procitani
                                   karakter */
    alocirano = 0;              /* Oznacava broj alociranih
                                   mesta */
    pesme[i].izvodjac = NULL;   /* Memorija koju mozemo
                                   koristiti za smestanje
                                   procitanih karaktera */

    /* Sve dok ne stignemo do prve beline u liniji - beline koja 
       se nalazi nakon imena izvodjaca - citamo karaktere iz
       datoteke */
    while ((c = fgetc(ulaz)) != ' ') {

      /* Proveravamo da li imamo dovoljno memorije za smestanje
         procitanog karaktera */
      if (j == alocirano) {

        /* Ako nemamo, ako smo potrosili svu alociranu memoriju, 
           alociramo novih KORAK mesta */
        alocirano += KORAK;
        pesme[i].izvodjac =
            (char *) realloc(pesme[i].izvodjac,
                             alocirano * sizeof(char));

        /* Proveravamo da li je nova alokacija uspesna */
        if (pesme[i].izvodjac == NULL) {
          /* Ako nije... */
          /* Oslobadjamo svu memoriju zauzetu do ovog koraka */
          for (k = 0; k < i; k++) {
            free(pesme[k].izvodjac);
            free(pesme[k].naslov);
          }
          free(pesme);
          /* I prekidamo sa izvrsavanjem programa */
          return 0;
        }

      }
      /* Ako imamo dovoljno memorije, smestamo procitani
         karakter */
      pesme[i].izvodjac[j] = c;
      j++;
      /* I nastavljamo sa citanjem */
    }

    /* Upisujemo terminirajucu nulu na kraju reci */
    pesme[i].izvodjac[j] = '\0';


    /* Citamo - */
    fgetc(ulaz);

    /* Citamo razmak */
    fgetc(ulaz);


    /* Citamo naslov pesme */
    j = 0;                      /* Oznacava poziciju na koju
                                   treba smestiti procitani
                                   karakter */
    alocirano = 0;              /* Oznacava broj alociranih
                                   mesta */
    pesme[i].naslov = NULL;     /* Memorija koju mozemo
                                   koristiti za smestanje
                                   procitanih karaktera */

    /* Sve dok ne stignemo do zareza - zareza koji se nalazi
       nakon naslova pesme - citamo karaktere iz datoteke */

    while ((c = fgetc(ulaz)) != ',') {
      /* Proveravamo da li imamo dovoljno memorije za smestanje
         procitanog karaktera */
      if (j == alocirano) {
        /* Ako nemamo, ako smo potrosili svu alociranu memoriju, 
           alociramo novih KORAK mesta */
        alocirano += KORAK;
        pesme[i].naslov =
            (char *) realloc(pesme[i].naslov,
                             alocirano * sizeof(char));

        /* Proveravamo da li je nova alokacija uspesna */
        if (pesme[i].naslov == NULL) {
          /* Ako nije... */
          /* Oslobadjamo svu memoriju zauzetu do ovog koraka */
          for (k = 0; k < i; k++) {
            free(pesme[k].izvodjac);
            free(pesme[k].naslov);
          }
          free(pesme[i].izvodjac);
          free(pesme);

          /* I prekidamo izvrsavanje programa */
          return 0;
        }

      }
      /* Ako imamo dovoljno memorije, smestamo procitani
         karakter */
      pesme[i].naslov[j] = c;
      j++;
      /* I nastavljamo dalje sa citanjem */
    }
    /* Upisujemo terminirajucu nulu na kraju reci */
    pesme[i].naslov[j] = '\0';

    /* Citamo razmak */
    fgetc(ulaz);


    /* Citamo broj gledanja */

    broj_gledanja = 0;

    /* Sve dok ne stignemo do znaka za novi red - kraja linije - 
       citamo karaktere iz datoteke */
    while ((c = fgetc(ulaz)) != '\n') {
      broj_gledanja = broj_gledanja * 10 + (c - '0');
    }
    pesme[i].broj_gledanja = broj_gledanja;

    /* Prelazimo na citanje sledece pesme */
    i++;

  }

  /* Cuvamo informaciju o broju pesama koje smo procitali */
  n = i;

  /* Zatvaramo datoteku jer nam nece vise trebati */
  fclose(ulaz);

  /* Analiziramo argumente komandne linije */
  if (argc == 1) {

    /* Nema dodatnih opcija - sortiramo po broju gledanja */
    qsort(pesme, n, sizeof(Pesma), &uporedi_gledanost);
  } else {

    if (argc == 2 && strcmp(argv[1], "-n") == 0) {
      /* Sortiramo po naslovu */
      qsort(pesme, n, sizeof(Pesma), &uporedi_naslove);
    } else {
      if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        /* Sortiramo po izvodjacu */
        qsort(pesme, n, sizeof(Pesma), &uporedi_izvodjace);
      } else {
        printf("Nedozvoljeni argumenti!\n");
        free(pesme);
        return 0;
      }
    }
  }

  /* Ispisujemo rezultat */
  for (i = 0; i < n; i++) {
    printf("%s - %s, %d\n", pesme[i].izvodjac, pesme[i].naslov,
           pesme[i].broj_gledanja);
  }

  /* Oslobadjamo memoriju */
  for (i = 0; i < n; i++) {
    free(pesme[i].izvodjac);
    free(pesme[i].naslov);
  }
  free(pesme);

  /* Prekidamo izvrsavanje programa */
  return 0;
}
