#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENATA 128
#define MAX_DUZINA 16

/* O svakom studentu postoje 3 informacije i one su objedinjene u
   strukturi kojom se predstavlja svaki student. */
typedef struct {
  /* Indeks mora biti tipa long jer su podaci u datoteci preveliki za 
     int, npr. 20140123 */
  long indeks;
  char ime[MAX_DUZINA];
  char prezime[MAX_DUZINA];
} Student;

/* Ucitan niz studenata ce biti sortiran rastuce prema indeksu, jer
   su studenti u datoteci vec sortirani. Iz tog razloga pretraga po
   indeksu se vrsi binarno, dok pretraga po prezimenu mora linearno,
   jer nema garancije da postoji uredjenje po prezimenu. */

/* Funkcija trazi u sortiranom nizu studenata a[] duzine n studenta
   sa indeksom x i vraca indeks pozicije nadjenog clana niza ili -1,
   ako element nije pronadjen. */
int binarna_pretraga(Student a[], int n, long x)
{
  int levi = 0;
  int desni = n - 1;
  int srednji;
  /* Dokle god je indeks levi levo od indeksa desni */
  while (levi <= desni) {
    /* Racuna se srednja pozicija */
    srednji = (levi + desni) / 2;
    /* Ako je indeks stutenta na toj poziciji veci od trazenog, tada
       se trazeni indeks mora nalaziti u levoj polovini niza */
    if (x < a[srednji].indeks)
      desni = srednji - 1;
    /* Ako je pak manji od trazenog, tada se on mora nalaziti u
       desnoj polovini niza */
    else if (x > a[srednji].indeks)
      levi = srednji + 1;
    else
      /* Ako je jednak trazenom indeksu x, tada je pronadjen student
         sa trazenom indeksom na poziciji srednji */
      return srednji;
  }
  /* Ako nije pronadjen, vraca se -1 */
  return -1;
}

/* Linearnom pretragom niza studenata trazi se prezime x */
int linearna_pretraga(Student a[], int n, char x[])
{
  int i;
  for (i = 0; i < n; i++)
    /* Poredjenje prezimena i-tog studenta i poslatog x */
    if (strcmp(a[i].prezime, x) == 0)
      return i;
  return -1;
}

/* Main funkcija mora imati argumente jer se ime datoteke prosledjuje
   kao argument komandne linije */
int main(int argc, char *argv[])
{
  Student dosije[MAX_STUDENATA];
  FILE *fin = NULL;
  int i;
  int br_studenata = 0;
  long trazen_indeks = 0;
  char trazeno_prezime[MAX_DUZINA];

  /* Provera da li je korisnik prilikom poziva programa prosledio ime 
     datoteke sa informacijama o studentima */
  if (argc != 2) {
    fprintf(stderr,
            "Greska: Program se poziva sa %s ime_datoteke\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke */
  fin = fopen(argv[1], "r");
  if (fin == NULL) {
    fprintf(stderr,
            "Neuspesno otvaranje datoteke %s za citanje\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Citanje se vrsi sve dok postoji red sa informacijama o studentu */
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

  /* Nakon citanja, datoteka vise nije neophodna i zatvara se. */
  fclose(fin);

  /* Unos indeksa koji se binarno trazi u nizu */
  printf("Unesite indeks studenta cije informacije zelite: ");
  scanf("%ld", &trazen_indeks);
  i = binarna_pretraga(dosije, br_studenata, trazen_indeks);
  /* Rezultat binarne pretrage */
  if (i == -1)
    printf("Ne postoji student sa indeksom %ld\n", trazen_indeks);
  else
    printf("Indeks: %ld, Ime i prezime: %s %s\n",
           dosije[i].indeks, dosije[i].ime, dosije[i].prezime);

  /* Unos prezimena koje se linearno trazi u nizu */
  printf("Unesite prezime studenta cije informacije zelite: ");
  scanf("%s", trazeno_prezime);
  i = linearna_pretraga(dosije, br_studenata, trazeno_prezime);
  /* Rezultat linearne pretrage */
  if (i == -1)
    printf("Ne postoji student sa prezimenom %s\n", trazeno_prezime);
  else
    printf("Indeks: %ld, Ime i prezime: %s %s\n",
           dosije[i].indeks, dosije[i].ime, dosije[i].prezime);

  return 0;
}
