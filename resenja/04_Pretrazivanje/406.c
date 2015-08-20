#include <stdio.h>
#include <math.h>

/* tacnost */
#define EPS 0.001

int main()
{
  double l, d, s;

  /* posto je u pitanju interval [0, 2] leva granica je 0, a
     desna 2 */
  l = 0;
  d = 2;

  /* sve dok ne pronadjemo trazenu vrednost argumenta */
  while (1) {
    /* pronalazimo sredinu intervala */
    s = (l + d) / 2;
    /* ako je vrednost kosinusa u ovoj tacki manja od zadate
       tacnosti, prekidamo pretragu */
    if (fabs(cos(s)) < EPS) {
      break;
    }
    /* ako je nula u levom delu intervala, nastavljamo pretragu
       na intervalu [l, s] */
    if (cos(l) * cos(s) < 0)
      d = s;
    else
      /* inace, nastavljamo pretragu na intervalu [s, d] */
      l = s;
  }

  /* stampamo vrednost trazene tacke */
  printf("%g\n", s);

  return 0;
}
