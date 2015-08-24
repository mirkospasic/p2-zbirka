#include <stdio.h>
#include <math.h>

/* Tacnost */
#define EPS 0.001

int main()
{
  double l, d, s;

  /* Posto je u pitanju interval [0, 2] leva granica je 0, a
     desna 2 */
  l = 0;
  d = 2;

  /* Sve dok ne pronadjemo trazenu vrednost argumenta */
  while (1) {
    /* Pronalazimo sredinu intervala */
    s = (l + d) / 2;
    /* Ako je vrednost kosinusa u ovoj tacki manja od zadate
       tacnosti, prekidamo pretragu */
    if (fabs(cos(s)) < EPS) {
      break;
    }
    /* Ako je nula u levom delu intervala, nastavljamo pretragu
       na intervalu [l, s] */
    if (cos(l) * cos(s) < 0)
      d = s;
    else
      /* Inace, nastavljamo pretragu na intervalu [s, d] */
      l = s;
  }

  /* Stampamo vrednost trazene tacke */
  printf("%g\n", s);

  return 0;
}
