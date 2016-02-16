#include <stdio.h>
#include <stdlib.h>
#include "matrica.h"

/* Funkcija racuna zbir elemenata v-te vrste */
int zbir_vrste(int **M, int n, int v)
{
  int j, zbir = 0;
  for (j = 0; j < n; j++)
    zbir += M[v][j];
  return zbir;
}

/* Funkcija racuna zbir elemenata k-te kolone */
int zbir_kolone(int **M, int n, int k)
{
  int i, zbir = 0;
  for (i = 0; i < n; i++)
    zbir += M[i][k];
  return zbir;
}

/* Funkcija proverava da li je kvadrat koji joj se prosledjuje kao
   argument magican. Ukoliko jeste magican funkcija vraca 1, inace 0. 
   Argument funkcije zbir ce sadrzati zbir elemenata neke vrste ili
   kolone ukoliko je kvadrat magican. */
int magicni_kvadrat(int **M, int n, int *zbir_magicnog)
{
  int i, j;
  int zbir = 0, zbir_pom;
  /* Promenljivu zbir inicijalizujemo na zbir 0-te vreste */
  zbir = zbir_vrste(M, n, 0);

  /* Racunaju se zbirovi u ostalim vrstama i ako neki razlikuje od
     vrednosti promeljive zbir funkcija vraca 1 */
  for (i = 1; i < n; i++) {
    zbir_pom = zbir_vrste(M, n, i);
    if (zbir_pom != zbir)
      return 0;
  }
  /* Racunaju se zbirovi u svim kolonama i ako neki razlikuje od
     vrednosti promeljive zbir funkcija vraca 1 */
  for (j = 0; j < n; j++) {
    zbir_pom = zbir_kolone(M, n, j);
    if (zbir_pom != zbir)
      return 0;
  }
  /* Inace su zbirovi svih vrsta i kolona jednaki, postavlja se
     vresnost u zbir_magicnog i funkcija vraca 1 */
  *zbir_magicnog = zbir;
  return 1;
}

int main()
{
  int n;
  int **matrica = NULL;
  int zbir_magicnog;
  scanf("%d", &n);

  /* Provera da li je n strogo pozitivan */
  if (n <= 0) {
    printf("-1\n");
    exit(EXIT_FAILURE);
  }

  /* Dinamicka alokacija kvadratne matrice dimenzije n */
  matrica = alociraj_matricu(n, n);
  if (matrica == NULL) {
    printf("-1\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje elemenata matrice sa standardnog ulaza */
  ucitaj_matricu(matrica, n, n);

  /* Ispisivanje rezultata na osnovu fukcije magicni_kvadrat */
  if (magicni_kvadrat(matrica, n, &zbir_magicnog)) {
    printf("%d\n", zbir_magicnog);
  } else
    printf("-\n");

  /* Oslobadjanje dinamicki alocirane memorije */
  matrica = dealociraj_matricu(matrica, n);

  exit(EXIT_SUCCESS);
}
