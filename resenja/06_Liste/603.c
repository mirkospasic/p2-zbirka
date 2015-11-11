#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DUZINA 20

/* Struktura kojom je predstavljen cvor liste sadrzi naziv etikete,
   broj pojavljivanja etikete i pokazivac na sledeci cvor liste */
typedef struct _Cvor {
  char etiketa[20];
  unsigned broj_pojavljivanja;
  struct _Cvor *sledeci;
} Cvor;

/* Pomocna funkcija koja kreira cvor. Vraca pokazivac na novi cvor
   ili NULL ako alokacija nije uspesno izvrsena */
Cvor *napravi_cvor(unsigned br, char *etiketa)
{
  /* Alocira se memorija za novi cvor liste i proverava se uspesnost
     alokacije */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja strukture */
  novi->broj_pojavljivanja = br;
  strcpy(novi->etiketa, etiketa);
  novi->sledeci = NULL;

  /* Vraca se adresa novog cvora */
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu cvorovima liste */
void oslobodi_listu(Cvor ** adresa_glave)
{
  Cvor *pomocni = NULL;

  /* Sve dok lista ni bude prazna, brise se tekuca glava liste i
     azurira se vrednost glave liste */
  while (*adresa_glave != NULL) {
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }
  /* Nakon izlaska iz petlje pokazivac glava u main funkciji koji se
     nalazi na adresi adresa_glave bice postavljen na NULL vrednost. */
}

/* Funkcija dodaje novi cvor na pocetak liste. Povratna vrednost je 1 
   ako je doslo do greske pri alokaciji memorije za nov cvor, odnosno 
   0 */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, unsigned br,
                           char *etiketa)
{
  /* Kreira se novi cvor i proverava se uspesnost alokacije */
  Cvor *novi = napravi_cvor(br, etiketa);
  if (novi == NULL)
    return 1;

  /* Dodaje se novi cvor na pocetak liste */
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;

  /* Vraca se indikator uspesnog dodavanja */
  return 0;
}

/* Funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu ili
   NULL ako takav cvor ne postoji u listi */
Cvor *pretrazi_listu(Cvor * glava, char etiketa[])
{
  Cvor *tekuci;

  /* Obilazi se cvor po cvor liste */
  for (tekuci = glava; tekuci != NULL; tekuci = tekuci->sledeci)
    /* Ako tekuci cvor sadrzi trazenu etiketu, vracamo njegovu
       vrednost */
    if (strcmp(tekuci->etiketa, etiketa) == 0)
      return tekuci;

  /* Cvor nije pronadjen */
  return NULL;
}

/* Funkcija ispisuje sadrzaj liste */
void ispisi_listu(Cvor * glava)
{
  /* Pocevsi od cvora koji je glava lista, ispisuju se sve etikete i
     broj njihovog pojavljivanja u HTML datoteci. */
  for (; glava != NULL; glava = glava->sledeci)
    printf("%s - %u\n", glava->etiketa, glava->broj_pojavljivanja);
}

int main(int argc, char **argv)
{
  /* Provera se da li je program pozvan sa ispravnim brojem
     argumenata. */
  if (argc != 2) {
    fprintf(stderr,
            "Greska! Program se poziva sa: ./a.out datoteka.html!\n");
    exit(EXIT_FAILURE);
  }

  /* Priprema datoteke za citanje */
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

  /* Cita se karakter po karakter datoteke sve dok se ne procita cela 
     datoteka */
  while ((c = fgetc(in)) != EOF) {

    /* Proverava se da li se pocinje sa citanjem nove etikete */
    if (c == '<') {
      /* Proverava se da li se cita zatvarajuca etiketa */
      if ((c = fgetc(in)) == '/') {
        i = 0;
        while ((c = fgetc(in)) != '>')
          procitana[i++] = c;
      }
      /* Cita se otvarajuca etiketa */
      else {
        i = 0;
        procitana[i++] = c;
        while ((c = fgetc(in)) != ' ' && c != '>')
          procitana[i++] = c;
      }
      procitana[i] = '\0';

      /* Trazi se procitana etiketa medju postojecim cvorovima liste.
         Ukoliko ne postoji, dodaje se novi cvor za ucitanu etiketu sa 
         brojem pojavljivanja 1. Inace se uvecava broj pojavljivanja
         etikete */
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

  /* Zatvaranje datoteke */
  fclose(in);

  /* Ispisuje se sadrzaj cvorova liste */
  ispisi_listu(glava);

  /* Oslobadja se memorija zauzeta listom */
  oslobodi_listu(&glava);

  return 0;
}
