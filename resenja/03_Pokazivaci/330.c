#include <stdio.h>
#include <stdlib.h>
#define KORAK 10

int main(void) 
{
  /* Adresa prvog alociranog bajta*/
  int* a = NULL;
  
  /* Velicina alocirane memorije  */
  int alocirano;  
  
  /* Broj elemenata niza */
  int n;  
  
  /* Broj koji se ucitava sa ulaza */
  int x;  
  int i;
  int* b = NULL;
  
  /* Inicijalizacija */
  alocirano = n = 0;

  /* Unosimo brojeve sa ulaza */  
  scanf("%d", &x);

  /* Sve dok je procitani broj razlicit od nule... */
  while(x!=0) { 
  
    /* Ako broj ucitanih elemenata niza odgovara broju 
       alociranih mesta, za smestanje novog elementa treba 
       obezbediti dodatni prostor. Da se ne bi za svaki sledeci 
       element pojedinacno alocirala memorija, prilikom 
       alokacije se vrsi rezervacija za jos KORAK dodatnih 
       mesta za buduce elemente */
    if(n == alocirano) {
      /* Povecava se broj alociranih mesta */
      alocirano = alocirano + KORAK; 
        
      /* Vrsi se realokacija memorije sa novom velicinom */   
      /********************************************************/
      /* Resenje sa funkcijom malloc() */
      /********************************************************/
      /* Vrsi se alokacija memorije sa novom velicinom, a adresa 
         pocetka novog memorijskog bloka se cuva u 
         promenljivoj b */
      b = (int*) malloc (alocirano * sizeof(int));

      /* Ako prilikom alokacije dodje do neke greske */
      if(b == NULL) {
        /* poruku ispisujemo na izlaz za greske */
        fprintf(stderr, "malloc(): ");
        fprintf(stderr, "greska pri alokaciji memorije.\n");	
                    
        /* Pre kraja programa moramo svu dinamicki alociranu 
           memoriju da oslobodimo. U ovom slucaju samo memoriju 
           na adresi a */
        free(a);
                
        /* Zavrsavamo program */
        exit(EXIT_FAILURE);
      }

      /* Svih n elemenata koji pocinju na adresi a prepisujemo
         na novu aderesu b */
      for(i = 0; i < n; i++)
        b[i] = a[i];

      /* Posle prepisivanja oslobadjamo blok memorije sa pocetnom 
         adresom u a */
      free(a);

      /* Promenljivoj a dodeljujemo adresu pocetka novog, veceg 
         bloka koji je prilikom alokacije zapamcen u 
         promenljivoj b */
      a = b;
	  
      /********************************************************/
      /* Resenje sa funkcijom realloc() */
      /********************************************************/
      /* Zbog funkcije realloc je neophodno da i u prvoj 
         iteraciji "a" bude inicijalizovano na NULL */
      /*
      a = (int*) realloc(a,alocirano*sizeof(int));
      
      if(a == NULL) {	  
        fprintf(stderr, "realloc(): ");
        fprintf(stderr, "greska pri alokaciji memorije.\n");    
        exit(EXIT_FAILURE);
      }
      */
    }
	
    /* Smestamo element u niz */
    a[n++] = x;

    /* i ucitavamo sledeci element */
    scanf("%d", &x);
  }

  /* Ispisujemo brojeve u obrnutom poretku */
  for(n--; n>=0; n--)
    printf("%d ", a[n]);
  printf("\n");
  
  /* Oslobadjamo dinamicki alociranu memoriju */
  free(a);

  /* Program se zavrsava */
  exit(EXIT_SUCCESS); 
}

 
