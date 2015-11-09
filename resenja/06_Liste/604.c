#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INDEKS 11
#define MAX_IME_PREZIME 21

/* Struktura kojom se predstavlja cvor liste koji sadrzi podatke o
   studentu. */
typedef struct _Cvor {
  char broj_indeksa[MAX_INDEKS];
  char ime[MAX_IME_PREZIME];
  char prezime[MAX_IME_PREZIME];
  struct _Cvor *sledeci;
} Cvor;

/* Funkcija kreira, inicijalizuje cvor liste i vraca pokazivac na nov 
   cvor ili NULL ukoliko alokacija nije prosla. */
Cvor *napravi_cvor(char *broj_indeksa, char *ime, char *prezime)
{
  /* Alocira se memorija za novi cvor liste i proverava uspesnost
     alokacije */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja strukture */
  strcpy(novi->broj_indeksa, broj_indeksa);
  strcpy(novi->ime, ime);
  strcpy(novi->prezime, prezime);
  novi->sledeci = NULL;

  return novi;
}

/* Funkcija oslobadja memoriju zauzetu za cvorove liste. */
void oslobodi_listu(Cvor ** adresa_glave)
{
  /* Ako je lista prazna, nema zauzete memorije. */
  if (*adresa_glave == NULL)
    return;

  /* Rep liste se oslobadja rekurzivnim pozivom. */
  oslobodi_listu(&(*adresa_glave)->sledeci);

  /* Potom se oslobadja i glava liste. */
  free(*adresa_glave);
  *adresa_glave = NULL;
}

/* Funkcija dodaje novi cvor na pocetak liste. Vraca 1 ako je doslo
   do greske pri alokaciji memorije za nov cvor, inace vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, char *broj_indeksa,
                           char *ime, char *prezime)
{
  /* Kreira se nov cvor i proverava se da li je bilo greske pri
     alokaciji. */
  Cvor *novi = napravi_cvor(broj_indeksa, ime, prezime);
  if (novi == NULL)
    return 1;

  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;

  return 0;
}

/* Funkcija ispisuje sadrzaj cvorova liste. */
void ispisi_listu(Cvor * glava)
{
  /* Pocevsi od glave liste */
  for (; glava != NULL; glava = glava->sledeci)
    printf("%s %s %s\n", glava->broj_indeksa, glava->ime,
           glava->prezime);
}

/* Funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu, u
   suprotnom vraca NULL. */
Cvor *pretrazi_listu(Cvor * glava, char *broj_indeksa)
{
  /* Ako je lista prazna, ne postoji trazeni cvor. */
  if (glava == NULL)
    return NULL;

  /* Poredi se trazeni sa brojem indeksa u cvoru koji je glava liste */
  if (!strcmp(glava->broj_indeksa, broj_indeksa))
    return glava;

  /* Ukoliko u cvoru glava nije trazeni indeks, pretraga se nastavlja 
     u repu liste. */
  return pretrazi_listu(glava->sledeci, broj_indeksa);
}

/* Glavni program */
int main(int argc, char **argv)
{
  /* Argumenti komandne linije su neophodni jer se iz komandne linije 
     dobija ime datoteke sa informacijama o studentima. */
  if (argc != 2) {
    fprintf(stderr,
            "Greska! Program se poziva sa: ./a.out ime_datoteke\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke za citanje */
  FILE *in = NULL;
  in = fopen(argv[1], "r");
  if (in == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Pomocne promenljive za citanje vrednosti koje treba smestiti u
     listu */
  char ime[MAX_IME_PREZIME], prezime[MAX_IME_PREZIME];
  char broj_indeksa[MAX_INDEKS];
  Cvor *glava = NULL;
  Cvor *trazeni = NULL;

  /* Ucitavanje vrednosti u listu */
  while (fscanf(in, "%s %s %s", broj_indeksa, ime, prezime) != EOF)
    if (dodaj_na_pocetak_liste(&glava, broj_indeksa, ime, prezime)) {
      fprintf(stderr, "Neuspela alokacija za nov cvor\n");
      oslobodi_listu(&glava);
      exit(EXIT_FAILURE);
    }

  /* Datoteka vise nije potrebna i zatvara se. */
  fclose(in);

  /* Ucitava se indeks po indeks studenta koji se trazi u listi. */
  while (scanf("%s", broj_indeksa) != EOF) {
    trazeni = pretrazi_listu(glava, broj_indeksa);
    if (trazeni == NULL)
      printf("ne\n");
    else
      printf("da: %s %s\n", trazeni->ime, trazeni->prezime);
  }

  /* Oslobadja se memorija zauzeta za cvorove liste. */
  oslobodi_listu(&glava);

  return 0;
}
