#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ucitaj_matricu(int ** M, int n, int m) 
{
  int i, j;
  
  /* Popunjavamo matricu vrstu po vrstu */ 
  for(i=0; i<n; i++)
    /* Popunjavamo i-tu vrstu matrice */
    for(j=0; j<m; j++)
      scanf("%d", &M[i][j]);    
}

void ispisi_elemente_ispod_dijagonale(int ** M, int n, int m) 
{
  int i, j;
  
  for(i=0; i<n; i++) { 
    /* Ispisujemo elemente ispod glavne dijagonale matrice */
    for(j=0; j<=i; j++) 
      printf("%d ", M[i][j]);        
    printf("\n");
  }
}

int main() {
  int m, n, i, j; 
  int **matrica = NULL;
  
  /* Unosimo dimenzije matrice */
  scanf("%d %d",&n, &m);

  /* Alociramo prostor za niz pokazivaca na vrste matrice */
  matrica = (int **) malloc(n * sizeof(int*));
  if(matrica == NULL) {
    fprintf(stderr,"malloc(): Neuspela alokacija\n");
    exit(EXIT_FAILURE);
  }

  /* Alociramo prostor za svaku vrstu matrice */
  for(i=0; i<n; i++) {
    matrica[i] = (int*) malloc(m * sizeof(int));

    if(matrica[i] == NULL) {
      fprintf(stderr,"malloc(): Neuspela alokacija\n");
      for(j=0; j<i; j++)
        free(matrica[j]);            
      free(matrica);
      exit(EXIT_FAILURE);
    }
  }

  ucitaj_matricu(matrica, n, m); 
    
  ispisi_elemente_ispod_dijagonale(matrica, n, m);
    
  /* Oslobadjamo dinamicki alociranu memoriju za matricu. 
     Prvo oslobadjamo prostor rezervisan za svaku vrstu */
  for( j=0; j<n; j++)
    free(matrica[j]);

  /* Zatim oslobadjamo memoriju za niz pokazivaca na vrste
     matrice */
  free(matrica);

  return 0;
}
