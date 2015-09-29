#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;
  /* Inicijalizacija polja novog cvora */
  strcpy(novi->broj_indeksa, broj_indeksa);
  strcpy(novi->ime, ime);
  strcpy(novi->prezime, prezime);
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja memoriju zauzetu za elemente liste. */
void oslobodi_listu(Cvor ** adresa_glave)
{
  if (*adresa_glave == NULL)
    return;
  /* Rep liste se oslobadja rekurzivnim pozivom. */
  oslobodi_listu(&(*adresa_glave)->sledeci);
  /* Potom se oslobadja i glava liste. */
  free(*adresa_glave);
  *adresa_glave = NULL;
}

/* Funkcija proverava da li je novi NULL pokazivac, i ukoliko jeste
   oslobadja celu listu cija se glava nalazi na adresi adresa_glave i 
   prekida program. */
void proveri_alokaciju(Cvor ** adresa_glave, Cvor * novi)
{
  if (novi == NULL) {
    fprintf(stderr, "Neuspela alokacija za nov cvor\n");
    oslobodi_listu(adresa_glave);
    exit(EXIT_FAILURE);
  }
}

/* Funkcija dodaje novi cvor na pocetak liste. */
void dodaj_na_pocetak_liste(Cvor ** adresa_glave, char *broj_indeksa,
                            char *ime, char *prezime)
{
  Cvor *novi = napravi_cvor(broj_indeksa, ime, prezime);
  proveri_alokaciju(adresa_glave, novi);
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;
}

/* Funkcija ispisuje sadrzaj cvorova liste. */
void ispisi_listu(Cvor * glava)
{
  for (; glava != NULL; glava = glava->sledeci)
    printf("%s %s %s\n", glava->broj_indeksa, glava->ime,
           glava->prezime);
}

/* Funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu, u
   suprotnom vraca NULL. */
Cvor *pretrazi_listu(Cvor * glava, char *broj_indeksa)
{
  if (glava == NULL)
    return NULL;
  if (!strcmp(glava->broj_indeksa, broj_indeksa))
    return glava;
  return pretrazi_listu(glava->sledeci, broj_indeksa);
}

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
    dodaj_na_pocetak_liste(&glava, broj_indeksa, ime, prezime);

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
