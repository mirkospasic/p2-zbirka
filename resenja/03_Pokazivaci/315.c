#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Funkcija ucitava elemente kvadratne matrice dimenzije n sa 
   standardnog ulaza */
void ucitaj_matricu(int m[][MAX], int n) 
{
  int i, j;
  
  for(i=0; i<n; i++) 
    for(j=0; j<n; j++) 
      scanf("%d", &m[i][j]);     
}

/* Funkcija ispisuje elemente kvadratne matrice dimenzije n na 
   standardni izlaz */
void ispisi_matricu(int m[][MAX], int n) {
  int i, j;  

  for(i=0; i<n; i++) { 
    for(j=0; j<n; j++)    
      printf("%d ", m[i][j]); 
    printf("\n");
  }
}

/* Funkcija proverava da li su zadate kvadratne matrice a i b 
   dimenzije n jednake */
int jednake_matrice(int a[][MAX], int b[][MAX], int n) {
  int i, j;
 
  for(i=0; i<n; i++) 
    for(j=0; j<n; j++) 
	  /* Nasli smo elemente na istim pozicijama u matricama
	     koji se razlikuju */
      if(a[i][j]!=b[i][j])
	    return 0;  
  
  /* Prosla je provera jednakosti za sve parove elemenata koji 
     su na istim pozicijama sto znaci da su matrice jednake */
  return 1;  
}

/* Funkcija izracunava zbir dve kvadratne matice */
void saberi(int a[][MAX], int b[][MAX], int c[][MAX], int n)
{
  int i, j;

  for(i=0; i<n; i++) 
    for(j=0; j<n; j++)      
      c[i][j] = a[i][j] + b[i][j];
}

/* Funkcija izracunava proizvod dve kvadratne matice */
void pomnozi(int a[][MAX], int b[][MAX], int c[][MAX], int n) 
{
  int i, j, k;
  
  for(i=0; i<n; i++) 
    for(j=0; j<n; j++) {      
	/* Mnozimo i-tu vrstu prve sa j-tom kolonom druge matrice */
	c[i][j] = 0;
	for(k=0; k<n; k++)
	  c[i][j] += a[i][k] * b[k][j];	  
	} 
}

int main() 
{
  /* Matrice ciji se elementi zadaju sa ulaza */
  int  a[MAX][MAX], b[MAX][MAX], c[MAX][MAX]; 
  
  /* Matrice zbira i proizvoda */  
  int zbir[MAX][MAX], proizvod[MAX][MAX];  
  
  /* Dimenzija matrica */
  int n;  
  int i, j;
  
  /* Ucitavamo dimenziju kvadratnih matrica i proveravamo njenu 
     korektnost */    
  scanf("%d", &n);
  
  /* Proveravamo da li je prekoraceno ogranicenje */
  if( n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
	fprintf(stderr, "matrica.\n");
    exit(EXIT_FAILURE);	
  }
  
  /* Ucitavamo matrice */
  ucitaj_matricu(a, n);
  ucitaj_matricu(b, n);
  
  /* Izracunavamo zbir i proizvod matrica */
  saberi(a, b, zbir, n);
  pomnozi(a, b, proizvod, n);  
  
  /* Ispisujemo rezultat */  
  if(jednake_matrice(a, b, n) == 1)
    printf("da\n");  
  else
    printf("ne\n");
	
  printf("Zbir matrica je:\n");
  ispisi_matricu(zbir, n);
  
  printf("Proizvod matrica je:\n");
  ispisi_matricu(proizvod, n);
 
  return 0;
}

