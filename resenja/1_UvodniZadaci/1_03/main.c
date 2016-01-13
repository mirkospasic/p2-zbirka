#include <stdio.h>
#include "polinom.h"

int main(int argc, char **argv)
{
  Polinom p, q, r;
  double x;
  int n;

  /* Unos polinoma p */
  printf
      ("Unesite polinom p (prvo stepen, pa zatim koeficijente od najveceg stepena do nultog):\n");
  p = ucitaj();

  /* Ispis polinoma p */
  ispisi(&p);

  /* Unos polinoma q */
  printf
      ("Unesite drugi polinom q (prvo stepen, pa zatim koeficijente od najveceg stepena do nultog):\n");
  q = ucitaj();

  /* Polinomi se sabiraju i ispisuje se izracunati zbir */
  r = saberi(&p, &q);
  printf("Zbir polinoma je: ");
  ispisi(&r);

  /* Polinomi se mnoze i ispisuje se izracunati prozivod */
  r = pomnozi(&p, &q);
  printf("Prozvod polinoma je polinom r:\n");
  ispisi(&r);

  /* Ispisuje se vrednost polinoma u unetoj tacki */
  printf("Unesite tacku u kojoj racunate vrednost polinoma r\n");
  scanf("%lf", &x);
  printf("Vrednost polinoma u tacki je %.2f\n", izracunaj(&r, x));


  /* Racuna se n-ti izvoda polinoma i ispisuje se dobijeni polinoma */
  printf("Unesite izvod polinoma koji zelite:\n");
  scanf("%d", &n);
  r = n_izvod(&r, n);
  printf("%d. izvod polinoma r je: ", n);
  ispisi(&r);

  exit(EXIT_SUCCESS);
}
