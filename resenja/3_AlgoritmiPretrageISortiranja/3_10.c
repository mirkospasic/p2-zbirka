#include <stdio.h>
#include <stdlib.h>

unsigned int logaritam_a(unsigned int x)
{
  /* Izlaz iz rekurzije */
  if (x == 1)
    return 0;
  /* Rekurzivni korak */
  return 1 + logaritam_a(x >> 1);
}

unsigned int logaritam_b(unsigned int x)
{
  /* Binarnom pretragom se trazi jedinica u binarnom zapisu broja x
     najvece vaznosti, tj. najlevlja. Pretragu se vrsi od pozicije 0
     do 31 */
  int d = 0, l = sizeof(unsigned int) * 8 - 1;
  int s;
  /* Sve dok je desna granica pretrage desnije od leve */
  while (d <= l) {
    /* Racuna se sredisnja pozicija */
    s = (l + d) / 2;
    /* Proverava se da li je na toj poziciji trazena jedinica */
    if ((1 << s) <= x && (1 << (s + 1)) > x)
      return s;
    /* Pretraga desne polovine binarnog zapisa */
    if ((1 << s) > x)
      l = s - 1;
    /* Pretraga leve polovine binarnog zapisa */
    else
      d = s + 1;
  }
  return s;
}

int main()
{
  unsigned int x;

  /* Unos podatka */
  scanf("%u", &x);

  /* Provera da li je uneti broj pozitivan */
  if (x == 0) {
    fprintf(stderr, "Greska: Logaritam od nule nije definisan\n");
    exit(EXIT_FAILURE);
  }

  /* Ispis povratnih vrednosti funkcija */
  printf("%u %u\n", logaritam_a(x), logaritam_b(x));

  exit(EXIT_SUCCESS);
}
