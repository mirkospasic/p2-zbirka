/* Napisati funkciju koja formira listu studenata tako sto se podaci o
   studentima ucitavaju iz datoteke cije se ime zadaje kao argument
   komandne linije. U svakom redu datoteke nalaze se podaci o studentu
   i to broj indeksa, ime i prezime. Napisati rekurzivnu funkciju koja
   odredjuje da li neki student (koji se trazi na osnovu broja indeksa,
   pri cemu se broj indeksa zadaje sa standardnog ulaza) pripada listi
   ili ne. Ispisati zatim odgovarajucu poruku i rekurzivno osloboditi
   memoriju koju je data lista zauzimala.

   Poziv: ./a.out studenti.txt
   Datoteka:			Ulaz:		Izlaz:
   123/2014 Marko Lukic 	3/2014 		da: Ana Sokic
   3/2014 Ana Sokic 		235/2008 	ne
   43/2013 Jelena Ilic 		41/2009 	da: Marija Zaric
   41/2009 Marija Zaric
   13/2010 Milovan Lazic
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INDEKS 10
#define MAX_IME_PREZIME 21

typedef struct _Cvor{
  char broj_indeksa[MAX_INDEKS];
  char ime[MAX_IME_PREZIME];
  char prezime[MAX_IME_PREZIME];
  struct _Cvor *sledeci;
} Cvor;

/*
  pomocna funkcija koja kreira cvor. 
  funkcija vraca pokazivac na novokreirani cvor ili NULL
  ako alokacija nije uspesno izvrsena.  
*/
Cvor *napravi_cvor(char broj_indeksa[], char ime[], char prezime[]){
  Cvor *novi = (Cvor*) malloc(sizeof(Cvor));
  if(novi == NULL)
    return NULL;
  strcpy(novi->broj_indeksa, broj_indeksa);
  strcpy(novi->ime, ime);
  strcpy(novi->prezime, prezime);
  novi->sledeci = NULL;
  return novi;
}

/* 
   funkcija oslobadja dinamicku memoriju zauzetu za elemente liste 
   ciji se pocetni cvor nalazi na adresi glava
*/
void oslobodi_listu(Cvor **glava){
  if(*glava == NULL)
    return;  
  oslobodi_listu( &(*glava)->sledeci);
  free(*glava);
  *glava = NULL;
}

/* 
  funkcija proverava uspesnost alokacije memorije za cvor novi i ukoliko 
  alokacija nije bila uspesna, oslobadja se sva prethodno zauzeta memorija 
  za listu cija pocetni cvor se nalazi na adresi glava  
*/
void proveri_alokaciju(Cvor** glava, Cvor* novi) {
  if(novi == NULL){
    fprintf(stderr, "Neuspela alokacija za nov cvor\n");
    oslobodi_listu(glava);
    exit(EXIT_FAILURE);
  }
}

/* 
  funkcija dodaje novi cvor na pocetak liste. 
  kreira novi cvor koriscenjem funkcije napravi_cvor() i uvezuje ga na pocetak 
*/
void dodaj_na_pocetak_liste(Cvor ** glava, char broj_indeksa[], char ime[], char prezime[]){
  Cvor *novi = napravi_cvor(broj_indeksa, ime, prezime); 
  proveri_alokaciju(glava, novi);
  novi->sledeci = *glava;
  *glava = novi;
}

// funkcija ispisuje sadrzaj liste
void ispisi_listu(Cvor *glava){
  for( ; glava != NULL; glava = glava->sledeci)
    printf("%s %s %s\n", glava->broj_indeksa, glava->ime, glava->prezime);
}

/*
  funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu
  (NULL u suprotnom)
*/
Cvor *pretrazi_listu(Cvor * glava, char broj_indeksa[]){
  if(glava == NULL)
    return NULL;
  if(!strcmp(glava->broj_indeksa, broj_indeksa))
    return glava;
  return pretrazi_listu(glava->sledeci, broj_indeksa);
}

int main(int argc, char **argv){
    
  /* 
   ako je broj argumenata komandne linije razlicit od 2, 
   znaci da je korisnik na pogresan nacin pozvao program i prijavljujemo gresku
 */
  if(argc != 2){
    fprintf(stderr, "Greska! Program se poziva sa: ./a.out naziv_datoteke.txt!\n");
    exit(EXIT_FAILURE);
  }

  FILE *in = NULL;
  in = fopen(argv[1], "r");
  if(in == NULL){
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char ime[MAX_IME_PREZIME], prezime[MAX_IME_PREZIME], broj_indeksa[MAX_INDEKS];
  Cvor *glava = NULL;
  Cvor *trazeni = NULL;

 // ucitavamo listu sa ulaza
  while(fscanf(in, "%s %s %s", broj_indeksa, ime, prezime) != EOF)
    dodaj_na_pocetak_liste(&glava, broj_indeksa, ime, prezime);
    
  //ispisi_listu(glava);
  
  int i = 0, n;
  char brojevi_indeksa[100][MAX_INDEKS];
  while(scanf("%s", brojevi_indeksa[i]) != EOF)
    i++;
  n = i;

  for(i = 0; i < n; i++){
    trazeni = pretrazi_listu(glava, brojevi_indeksa[i]);
    if(trazeni == NULL)
      printf("ne\n");
    else
      printf("da: %s %s\n", trazeni->ime, trazeni->prezime);
  }

  oslobodi_listu(&glava);
  fclose(in);
  return 0;
}
