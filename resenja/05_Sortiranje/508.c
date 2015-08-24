#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_BR_TACAKA 128

typedef struct Tacka {
  int x;
  int y;
} Tacka;

/* Funkcija racuna rastojanje zadate tacke od koordinatnog
   pocetka (0,0) */
float rastojanje(Tacka A)
{

  return sqrt(A.x * A.x + A.y * A.y);
}

/* Funkcija koja sortira niz tacaka po rastojanju od
   koordinatnog pocetka */
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

  /* Proveravamo broj argumenata komandne linije: ocekujemo ime
     izvrsnog programa, opciju, ime ulazne datoteke i ime
     izlazne datoteke tj. ocekujemo 4 argumenta */

  if (argc != 4) {
    fprintf(stderr,
            "Program se poziva sa: ./a.out opcija ulaz izlaz!\n");
    return 0;
  }

  /* Otvaramo datoteku u kojoj su zadate tacke */
  ulaz = fopen(argv[2], "r");
  if (ulaz == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s!\n",
            argv[2]);
    return 0;
  }

  /* Otvaramo datoteku u koju treba upisati rezultat */
  izlaz = fopen(argv[3], "w");
  if (izlaz == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s!\n",
            argv[3]);
    return 0;
  }

  /* Sve dok ne stignemo do kraja ulazne datoteke ucitavamo
     koordinate tacaka i smestamo ih na odgovarajucu poziciju
     odredjenu brojacem i; prilikom ucitavanja oslanjamo se na
     svojstvo funkcije fscanf povratka EOF vrednosti kada stigne 
     do kraja ulaza */

  i = 0;
  while (fscanf(ulaz, "%d %d", &tacke[i].x, &tacke[i].y) != EOF) {
    i++;
  }

  /* Cuvamo broj procitanih tacaka */
  n = i;


  /* Analiziramo zadatu opciju: kako ocekujemo da je argv[1]
     "-x" ili "-y" ili "-o" sigurni smo da je argv[1][0] crtica
     (karakter -) i dalje proveravamo sta je na sledecoj
     poziciji tj. sta je argv[1][1] */

  switch (argv[1][1]) {
  case 'x':
    /* Ako je u pitanju karakter x, pozivamo funkciju za
       sortiranje po vrednosti x koordinate */
    sortiraj_po_x(tacke, n);
    break;
  case 'y':
    /* Ako je u pitanju karakter y, pozivamo funkciju za
       sortiranje po vrednosti y koordinate */
    sortiraj_po_y(tacke, n);
    break;
  case 'o':
    /* Ako je u pitanju karakter o, pozivamo funkciju za
       sortiranje po udaljenosti od koorinatnog pocetka */
    sortiraj_po_rastojanju(tacke, n);
  }

  /* Upisujemo dobijeni niz u izlaznu datoteku */
  for (i = 0; i < n; i++) {
    fprintf(izlaz, "%d %d\n", tacke[i].x, tacke[i].y);
  }

  /* Zatvaramo otvorene datoteke */
  fclose(ulaz);
  fclose(izlaz);

  /* I zavrsavamo sa programom */
  return 0;
}
