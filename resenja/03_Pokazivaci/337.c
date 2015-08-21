#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Funkcija izvrsava trazene transformacije nad matricom */
void izmeni (float** a, int n) 
{
  int i, j;
  
  for(i=0; i<n; i++)    
    for(j=0; j<n; j++)         
	/* Ako je indeks vrste manji od indeksa kolone */
	if(i<j)	  
	  /* element se nalazi iznad glavne dijagonale 
	     pa ga polovimo */
	    a[i][j]/=2;	 	
	else
	  /* Ako je indeks vrste veci od indeksa kolone */
	  if(i>j)	    
	    /* element se nalazi ispod glavne dijagonale 
		   pa ga dupliramo*/
	    a[i][j] *= 2; 
}

/* Funkcija izracunava zbir apsolutnih vrednosti elemenata ispod 
   sporedne dijagonale */
float zbir_ispod_sporedne_dijagonale(float** m, int n) 
{
  int i, j;
  float zbir=0;
  
  for(i=0; i<n; i++)   
    for(j=0; j<n; j++)         
      /* Ukoliko je zbir indeksa vrste i indeksa kolone 
         elementa veci od n-1, to znaci da se element nalazi 
         ispod sporedne dijagonale */
      if(i+j>n-1)
	    zbir+=fabs(m[i][j]);	      
 
  return zbir;  
}

/* Funkcija ucitava elemente kvadratne matrice dimenzije n 
   iz zadate datoteke */
void ucitaj_matricu(FILE* ulaz, float** m, int n) {
  int i, j;
  
  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      fscanf(ulaz, "%f", &m[i][j]);
}

/* Funkcija ispisuje elemente kvadratne matrice dimenzije n 
   na standardni izlaz */
void ispisi_matricu(float** m, int n) {
  int i, j;
  
  for(i=0; i<n; i++){
    for(j=0; j<n; j++)
      printf("%.2f ", m[i][j]); 
    printf("\n");
  }
}

/* Funkcija alocira memoriju za kvadratnu matricu dimenzije n */
float** alociraj_memoriju(int n) {
  int i, j;
  float** m;
  
  m = (float**) malloc(n * sizeof(float*));
  if(m == NULL) {
    fprintf(stderr,"malloc(): Neuspela alokacija\n");
    exit(EXIT_FAILURE);   
  }

  /* Za svaku vrstu matrice */
  for(i=0; i<n; i++) {    
    /* Alociramo memoriju */
    m[i] = (float*) malloc(n * sizeof(float));
    
    /* Proveravamo da li je doslo do greske pri alokaciji */
    if(m[i] == NULL) {
      /* Ako jeste, ispisujemo poruku */
      printf("malloc(): neuspela alokacija memorije!\n");
      
      /* Oslobadjamo memoriju zauzetu do ovog koraka */
      for(j=0; j<i; j++)
	    free(m[i]);	
      free(m);      
      exit(EXIT_FAILURE);
    }    
  }
  return m;
}

/* Funckija oslobadja memoriju zauzetu kvadratnom matricom 
   dimenzije n */
void oslobodi_memoriju(float** m, int n) 
{
  int i;
  
  for(i=0; i<n; i++)
    free(m[i]); 
  free(m);
}

int main(int argc, char* argv[]) 
{
  FILE* ulaz;
  float** a;
  int n;
  
 /* Ako korisnik nije uneo trazene argumente, 
     prijavljujemo gresku */
  if(argc < 2) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s ime_dat.\n", argv[0]);
    exit(EXIT_FAILURE);
  }
    
  /* Otvaramo datoteku za citanje */
  ulaz = fopen(argv[1], "r");
  if(ulaz == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke %s.\n", 
	                                            argv[1]);
    exit(EXIT_FAILURE);
  }
  
  /* citamo dimenziju matrice */
  fscanf(ulaz, "%d", &n);
  
  /* Alociramo memoriju */
  a = alociraj_memoriju(n);
  
  /* Ucitavamo elemente matrice */
  ucitaj_matricu(ulaz, a, n);
  
  float zbir = zbir_ispod_sporedne_dijagonale(a, n);
  
  /* Pozivamo funkciju za modifikovanje elemenata */
  izmeni(a, n);
  
  /* Ispisujemo rezultat */
  printf("Zbir apsolutnih vrednosti ispod sporedne dijagonale ");
  printf("je %.2f.\n", zbir);
  
  printf("Transformisana matrica je:\n");
  ispisi_matricu(a,n);
  
  /* Oslobadjamo memoriju */
  oslobodi_memoriju(a, n);
  
  /* Zatvaramo datoteku */  
  fclose(ulaz);
  
  /* i prekidamo sa izvrsavanjem programa */
  return 0;
}
