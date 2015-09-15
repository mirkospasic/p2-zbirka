#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_DUZINA 20

typedef struct _Element {
  unsigned broj_pojavljivanja;
  char etiketa[20];
  struct _Element *sledeci;
} Element;

/* Pomocna funkcija koja kreira cvor. Vraca pokazivac na novi
   cvor ili NULL ako alokacija nije uspesno izvrsena. */
Element *napravi_cvor(unsigned br, char *etiketa)
{
  Element *novi = (Element *) malloc(sizeof(Element));
  if (novi == NULL)
    return NULL;

  novi->broj_pojavljivanja = br;
  strcpy(novi->etiketa, etiketa);
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente
   liste. */
void oslobodi_listu(Element ** glava)
{
  Element *pomocni = NULL;

  while (*glava != NULL) {
    pomocni = (*glava)->sledeci;
    free(*glava);
    *glava = pomocni;
  }
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi
   i ukoliko alokacija nije bila uspesna, oslobadja se sva
   prethodno zauzeta memorija za listu cija pocetni cvor se
   nalazi na adresi glava. */
void provera_alokacije(Element * novi, Element ** glava)
{
  if (novi == NULL) {
    fprintf(stderr, "malloc() greska u funkciji 
napravi_cvor()!\n");
    oslobodi_listu(glava);
    exit(EXIT_FAILURE);
  }
}

/* Funkcija dodaje novi cvor na pocetak liste. */
void dodaj_na_pocetak_liste(Element ** glava, unsigned br,
                            char *etiketa)
{
  Element *novi = napravi_cvor(br, etiketa);
  provera_alokacije(novi, glava);
  novi->sledeci = *glava;
  *glava = novi;
}

/* Funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu.
   (NULL u suprotnom) */
Element *pretrazi_listu(Element * glava, char etiketa[])
{
  Element *tekuci;
  for (tekuci = glava; tekuci != NULL; tekuci = tekuci->sledeci)
    if (strcmp(tekuci->etiketa, etiketa) == 0)
      return tekuci;
  return NULL;
}

/* Funkcija ispisuje sadrzaj liste */
void ispisi_listu(Element * glava)
{
  for (; glava != NULL; glava = glava->sledeci)
    printf("%s - %u\n", glava->etiketa,
           glava->broj_pojavljivanja);
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Greska! Program se poziva sa: ./a.out 
datoteka.html!\n");
    exit(EXIT_FAILURE);
  }

  FILE *in = NULL;
  in = fopen(argv[1], "r");
  if (in == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke %s!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char c;
  int i = 0;
  char a[MAX_DUZINA];

  Element *glava = NULL;
  Element *trazeni = NULL;

  while ((c = fgetc(in)) != EOF) {

    if (c == '<') {
      /* Citamo zatvarac */
      if ((c = fgetc(in)) == '/') {
        i = 0;
        while ((c = fgetc(in)) != '>')
          a[i++] = c;
      }

      /* Citamo otvarac */
      else {
        i = 0;
        a[i++] = c;
        while ((c = fgetc(in)) != ' ' && c != '>')
          a[i++] = c;
      }
      a[i] = '\0';

      /* Ispitujemo da li medju do sada formiranim cvorovima
         postoji cvor sa ucitanom etiketom. Ukoliko ne postoji,
         dodajemo novi cvor za ucitanu etiketu (broj
         pojavljivanja postavljamo na 1), inace uvecavamo broj
         pojavljivanja. */
      trazeni = pretrazi_listu(glava, a);
      if (trazeni == NULL)
        dodaj_na_pocetak_liste(&glava, 1, a);
      else
        trazeni->broj_pojavljivanja++;
    }
  }

  ispisi_listu(glava);
  oslobodi_listu(&glava);

  fclose(in);
  return 0;
}
