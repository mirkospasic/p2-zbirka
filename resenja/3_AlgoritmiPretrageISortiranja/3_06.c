#include <stdio.h>
#include <math.h>

/* Tacnost */
#define EPS 0.001

int main()
{
  /* Kod intervala [0, 2] leva granica je 0, a desna 2 */
  double l = 0, d = 2, s;

  /* Sve dok se ne pronadje trazena vrednost argumenta */
  while (1) {
    /* Polovi se interval */
    s = (l + d) / 2;
    /* Ako je apsolutna vrednost kosinusa u ovoj tacki manja od
       zadate tacnosti, prekida se pretraga */
    if (fabs(cos(s)) < EPS)
      break;
    /* Ako je nula u levom delu intervala, nastavlja se pretraga na
       [l, s] */
    if (cos(l) * cos(s) < 0)
      d = s;
    else
      /* Inace, na intervalu [s, d] */
      l = s;
  }

  /* Stampa se vrednost trazene tacke */
  printf("%g\n", s);

  return 0;
}
