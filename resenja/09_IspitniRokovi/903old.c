#include <stdio.h>
#define MAX 50

{
  int m[MAX][MAX];
  int v, k;
  int i, j;
  int max_broj_negativnih, max_indeks_kolone;
  int broj_negativnih;
  
  /* Ucitavanje dimenzije matrice */ 
  scanf("%d", &v); 
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);  
  }
  scanf("%d", &k);
  if (k < 0 || k > MAX) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);  
  }
  /* Ucitavanje elemenata matrice */ 
  for (i = 0; i < v; i++) {
    for (j = 0; j < k; j++) {
      scanf("%d", &m[i][j]);
	  }
  }
  
     elemenata */ 
  max_indeks_kolone = 0;
  max_broj_negativnih = 0;
  for (i = 0; i < v; i++) {
    if (m[i][0] < 0) {
      max_broj_negativnih++;
    }
  }
  for (j = 0; j < k; j++) {
    broj_negativnih = 0;
    for (i = 0; i < v; i++) {
      if (m[i][j] < 0) {
        broj_negativnih++;      
	  }
      if (broj_negativnih > max_broj_negativnih) {
        max_indeks_kolone = j;
      }
    }
  }
  
  /* Ispisivanje trazenog rezultata */ 
  printf("%d\n", max_indeks_kolone);
  return 0;

