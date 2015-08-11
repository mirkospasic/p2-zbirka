#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

int main(int argc, char **argv) {
  FILE *f;
  int brojac = 0;
  char linija[MAX], *p;

  if (argc != 3) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(linija, MAX, f) != NULL) {
    p = linija;
    while (1) {
      p = strstr(p, argv[2]);
      if (p == NULL)
	break;
      brojac++;
      p = p + strlen(argv[2]);
    }
  }
  
  fclose(f);
  
  printf("%d\n", brojac);

  return 0;
}
