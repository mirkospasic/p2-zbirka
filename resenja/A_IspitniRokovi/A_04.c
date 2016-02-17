#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAKS 128

int main(int argc, char **argv)
{
  FILE *f;
  int brojac = 0;
  char linija[MAKS], *p;

  /* Provera da li je broj argumenata komandne linije 3 */
  if (argc != 3) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
  /* Otvaranje datoteke ciji je naziv zadat kao argument komandne
     linije */
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }
  /* Ucitavanje iz otvorene datoteke - liniju po liniju */
  while (fgets(linija, MAKS, f) != NULL) {
    p = linija;
    while (1) {
      p = strstr(p, argv[2]);

      /* Ukoliko nije podniska tj. p je NULL izlazi se iz petlje */
      if (p == NULL)
        break;
      /* Inace se uvecava brojac */
      brojac++;
      /* p se pomera da bi se u sledecoj iteraciji posmatra ostatak
         linije nakon uocene podniske */
      p = p + strlen(argv[2]);
    }
  }

  /* Zatvaranje datoteke */
  fclose(f);

  /* Ispisivanje vrednosti brojaca */
  printf("%d\n", brojac);

  exit(EXIT_SUCCESS);
}
