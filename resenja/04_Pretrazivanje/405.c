#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* Struktura koja opisuje tacku u ravni */
typedef struct Tacka {
  float x;
  float y;
} Tacka;

/* Funkcija koja racuna rastojanje zadate tacke od koordinatnog
   pocetka (0,0) */
float rastojanje(Tacka A)
{
  return sqrt(A.x * A.x + A.y * A.y);
}

/* Funkcija koja pronalazi tacku najblizu koordinatnom pocetku u 
   nizu zadatih tacaka t dimenzije n */
Tacka najbliza_koordinatnom(Tacka t[], int n)
{
  Tacka najbliza;
  int i;
  najbliza = t[0];
  for (i = 1; i < n; i++) {
    if (rastojanje(t[i]) < rastojanje(najbliza)) {
      najbliza = t[i];
    }
  }
  return najbliza;
}

/* Funkcija koja pronalazi tacku najblizu x osi u nizu zadatih
   tacaka t dimenzije n */
Tacka najbliza_x_osi(Tacka t[], int n)
{

  Tacka najbliza;
  int i;
  najbliza = t[0];
  for (i = 1; i < n; i++) {
    if (fabs(t[i].x) < fabs(najbliza.x)) {
      najbliza = t[i];
    }
  }
  return najbliza;
}

/* Funkcija koja pronalazi tacku najblizu y osi u nizu zadatih
   tacaka t dimenzije n */
Tacka najbliza_y_osi(Tacka t[], int n)
{
  Tacka najbliza;
  int i;
  najbliza = t[0];
  for (i = 1; i < n; i++) {
    if (fabs(t[i].y) < fabs(najbliza.y)) {
      najbliza = t[i];
    }
  }
  return najbliza;
}

#define MAX 1024

int main(int argc, char *argv[])
{
  FILE *ulaz;
  Tacka tacke[MAX];
  Tacka najbliza;
  int i, n;

  /* Ocekujemo da korisnik unese barem ime izvrsne verzije
     programa i ime datoteke sa tackama */
  if (argc < 2) {
    fprintf(stderr,
            "koriscenje programa: %s ime_datoteke\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Otvaramo datoteku za citanje */
  ulaz = fopen(argv[1], "r");
  if (ulaz == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s!\n",
            argv[1]);
    return EXIT_FAILURE;
  }

  /* Sve dok ima tacaka u datoteci, smestamo ih u niz sa
     tackama; i predstavlja indeks tekuce tacke */
  i = 0;
  while (fscanf(ulaz, "%f %f", &tacke[i].x, &tacke[i].y) == 2) {
    i++;
  }
  n = i;

  /* Proveravamo koji su dodatni argumenti komandne linije. Ako
     nema dodatnih argumenata */
  if (argc == 2)
    /* Trazimo najblizu tacku u odnosu na koordinatni pocetak */
    najbliza = najbliza_koordinatnom(tacke, n);
  /* Inace proveravamo koji je dodatni argument. Ako je u
     pitanju opcija -x */
  else if (strcmp(argv[2], "-x") == 0)
    /* Racunamo rastojanje u odnosu na x osu */
    najbliza = najbliza_x_osi(tacke, n);
  /* Ako je u pitanju opcija -y */
  else if (strcmp(argv[2], "-y") == 0)
    /* Racunamo rastojanje u odnosu na y osu */
    najbliza = najbliza_y_osi(tacke, n);
  else {
    /* Ako nije zadata opcija -x ili -y, ispisujemo obavestenje
       za korisnika i prekidamo izvrsavanje programa */
    fprintf(stderr, "Pogresna opcija\n");
    return EXIT_FAILURE;
  }

  /* Stampamo koordinate trazene tacke */
  printf("%g %g\n", najbliza.x, najbliza.y);

  fclose(ulaz);

  return 0;
}
