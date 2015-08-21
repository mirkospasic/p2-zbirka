#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Funkcija obrce elemente niza koriscenjem indekse sintakse */
void obrni_niz_v1(int a[] , int n) 
{
  int i, j;
  
  for(i = 0, j = n-1; i < j; i++, j--) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
}

/* Funkcija obrce elemente niza koriscenjem pokazivacke 
   sintakse. Umesto "void obrni_niz(int *a, int n)" potpis 
   metode bi mogao da bude i "void obrni_niz(int a[], int n)".
   U oba slucaja se argument funkcije "a" tumaci kao pokazivac, 
   ili tacnije, kao adresa prvog elementa niza. U odnosu na 
   njega se odredjuju adrese ostalih elemenata u nizu */
void obrni_niz_v2(int *a, int n) 
{  
  /* Pokazivaci na elemente niza a */
  int *prvi, *poslednji;   
    
  
  for(prvi = a, poslednji = a + n - 1; 
                prvi < poslednji; prvi++, poslednji--) {
    int t = *prvi;
    *prvi = *poslednji;
    *poslednji = t;
  }
}

/* Funkcija obrce elemente niza koriscenjem pokazivacke 
   sintakse - modifikovano koriscenje pokazivaca */
void obrni_niz_v3(int *a, int n) 
{  
  /* Pokazivaci na elemente niza a */
  int *prvi, *poslednji;   
    
  /* Obrcemo niz */
  for(prvi = a, poslednji = a + n - 1; prvi < poslednji;  ) {
    int t = *prvi;
    
    /* Na adresu na koju pokazuje pokazivac "prvi" postavlja se 
	   vrednost koja se nalazi na adresi na koju pokazuje 
	   pokazivac "poslednji". Nakon toga se pokazivac "prvi" 
	   uvecava za jedan sto za  posledicu ima da "prvi" pokazuje 
	   na sledeci element u nizu */
    *prvi++ = *poslednji; 
    
    /* Vrednost promenljive "t" se postavlja na adresu na koju 
	   pokazuje pokazivac "poslednji". Ovaj pokazivac se zatim 
	   umanjuje za jedan, sto za posledicu ima da pokazivac 
	   "poslednji" sada pokazuje na element koji mu prethodi u 
	   nizu */
     *poslednji-- = t;
  }
}

int main() 
{
  /* Deklaracija niza a od najvise MAX elemenata */
  int a[MAX];  
  
  /* Broj elemenata niza a */
  int n; 

  /* Pokazivac na elemente niza a */  
  int *p;  
  
  /* Unosimo dimenziju niza */  
  scanf("%d", &n);
    
  /* Proveravamo da li je prekoraceno ogranicenje dimenzije */ 
  if(n <= 0 || n > MAX) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija niza.\n");  
    exit(EXIT_FAILURE);
  }  
  
  /* Unosimo elemente niza */  
  for(p = a; p - a < n; p++)
    scanf("%d", p);  
    
  obrni_niz_v1(a,n);
  // obrni_niz_v2(a,n);
  // obrni_niz_v3(a,n);
     
  /* Prikazujemo sadrzaj niza nakon obrtanja */
  for(p = a; p - a < n; p++)
    printf("%d ", *p);    
  printf("\n");
    
  return 0;
}



