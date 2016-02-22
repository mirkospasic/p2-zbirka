#include <stdio.h>
#include <stdlib.h>

#include "polinom.h"

int main(int argc, char **argv)
{
  Polinom p, q, z, r;
  double x;
  int n;

  /* Unosi se polinom p */
  p = ucitaj();

  /* Ispisuje se polinom p */
  ispisi(&p);

  /* Unosi se polinom q */
  q = ucitaj();

  /* Polinomi se sabiraju i ispisuje se izracunati zbir */
  z = saberi(&p, &q);
  printf("Zbir polinoma je polinom z:\n");
  ispisi(&z);

  /* Polinomi se mnoze i ispisuje se izracunati prozivod */
  r = pomnozi(&p, &q);
  printf("Prozvod polinoma je polinom r:\n");
  ispisi(&r);

  /* Ispisuje se vrednost polinoma u unetoj tacki */
  printf("Unesite tacku u kojoj racunate vrednost polinoma z:\n");
  scanf("%lf", &x);
  printf("Vrednost polinoma z u tacki %.2f je %.2f\n", x,
         izracunaj(&z, x));

  /* Racuna se n-ti izvod polinoma i ispisuje se rezultat */
  printf("Unesite izvod polinoma koji zelite:\n");
  scanf("%d", &n);
  r = n_izvod(&r, n);
  printf("%d. izvod polinoma r je: ", n);
  ispisi(&r);

  exit(EXIT_SUCCESS);
}
