#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_DUZINA 20

typedef struct _Cvor {
  unsigned broj_pojavljivanja;
  char etiketa[20];
  struct _Cvor *sledeci;
} Cvor;

/* Pomocna funkcija koja kreira cvor. Vraca pokazivac na novi cvor
   ili NULL ako alokacija nije uspesno izvrsena. */
Cvor *napravi_cvor(unsigned br, char *etiketa)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->broj_pojavljivanja = br;
  strcpy(novi->etiketa, etiketa);
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove liste. */
void oslobodi_listu(Cvor ** adresa_glave)
{
  Cvor *pomocni = NULL;

  while (*adresa_glave != NULL) {
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }
}

/* Funkcija dodaje novi cvor na pocetak liste. Vraca 1 ako je doslo
   do greske pri alokaciji memorije za nov cvor, inace vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, unsigned br,
                           char *etiketa)
{
  Cvor *novi = napravi_cvor(br, etiketa);
  if (novi == NULL)
    return 1;

  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;
  return 0;
}

/* Funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu ili
   NULL ako takav cvor ne postoji. */
Cvor *pretrazi_listu(Cvor * glava, char etiketa[])
{
  Cvor *tekuci;
  for (tekuci = glava; tekuci != NULL; tekuci = tekuci->sledeci)
    if (strcmp(tekuci->etiketa, etiketa) == 0)
      return tekuci;
  return NULL;
}

/* Funkcija ispisuje sadrzaj liste */
void ispisi_listu(Cvor * glava)
{
  for (; glava != NULL; glava = glava->sledeci)
    printf("%s - %u\n", glava->etiketa, glava->broj_pojavljivanja);
}

/* Glavni program */
int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr,
            "Greska! Program se poziva sa: ./a.out datoteka.html!\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaramo datoteku za citanje */
  FILE *in = NULL;
  in = fopen(argv[1], "r");
  if (in == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke %s!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char c;
  int i = 0;
  char procitana[MAX_DUZINA];
  Cvor *glava = NULL;
  Cvor *trazeni = NULL;

  while ((c = fgetc(in)) != EOF) {

    if (c == '<') {
      /* Cita se zatvorena etiketa. */
      if ((c = fgetc(in)) == '/') {
        i = 0;
        while ((c = fgetc(in)) != '>')
          procitana[i++] = c;
      }
      /* Cita se otvorena etiketa. */
      else {
        i = 0;
        procitana[i++] = c;
        while ((c = fgetc(in)) != ' ' && c != '>')
          procitana[i++] = c;
      }
      procitana[i] = '\0';

      /* Trazi se ucitana etiketa medju postojecim cvorovima liste.
         Ukoliko ne postoji, dodaje se novi cvor za ucitanu etiketu
         sa brojem pojavljivanja 1, inace uvecava se broj
         pojavljivanja etikete. */
      trazeni = pretrazi_listu(glava, procitana);
      if (trazeni == NULL) {
        if (dodaj_na_pocetak_liste(&glava, 1, procitana) == 1) {
          fprintf(stderr, "Neuspela alokacija za nov cvor\n");
          oslobodi_listu(&glava);
          exit(EXIT_FAILURE);
        }
      } else
        trazeni->broj_pojavljivanja++;
    }
  }

  fclose(in);

  ispisi_listu(glava);
  oslobodi_listu(&glava);

  return 0;
}
