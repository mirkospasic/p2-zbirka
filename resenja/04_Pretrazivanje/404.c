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
  /* Ako je indeks elementa na levom kraju veci od indeksa
     elementa na desnom kraju dela niza koji se pretrazuje, onda 
     zapravo pretrazujemo prazan deo niza. U praznom nizu nema
     elementa koji trazimo i zato vracamo -1 */
  if (levi > desni)
    return -1;
  /* Racunamo indeks srednjeg elementa */
  int srednji = (levi + desni) / 2;
  /* Da li je srednji, bas onaj kog trazimo? */
  if (a[srednji].indeks == x) {
    return srednji;
  }
  /* Ako je trazeni indeks manji od indeksa srednjeg, onda
     potragu nastavljamo u levoj polovini niza jer znamo da je
     niz sortiran po indeksu u rastucem poretku. */
  if (x < a[srednji].indeks)
    return binarna_pretraga_rekurzivna(a, levi, srednji - 1, x);
  /* Inace ga treba traziti u desnoj polovini */
  else
    return binarna_pretraga_rekurzivna(a, srednji + 1, desni, x);
}

int linearna_pretraga_rekurzivna_v2(Student a[], int n, char x[])
{
  /* Ako je niz prazan, vracamo -1, jer ga ne mozemo naci */
  if (n == 0)
    return -1;
  /* Kako trazimo prvog studenta sa trazenim prezimenom,
     pocinjemo sa prvim studentom u nizu. */
  if (strcmp(a[0].prezime, x) == 0)
    return 0;
  int i = linearna_pretraga_rekurzivna_v2(a + 1, n - 1, x);
  return i >= 0 ? 1 + i : -1;
}

int linearna_pretraga_rekurzivna(Student a[], int n, char x[])
{
  /* Ako je niz prazan, vracamo -1, jer ga ne mozemo naci */
  if (n == 0)
    return -1;
  /* Kako trazimo poslednjeg studenta sa trazenim prezimenom,
     pocinjemo sa poslednjim studentom u nizu. */
  if (strcmp(a[n - 1].prezime, x) == 0)
    return n - 1;
  return linearna_pretraga_rekurzivna(a, n - 1, x);
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
     ime datoteke sa informacijama o studentima */
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

  /* Unos indeksa koji se binarno trazi u nizu */
  printf("Unesite indeks studenta cije informacije zelite: ");
  scanf("%ld", &trazen_indeks);
  i = binarna_pretraga_rekurzivna(dosije, 0, br_studenata - 1,
                                  trazen_indeks);
  if (i == -1)
    printf("Ne postoji student sa indeksom %ld\n",
           trazen_indeks);
  else
    printf("Indeks: %ld, Ime i prezime: %s %s\n",
           dosije[i].indeks, dosije[i].ime, dosije[i].prezime);

  printf("Unesite prezime studenta cije informacije zelite: ");
  scanf("%s", trazeno_prezime);
  i = linearna_pretraga_rekurzivna(dosije, br_studenata,
                                   trazeno_prezime);
  if (i == -1)
    printf("Ne postoji student sa prezimenom %s\n",
           trazeno_prezime);
  else
    printf
        ("Poslednji takav student:\nIndeks: %ld, Ime i prezime: %s %s\n",
         dosije[i].indeks, dosije[i].ime, dosije[i].prezime);

  return 0;
}
