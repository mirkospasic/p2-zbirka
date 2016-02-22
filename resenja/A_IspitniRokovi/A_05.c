#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Struktura trougao */
typedef struct _trougao {
  double xa, ya, xb, yb, xc, yc;
} trougao;

/* Funkcija racuna duzinu duzi */
double duzina(double x1, double y1, double x2, double y2)
{
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

/* Funkcija racuna povrsinu trougla koristeci Heronov obrazac */
double povrsina(trougao t)
{
  /* Racunaju se duzine stranica trougla */
  double a = duzina(t.xb, t.yb, t.xc, t.yc);
  double b = duzina(t.xa, t.ya, t.xc, t.yc);
  double c = duzina(t.xa, t.ya, t.xb, t.yb);
  /* Racuna se poluobim trougla */
  double s = (a + b + c) / 2;
  /* Primenom Heronovog obrasca racuna se povrsina trougla */
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

/* Funkcija poredi dva trougla. Ukoliko je povrsina trougla koji je
   prvi argument funkcije manja od povrsine trougla koji je drugi
   element funkcije funkcija vraca 1, ukoliko je veca -1, a ukoliko
   su povrsine dva trougla jednake vraca nulu. Dakle, funkcija je
   napisana tako da se moze proslediti funkciji qsort da se niz
   trouglova sortira po povrsini opadajuce. */
int poredi(const void *a, const void *b)
{
  trougao x = *(trougao *) a;
  trougao y = *(trougao *) b;
  double xp = povrsina(x);
  double yp = povrsina(y);
  if (xp < yp)
    return 1;
  if (xp > yp)
    return -1;
  return 0;
}

int main()
{
  FILE *f;
  int n, i;
  trougao *niz;

  /* Otvara se datoteka ciji je naziv trouglovi.txt */
  if ((f = fopen("trouglovi.txt", "r")) == NULL) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitava se podatak o broju trouglova iz datoteke */
  if (fscanf(f, "%d", &n) != 1) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Dinamicka alokacija memorije za niz trouglova duzine n
     rezervise se memorijski prostor */
  if ((niz = malloc(n * sizeof(trougao))) == NULL) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavaju se podaci u niz iz otvorene datoteke */
  for (i = 0; i < n; i++) {
    if (fscanf(f, "%lf%lf%lf%lf%lf%lf", &niz[i].xa, &niz[i].ya,
               &niz[i].xb, &niz[i].yb, &niz[i].xc,
               &niz[i].yc) != 6) {
      fprintf(stderr, "-1\n");
      exit(EXIT_FAILURE);
    }
  }

  /* Poziva se funkcija qsort da sortira niz na osnovu funkcije
     poredi */
  qsort(niz, n, sizeof(trougao), &poredi);

  /* Ispisuje se sortirani niz na standardni izlaz */
  for (i = 0; i < n; i++)
    printf("%g %g %g %g %g %g\n", niz[i].xa, niz[i].ya, niz[i].xb,
           niz[i].yb, niz[i].xc, niz[i].yc);

  /* Oslobadja se dinamicki alocirana memorija */
  free(niz);

  /* Zatvara se datoteka */
  fclose(f);

  exit(EXIT_SUCCESS);
}
