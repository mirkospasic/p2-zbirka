#include <stdio.h>
#include <stdlib.h>

/* Funkcija proverava da li je kvadrat koji joj se prosledjuje kao  argument magican. Ukoliko jeste magican funkcija vracav1, inace 0. */ 
int magicni_kvadrat(int **M, int n) 
{
  int i, j;
  int zbir = 0, zbir_pom;
  for (j = 0; j < n; j++)
    zbir += M[0][j];
  
  for (i = 1; i < n; i++) {
    zbir_pom = 0;
    for (j = 0; j < n; j++)
      zbir_pom += M[i][j];
	  if (zbir_pom != zbir)
	    return 0;
  }
  for (j = 0; j < n; j++) {
    zbir_pom = 0;
    for (i = 0; i < n; i++)
      zbir_pom += M[i][j];
    if (zbir_pom != zbir)
      return 0;
  }
  return 1;}
int main() 
{
  int n, i, j;
  int **matrica = NULL;
  int zbir = 0;
  scanf("%d", &n);
  
  /* Provera da li je n strogo pozitivan */ 
  if (n <= 0) {
    printf("-1\n");
    exit(EXIT_FAILURE);
  }
  
  /* Dinamicka alokacija matrice dimenzije nxn */ 
  matrica = (int **) malloc(n * sizeof(int *));
  if (matrica == NULL) {
    printf("-1\n");
    exit(EXIT_FAILURE);  
  }
  for (i = 0; i < n; i++) {
    matrica[i] = (int *) malloc(n * sizeof(int));
    if (matrica[i] == NULL) {
	  fprintf(stderr, "-1\n");
      for (j = 0; j < i; j++)
        free(matrica[j]);
      free(matrica);
      exit(EXIT_FAILURE);
    }
  }
 
  /* Ucitavanje elemenata matrice sa standardnog ulaza */ 
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &matrica[i][j]);
      
  /* Ispisivanje rezultata na osnovu fukcije magicni_kvadrat */ 
  if (magicni_kvadrat(matrica, n)) {
    for (i = 0; i < n; i++)
      zbir += matrica[0][i];
    printf("%d\n", zbir);
  } else
    printf("-\n");
  
  /* Oslobadjanje dinamicki alocirane memorije */ 
  for (j = 0; j < n; j++)
    free(matrica[j]);
  free(matrica);
  
  return 0;}


