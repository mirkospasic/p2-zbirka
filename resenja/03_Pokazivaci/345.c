
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Funkcija tabela() prihvata granice intervala a i b, broj
   ekvidistantnih tacaka n, kao i pokazivac f koji pokazuje na 
   funkciju koja prihvata double argument, i vraca double
   vrednost. Za tako datu funkciju ispisuju se njene vrednosti 
   u intervalu [a,b] u n ekvidistantnih tacaka intervala */
void tabela(double a, double b, int n, double (*fp) (double))
{
  int i;
  double x;

  printf("-----------------------\n");
  for (i = 0; i < n; i++) {
    x = a + i * (b - a) / (n - 1);
    printf("| %8.5f | %8.5f |\n", x, (*fp) (x));
  }
  printf("-----------------------\n");
}

double sqr(double a)
{
  return a * a;
}

int main(int argc, char *argv[])
{
  double a, b;
  int n;
  
  char ime_fje[6];
  
  /* Pokazivac na funkciju koja ima jedan argument tipa double i 
     povratnu vrednost istog tipa */
  double (*fp) (double);

  /* Ako korisnik nije uneo trazene argumente, prijavljuje se
     greška */
  if (argc < 2) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s ime_funkcije iz math.h.\n",
           argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Niska ime_fje sadrzi ime trazene funkcije koja je
     navedena u komandnoj liniji */
  strcpy(ime_fje, argv[1]);

  /* Inicijalizuje se pokazivac na funkciju koja treba da se
     tabelira */
  if (strcmp(ime_fje, "sin") == 0)
    fp = &sin;
  else if (strcmp(ime_fje, "cos") == 0)
    fp = &cos;
  else if (strcmp(ime_fje, "tan") == 0)
    fp = &tan;
  else if (strcmp(ime_fje, "atan") == 0)
    fp = &atan;
  else if (strcmp(ime_fje, "acos") == 0)
    fp = &acos;
  else if (strcmp(ime_fje, "asin") == 0)
    fp = &asin;
  else if (strcmp(ime_fje, "exp") == 0)
    fp = &exp;
  else if (strcmp(ime_fje, "log") == 0)
    fp = &log;
  else if (strcmp(ime_fje, "log10") == 0)
    fp = &log10;
  else if (strcmp(ime_fje, "sqrt") == 0)
    fp = &sqrt;
  else if (strcmp(ime_fje, "floor") == 0)
    fp = &floor;
  else if (strcmp(ime_fje, "ceil") == 0)
    fp = &ceil;
  else if (strcmp(ime_fje, "sqr") == 0)
    fp = &sqr;
  else {
    printf("Program jos uvek ne podrzava trazenu funkciju!\n");
    exit(EXIT_SUCCESS);
  }

  printf("Unesite krajeve intervala:\n");
  scanf("%lf %lf", &a, &b);

  printf("Koliko tacaka ima na ekvidistantnoj mrezi ");
  printf("(ukljucujuci krajeve intervala)?\n");
  scanf("%d", &n);

  /* Mreza mora da ukljucuje bar krajeve intervala, tako da se
     mora uneti broj veci od 2 */
  if (n < 2) {
    fprintf(stderr, "Broj tacaka mreze mora biti bar 2!\n");
    exit(EXIT_FAILURE);
  }

  /* Ispisuje se ime funkcije */
  printf("     x %10s(x)\n", ime_fje);

  /* Prosledjuje se funkciji tabela() funkcija zadata kao
     argument komandne linije */
  tabela(a, b, n, fp);

  exit(EXIT_SUCCESS);
}
