/* Napisati program koji prebrojava pojavljivanja etiketa (bez
   atributa) HTML datoteke cije se ime zadaje kao argument komandne
   linije. Sadrzaj rezultujuce liste ispisati na standardni izlaz. Za
   formirianje liste koristiti strukturu:

   typedef struct _Element
   {
	unsigned broj_pojavljivanja;
	char etiketa[20];
	struct _Element *sledeci;
   } Element;

   Poziv: ./a.out datoteka.html
   Datoteka.html:					Izlaz:
   <html>						a - 4
     <head><title>Primer</title></head>			br - 1
     <body>						h1 - 2
       <h1>Naslov</h1>					body - 2
       Danas je lep i suncan dan. <br>			title - 2
       A sutra ce biti jos lepsi.			head - 2
       <a link="http://www.google.com"> Link 1</a>	html - 2
       <a link="http://www.math.rs"> Link 2</a>
     </body>
   </html>
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_DUZINA 20 

typedef struct _Element{
  unsigned broj_pojavljivanja;
  char etiketa[20];
  struct _Element *sledeci;
} Element;

/*
  pomocna funkcija koja kreira cvor. 
  funkcija vraca pokazivac na novokreirani cvor ili NULL
  ako alokacija nije uspesno izvrsena.  
*/
Element *napravi_cvor(unsigned br, char etiketa[]){
  Element *novi = (Element*) malloc(sizeof(Element));
  if(novi == NULL)
    return NULL;
  novi->broj_pojavljivanja = br;
  strcpy(novi->etiketa, etiketa);
  novi->sledeci = NULL;
  return novi;
}

/* 
   funkcija oslobadja dinamicku memoriju zauzetu za elemente liste 
   ciji se pocetni cvor nalazi na adresi glava
*/
void oslobodi_listu(Element **glava){
  Element *pomocni = NULL;
  while(*glava != NULL){
    pomocni = (*glava)->sledeci;
    free(*glava);
    *glava = pomocni;
  }
}

/* 
  funkcija proverava uspesnost alokacije memorije za cvor novi i ukoliko 
  alokacija nije bila uspesna, oslobadja se sva prethodno zauzeta memorija 
  za listu cija pocetni cvor se nalazi na adresi glava  
*/
void provera_alokacije(Element *novi, Element **glava){
  if(novi == NULL){
    fprintf(stderr, "malloc() greska u funkciji napravi_cvor()!\n");
    oslobodi_listu(glava);
    exit(EXIT_FAILURE);
  }
}

/* 
  funkcija dodaje novi cvor na pocetak liste. 
  kreira novi cvor koriscenjem funkcije napravi_cvor() i uvezuje ga na pocetak 
*/
void dodaj_na_pocetak_liste(Element **glava, unsigned br, char etiketa[]){
  Element *novi = napravi_cvor(br, etiketa);
  provera_alokacije(novi, glava);
  novi->sledeci = *glava;
  *glava = novi;
}

/*
  funkcija vraca cvor koji kao vrednost sadrzi trazenu etiketu
  (NULL u suprotnom)
*/
Element *pretrazi_listu(Element *glava, char etiketa[]){
  Element *tekuci;
  for(tekuci = glava; tekuci != NULL; tekuci = tekuci->sledeci)
    if(strcmp(tekuci->etiketa, etiketa) == 0)
      return tekuci;
  return NULL;
}

// funkcija ispisuje sadrzaj liste
void ispisi_listu(Element *glava){
  for( ; glava != NULL; glava = glava->sledeci)
    printf("%s - %u\n", glava->etiketa, glava->broj_pojavljivanja);
}

int main(int argc, char **argv){

/* 
   ako je broj argumenata komandne linije razlicit od 2, 
   znaci da je korisnik na pogresan nacin pozvao program i prijavljujemo gresku
 */
  if(argc != 2){
    fprintf(stderr, "Greska! Program se poziva sa: ./a.out datoteka.html!\n");
    exit(EXIT_FAILURE);
  }

  FILE *in = NULL;
  in = fopen(argv[1], "r");
  if(in == NULL){
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char c;
  int i = 0;
  char a[MAX_DUZINA];

  Element *glava = NULL; 
  Element *trazeni = NULL;

  while((c = fgetc(in)) != EOF){

    if(c == '<'){ 

    // etiketa je u okviru zatvorenog taga 
      if ((c = fgetc(in)) == '/'){
        i = 0; 
        while((c = fgetc(in)) != '>')
          a[i++] = c;
      }

    // etiketa je u okrviru otvorenog taga */
      else{
        i = 0; // u novu nisku ucitavamo od 0. karaktera
	    a[i++] = c; // karakter koji je ucitan, a nije '/'
        while((c = fgetc(in)) != ' ' && c != '>')
          a[i++] = c;
      }    
      a[i] = '\0';
      
    /* 
       ispitujemo da li medju do sada formiranim cvorovima 
       postoji cvor sa ucitanom etiketom
     */
      trazeni = pretrazi_listu(glava, a);

      // ukoliko ne postoji, dodajemo novi cvor za ucitanu etiketu (broj pojave postavljamo na 1)
      if(trazeni == NULL) 
             dodaj_na_pocetak_liste(&glava, 1, a);
      // ukoliko postoji, broj pojave te etikete povecavamo za 1
      else
        trazeni->broj_pojavljivanja++;
    }
  }

  ispisi_listu(glava);
  oslobodi_listu(&glava);

  fclose(in);
  return 0;
}
