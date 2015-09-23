#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 50

void greska()
{
  printf("-1\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{

  FILE *ulaz;
  char **linije;
  int i, j, n;

  /* Proverava argumenata komandne linije. */
  if (argc != 2) {
    greska();
  }

  /* Otvaranje datoteke cije ime je navedeno kao argument
     komandne linije neposredno nakon imena programa koji se
     poziva. */
  ulaz = fopen(argv[1], "r");
  if (ulaz == NULL) {
    greska();
  }

  /* Ucitavanje broja linija. */
  fscanf(ulaz, "%d", &n);

  /* Alociranje memorije na osnovu ucitanog broja linija. */
  linije = (char **) malloc(n * sizeof(char *));
  if (linije == NULL) {
    greska();
  }
  for (i = 0; i < n; i++) {
    linije[i] = malloc(MAX * sizeof(char));
    if (linije[i] == NULL) {
      for (j = 0; j < i; j++) {
        free(linije[j]);
      }
      free(linije);
      greska();
    }
  }

  /* Ucitavanje svih n linija iz datoteke. */
  for (i = 0; i < n; i++) {
    fscanf(ulaz, "%s", linije[i]);
  }

  /* Ispisivanje u odgovarajucem poretku ucitane linije koje
     zadovoljavaju kriterijum. */
  for (i = n - 1; i >= 0; i--) {
    if (isupper(linije[i][0])) {
      printf("%s\n", linije[i]);
    }
  }

  /* Oslobadjanje memorije koja je dinamicki alocirana. */
  for (i = 0; i < n; i++) {
    free(linije[i]);
  }

  free(linije);

  /* Zatvaranje datoteku. */
  fclose(ulaz);

  return 0;

}
