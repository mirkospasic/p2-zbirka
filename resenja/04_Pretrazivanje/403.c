#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENATA 128
#define MAX_DUZINA 16

/* O svakom studentu imamo 3 informacije i njih objedinjujemo u
   strukturu kojom cemo predstavljati svakog studenta. */
typedef struct {
  /* Indeks mora biti tipa long jer su podaci u datoteci
     preveliki za int, npr. 20140123 */
  long indeks;
  char ime[MAX_DUZINA];
  char prezime[MAX_DUZINA];
} Student;

/* Ucitan niz studenata ce biti sortiran prema indeksu, jer cemo 
   ih, redom, kako citamo smestati u niz, a u datoteci su vec
   smesteni sortirani rastuce prema broju indeksa. Iz tog
   razloga pretragu po indeksu cemo vrsiti binarnom pretragom,
   dok pretragu po prezimenu moramo vrsiti linearno, jer nemamo
   garancije da postoji uredjenje po prezimenu. */

/* Funkcija trazi u sortiranom nizu a[] duzine n broj x. Vraca
   indeks pozicije nadjenog elementa ili -1, ako element nije
   pronadjen */
int binarna_pretraga(Student a[], int n, long x)
{
  int levi = 0;
  int desni = n - 1;
  int srednji;
  /* Dokle god je indeks levi levo od indeksa desni */
  while (levi <= desni) {
    /* Racunamo srednji indeks */
    srednji = (levi + desni) / 2;
    /* Ako je srednji element veci od x, tada se x mora nalaziti 
       u levoj polovini niza */
    if (x < a[srednji].indeks)
      desni = srednji - 1;
    /* Ako je srednji element manji od x, tada se x mora
       nalaziti u desnoj polovini niza */
    else if (x > a[srednji].indeks)
      levi = srednji + 1;
    else
      /* Ako je srednji element jednak x, tada smo pronasli x na 
         poziciji srednji */
      return srednji;
  }
  /* Ako nije pronadjen vracamo -1 */
  return -1;
}

int linearna_pretraga(Student a[], int n, char x[])
{
  int i;
  for (i = 0; i < n; i++)
    /* Poredimo prezime i-tog studenta i poslato x */
    if (strcmp(a[i].prezime, x) == 0)
      return i;
  return -1;
}

/* Main funkcija mora imate argumente jer se ime datoteke dobija 
   kao argument komandne linije */
int main(int argc, char *argv[])
{
  /* Ucitacemo redom sve studente iz datoteke u niz. */
  Student dosije[MAX_STUDENATA];
  FILE *fin = NULL;
  int i;
  int br_studenata = 0;
  long trazen_indeks = 0;
  char trazeno_prezime[MAX_DUZINA];

  /* Proveravamo da li nam je korisnik prilikom poziva prosledio 
     ime_datoteke sa informacijama o studentima */
  if (argc != 2) {
    fprintf(stderr,
            "Greska: Program se poziva sa %s ime_datoteke\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaramo datoteku */
  fin = fopen(argv[1], "r");
  if (fin == NULL) {
    fprintf(stderr,
            "Neuspesno otvaranje datoteke %s za citanje\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Citamo sve dok imamo red sa informacijama o studentu */
  i = 0;
  while (1) {
    if (i == MAX_STUDENATA)
      break;
    if (fscanf
        (fin, "%ld %s %s", &dosije[i].indeks, dosije[i].ime,
         dosije[i].prezime) != 3)
      break;
    i++;
  }
  br_studenata = i;

  /* Nakon citanja datoteka nam vise nije neophodna i odmah je
     zatvaramo */
  fclose(fin);

  printf("Unesite indeks studenta cije informacije zelite: ");
  scanf("%ld", &trazen_indeks);
  i = binarna_pretraga(dosije, br_studenata, trazen_indeks);
  if (i == -1)
    printf("Ne postoji student sa indeksom %ld\n",
           trazen_indeks);
  else
    printf("Indeks: %ld, Ime i prezime: %s %s\n",
           dosije[i].indeks, dosije[i].ime, dosije[i].prezime);

  printf("Unesite prezime studenta cije informacije zelite: ");
  scanf("%s", trazeno_prezime);
  i = linearna_pretraga(dosije, br_studenata, trazeno_prezime);
  if (i == -1)
    printf("Ne postoji student sa prezimenom %s\n",
           trazeno_prezime);
  else
    printf("Indeks: %ld, Ime i prezime: %s %s\n",
           dosije[i].indeks, dosije[i].ime, dosije[i].prezime);

  return 0;
}
