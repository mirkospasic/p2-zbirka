#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BR_TACAKA 128

/* Struktura koja reprezentuje koordinate tacke */
typedef struct Tacka {
  int x;
  int y;
} Tacka;

/* Funkcija racuna rastojanje zadate tacke od koordinatnog pocetka */
float rastojanje(Tacka A)
{
  return sqrt(A.x * A.x + A.y * A.y);
}

/* Funkcija koja sortira niz tacaka po rastojanju od koordinatnog
   pocetka */
void sortiraj_po_rastojanju(Tacka t[], int n)
{
  int min, i, j;
  Tacka tmp;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++) {
      if (rastojanje(t[j]) < rastojanje(t[min])) {
        min = j;
      }
    }
    if (min != i) {
      tmp = t[i];
      t[i] = t[min];
      t[min] = tmp;
    }
  }
}

/* Funkcija koja sortira niz tacaka po vrednosti x koordinate */
void sortiraj_po_x(Tacka t[], int n)
{
  int min, i, j;
  Tacka tmp;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++) {
      if (abs(t[j].x) < abs(t[min].x)) {
        min = j;
      }
    }
    if (min != i) {
      tmp = t[i];
      t[i] = t[min];
      t[min] = tmp;
    }
  }
}

/* Funkcija koja sortira niz tacaka po vrednosti y koordinate */
void sortiraj_po_y(Tacka t[], int n)
{
  int min, i, j;
  Tacka tmp;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++) {
      if (abs(t[j].y) < abs(t[min].y)) {
        min = j;
      }
    }
    if (min != i) {
      tmp = t[i];
      t[i] = t[min];
      t[min] = tmp;
    }
  }
}

int main(int argc, char *argv[])
{
  FILE *ulaz;
  FILE *izlaz;
  Tacka tacke[MAX_BR_TACAKA];
  int i, n;

  /* Proveravanje broja argumenata komandne linije: ocekuje se ime
     izvrsnog programa, opcija, ime ulazne datoteke i ime izlazne
     datoteke, tj. 4 argumenta */
  if (argc != 4) {
    fprintf(stderr,
            "Program se poziva sa: ./a.out opcija ulaz izlaz!\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke u kojoj su zadate tacke */
  ulaz = fopen(argv[2], "r");
  if (ulaz == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s!\n",
            argv[2]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke u koju treba upisati rezultat */
  izlaz = fopen(argv[3], "w");
  if (izlaz == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s!\n",
            argv[3]);
    exit(EXIT_FAILURE);
  }

  /* Sve dok se ne stigne do kraja ulazne datoteke, ucitavaju se
     koordinate tacaka i smestaju na odgovarajuce pozicije odredjene
     brojacem i. */
  i = 0;
  while (fscanf(ulaz, "%d %d", &tacke[i].x, &tacke[i].y) != EOF) {
    i++;
  }

  /* Ukupan broj procitanih tacaka */
  n = i;

  /* Analizira se prosledjena opcija. Moguce vrednosti za argv[1] su
     "-x" ili "-y" ili "-o", pa je argv[1][0] sigurno crtica
     (karakter -), a karakter argv[1][1] odredjuje kriterijum
     sortiranja */
  switch (argv[1][1]) {
  case 'x':
    /* Sortiranje po vrednosti x koordinate */
    sortiraj_po_x(tacke, n);
    break;
  case 'y':
    /* Sortiranje po vrednosti y koordinate */
    sortiraj_po_y(tacke, n);
    break;
  case 'o':
    /* Sortiranje po udaljenosti od koorinatnog pocetka */
    sortiraj_po_rastojanju(tacke, n);
    break;
  }

  /* Upisivanje dobijenog niza u izlaznu datoteku */
  for (i = 0; i < n; i++) {
    fprintf(izlaz, "%d %d\n", tacke[i].x, tacke[i].y);
  }

  /* Zatvaranje otvorenih datoteka */
  fclose(ulaz);
  fclose(izlaz);

  return 0;
}
