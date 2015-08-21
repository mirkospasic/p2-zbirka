#include <stdio.h>
#include <stdlib.h>
#define MAX 100

/* Funkcija povecava za jedan sve elemente u prvoj polovini niza
   a smanjuje za jedan sve elemente u drugoj polovini niza. 
   Ukoliko niz ima neparan broj elemenata, srednji element 
   ostaje nepromenjen */
void povecaj_smanji (int *a , int n) 
{
  int *prvi = a;
  int *poslednji = a+n-1;
    
  while( prvi < poslednji ){
  
    /* Povecava se vrednost elementa na koji pokazuje 
	   pokazivac prvi */
	(*prvi)++;  
    
	/* Pokazivac prvi se pomera na sledeci element */
	prvi++;
	
    /* Smanjuje se vrednost elementa na koji pokazuje 
	   pokazivac poslednji */
	(*poslednji)--; 
	
    /* Pokazivac poslednji se pomera na prethodni element */
	poslednji--;       
  }
}

void povecaj_smanji_sazetije(int *a , int n) 
{
  int *prvi = a;
  int *poslednji = a+n-1;
    
  while( prvi < poslednji ){
    (*prvi++)++;
    (*poslednji--)--;
  }
}

int main() 
{
  int a[MAX];  
  int n;  
  int *p;  
    
  /* Unosimo broj elemenata */
  scanf("%d", &n);
    
  /* Proveravamo da li je prekoraceno ogranicenje dimenzije */
  if(n <= 0 || n > MAX) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija niza.\n");  
    exit(EXIT_FAILURE);
  } 
  
  /* Unosimo elemente niza */
  for(p = a; p - a < n; p++)
    scanf("%d", p);
         
  povecaj_smanji(a,n);
  /*  povecaj_smanji_sazetije(a,n); */
    
  /* Prikaz niza nakon modifikacije */  
  for(p = a; p - a < n; p++)
    printf("%d ", *p);
  printf("\n");
    
  return 0;
}


