#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
  double l, d, s, epsilon;

  char ime_funkcije[6];

  /* Pokazivac na funkciju koja ima jedan argument tipa double i
     povratnu vrednost istog tipa */
  double (*fp) (double);

  /* Ako korisnik nije uneo argument, prijavljuje se greska */
  if (argc != 2) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Nedovoljan broj argumenata komandne linije.\n");
    fprintf(stderr,
            "Program se poziva sa %s ime_funkcije iz math.h.\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Niska ime_funkcije sadrzi ime trazene funkcije koja je navedena
     u komandnoj liniji */
  strcpy(ime_funkcije, argv[1]);

  /* Inicijalizuje se pokazivac na funkciju koja se tabelira */
  if (strcmp(ime_funkcije, "sin") == 0)
    fp = &sin;
  else if (strcmp(ime_funkcije, "cos") == 0)
    fp = &cos;
  else if (strcmp(ime_funkcije, "tan") == 0)
    fp = &tan;
  else if (strcmp(ime_funkcije, "atan") == 0)
    fp = &atan;
  else if (strcmp(ime_funkcije, "asin") == 0)
    fp = &asin;
  else if (strcmp(ime_funkcije, "log") == 0)
    fp = &log;
  else if (strcmp(ime_funkcije, "log10") == 0)
    fp = &log10;
  else {
    fprintf(stderr, "Program ne podrzava trazenu funkciju!\n");
    exit(EXIT_SUCCESS);
  }

  printf("Unesite krajeve intervala: ");
  scanf("%lf %lf", &l, &d);

  if ((*fp) (l) * (*fp) (d) >= 0) {
    fprintf(stderr,
            "Funkcija %s na intervalu [%g, %g] ne zadovoljava uslove\n",
            ime_funkcije, l, d);
    exit(EXIT_FAILURE);
  }

  printf("Unesite preciznost: ");
  scanf("%lf", &epsilon);

  /* Sve dok se ne pronadje trazena vrednost argumenta */
  while (1) {
    /* Polovi se interval */
    s = (l + d) / 2;
    /* Ako je apsolutna vrednost trazene funkcije u ovoj tacki manja
       od zadate tacnosti, prekida se pretraga */
    if (fabs((*fp) (s)) < epsilon) {
      break;
    }
    /* Ako je nula u levom delu intervala, nastavlja se pretraga na
       [l, s] */
    if ((*fp) (l) * (*fp) (s) < 0)
      d = s;
    else
      /* Inace, na intervalu [s, d] */
      l = s;
  }

  /* Stampanje vrednosti trazene tacke */
  printf("%g\n", s);

  return 0;
}
