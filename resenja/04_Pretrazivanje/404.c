#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENATA 128
#define MAX_DUZINA 16

typedef struct {
  long indeks;
  char ime[MAX_DUZINA];
  char prezime[MAX_DUZINA];
} Student;

int binarna_pretraga_rekurzivna(Student a[], int levi, int desni,
                                long x)
{
  /* Ako je pozicija elementa na levom kraju veca od pozicije
     elementa na desnom kraju dela niza koji se pretrazuje, onda se
     zapravo pretrazuje prazan deo niza. U praznom delu niza nema
     trazenog elementa pa se vraca -1 */
  if (levi > desni)
    return -1;
  /* Racunanje pozicije srednjeg elementa */
  int srednji = (levi + desni) / 2;
  /* Da li je srednji bas onaj trazeni */
  if (a[srednji].indeks == x) {
    return srednji;
  }
  /* Ako je trazeni indeks manji od indeksa studenta na srednjoj
     poziciji, onda se pretraga nastavlja u levoj polovini niza, jer
     je poznato da je niz sortiran po indeksu u rastucem poretku. */
  if (x < a[srednji].indeks)
    return binarna_pretraga_rekurzivna(a, levi, srednji - 1, x);
  /* Inace ga treba traziti u desnoj polovini */
  else
    return binarna_pretraga_rekurzivna(a, srednji + 1, desni, x);
}

int linearna_pretraga_rekurzivna_v2(Student a[], int n, char x[])
{
  /* Ako je niz prazan, vraca se -1 */
  if (n == 0)
    return -1;
  /* Kako se trazi prvi student sa trazenim prezimenom, pocinje se sa 
     prvim studentom u nizu. */
  if (strcmp(a[0].prezime, x) == 0)
    return 0;
  int i = linearna_pretraga_rekurzivna_v2(a + 1, n - 1, x);
  return i >= 0 ? 1 + i : -1;
}

int linearna_pretraga_rekurzivna(Student a[], int n, char x[])
{
  /* Ako je niz prazan, vraca se -1 */
  if (n == 0)
    return -1;
  /* Ako se trazi poslednji student sa trazenim prezimenom, pocinje
     se sa poslednjim studentom u nizu. */
  if (strcmp(a[n - 1].prezime, x) == 0)
    return n - 1;
  return linearna_pretraga_rekurzivna(a, n - 1, x);
}

/* Main funkcija mora imati argumente jer se ime datoteke i opcija
   prosledjuju kao argumenti komandne linije */
int main(int argc, char *argv[])
{
  Student dosije[MAX_STUDENATA];
  FILE *fin = NULL;
  int i;
  int br_studenata = 0;
  long trazen_indeks = 0;
  char trazeno_prezime[MAX_DUZINA];
  int bin_pretraga;

  /* Provera da li je korisnik prilikom poziva programa prosledio ime 
     datoteke sa informacijama o studentima i opciju pretrage */
  if (argc != 3) {
    fprintf(stderr,
            "Greska: Program se poziva sa %s ime_datoteke opcija\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Provera prosledjene opcije */
  if (strcmp(argv[2], "-indeks") == 0)
    bin_pretraga = 1;
  else if (strcmp(argv[2], "-prezime") == 0)
    bin_pretraga = 0;
  else {
    fprintf(stderr, "Opcija mora biti -indeks ili -prezime\n");
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

  /* Pretraga po indeksu */
  if (bin_pretraga) {
    /* Unos indeksa koji se binarno trazi u nizu */
    printf("Unesite indeks studenta cije informacije zelite: ");
    scanf("%ld", &trazen_indeks);
    i = binarna_pretraga_rekurzivna(dosije, 0, br_studenata,
                                    trazen_indeks);
    /* Rezultat binarne pretrage */
    if (i == -1)
      printf("Ne postoji student sa indeksom %ld\n", trazen_indeks);
    else
      printf("Indeks: %ld, Ime i prezime: %s %s\n",
             dosije[i].indeks, dosije[i].ime, dosije[i].prezime);
  }
  /* Pretraga po prezimenu */
  else {
    /* Unos prezimena koje se linearno trazi u nizu */
    printf("Unesite prezime studenta cije informacije zelite: ");
    scanf("%s", trazeno_prezime);
    i = linearna_pretraga_rekurzivna_v2(dosije, br_studenata,
                                        trazeno_prezime);
    /* Rezultat linearne pretrage */
    if (i == -1)
      printf("Ne postoji student sa prezimenom %s\n",
             trazeno_prezime);
    else
      printf("Indeks: %ld, Ime i prezime: %s %s\n",
             dosije[i].indeks, dosije[i].ime, dosije[i].prezime);
  }
  exit(EXIT_SUCCESS);
}
