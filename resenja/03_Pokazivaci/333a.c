#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32

/* Struktura koja opisuje jednu pesmu */
typedef struct {
  char izvodjac[MAX];
  char naslov[MAX];
  int broj_gledanja;
} Pesma;

/* Funkcija za uporedjivanje pesama po broju gledanosti 
  (potrebna za rad qsort funkcije) */
int uporedi_gledanost(const void* pp1, const void* pp2) 
{
  Pesma* p1 = (Pesma*) pp1;
  Pesma* p2 = (Pesma*) pp2;
  
  return p2->broj_gledanja-p1->broj_gledanja;
}

/* Funkcija za uporedjivanje pesama po naslovu 
  (potrebna za rad qsort funkcije) */
int uporedi_naslove(const void* pp1, const void* pp2) 
{
  Pesma* p1 = (Pesma*) pp1;
  Pesma* p2 = (Pesma*) pp2;
  
  return strcmp(p1->naslov, p2->naslov);
}

/* Funkcija za uporedjivanje pesama po izvodjacu 
  (potrebna za rad qsort funkcije) */
int uporedi_izvodjace(const void* pp1, const void* pp2) 
{
  Pesma* p1 = (Pesma*) pp1;
  Pesma* p2 = (Pesma*) pp2;
  
  return strcmp(p1->izvodjac, p2->izvodjac);
}

int main(int argc, char* argv[]) 
{
  FILE* ulaz;
  Pesma* pesme;
  int i, n;
  int duzina_naslova;
  
  /* Pripremamo datoteku za citanje */
  ulaz = fopen("pesme.txt", "r");
  if(ulaz == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke.\n");
    exit(EXIT_FAILURE);   
  }
  
  /* citamo informaciju o broju pesama */
  fscanf(ulaz, "%d", &n);
  
  /* Alociramo memoriju za niz pesama */
  pesme = (Pesma*) malloc(n * sizeof(Pesma));
  if(pesme == NULL) {
    printf("malloc(): neuspela alokacija!\n");
    exit(EXIT_FAILURE); 
  }
  
  /* Ucitavamo informacije o pesmama */
  for(i=0; i<n; i++) {
    fscanf(ulaz, "%s - %s %d", pesme[i].izvodjac, 
	        pesme[i].naslov, &pesme[i].broj_gledanja);
			
    /* Eliminisemo zarez koji smo procitali uz naslov */
    duzina_naslova = strlen(pesme[i].naslov);
	
    pesme[i].naslov[duzina_naslova-1] = '\0';    
  }
  
  /* Zatvaramo datoteku jer nam vise nece trebati */
  fclose(ulaz);
  
  /* Analiziramo argumente komandne linije */
  if(argc == 1)     
	/* Nema dodatnih opcija - sortiramo po broju gledanja */
	qsort(pesme, n, sizeof(Pesma), uporedi_gledanost);
  else if(argc == 2 && strcmp(argv[1], "-n") == 0)
	  /* sortiramo po naslovu */
	  qsort(pesme, n, sizeof(Pesma), uporedi_naslove);
  else if(argc == 2 && strcmp(argv[1], "-i") == 0)
      /* sortiramo po izvodjacu */
      qsort(pesme, n, sizeof(Pesma), uporedi_izvodjace);
  else {	 
    fprintf(stderr, "Nedozvoljeni argument komandne linije!\n");
    free(pesme);
    exit(EXIT_FAILURE); 
  } 
  
  /* Ispisujemo rezultat */
  for(i=0; i<n; i++)
    printf("%s - %s, %d\n", pesme[i].izvodjac, pesme[i].naslov, 
	                                     pesme[i].broj_gledanja);    
  
  /* Oslobadjamo memoriju */
  free(pesme);
  
  /* Prekidamo izvrsavanje programa */
  return 0;  
}
