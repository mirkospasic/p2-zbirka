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
  /* Binarnom pretragom trazimo jedinicu u binarnom zapisu broja 
     x najvece vaznosti, tj. najlevlju. Pretragu radimo od
     pozicije 0 do 31 */
  int d = 0, l = sizeof(unsigned int) * 8 - 1;
  int s;
  /* Sve dok je desna granica pretrage desnije od leve */
  while (d <= l) {
    /* Racunamo sredisnju poziciju */
    s = (l + d) / 2;
    /* Proveravamo da li je na toj poziciji trazena jedinica */
    if ((1 << s) <= x && (1 << (s + 1)) > x)
      return s;
    /* Pretrazujemo desnu polovinu binarnog zapisa */
    if ((1 << s) > x)
      l = s - 1;
    /* Pretrazujemo levu polovinu binarnog zapisa */
    else
      d = s + 1;
  }
  return s;
}

int main()
{
  unsigned int x;

  /* Unos podatka */
  printf("Unesi pozitivan ceo broj: ");
  scanf("%u", &x);

  /* Provera da li je uneti broj pozitivan */
  if (x == 0) {
    fprintf(stderr, "Logaritam od nule nije definisan\n");
    exit(EXIT_FAILURE);
  }

  /* Ispis povratnih vrednosti funkcija */
  printf("%u %u\n", logaritam_a(x), logaritam_b(x));

  return 0;
}
