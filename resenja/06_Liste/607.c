/* Napisati program koji objedinjuje dve sortirane liste. Funkcija ne
   treba da kreira nove cvorove, vec da samo postojece cvorove
   preraspodeli. Prva lista se ucitava iz datoteke koja se zadaje kao
   prvi argument komandne linije, a druga iz druge. Rezultujucu listu
   ispisati na standardni izlaz.

   Poziv:    ./a.out dat1.txt dat2.txt
   dat1.txt: 2 4 6 10 15
   dat2.txt: 5 6 11 12 14 16
   Izlaz:    2 4 5 6 6 10 11 12 14 15 16
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct _Cvor{
  int broj;
  struct _Cvor *sledeci;
} Cvor;

/*
  pomocna funkcija koja kreira cvor. 
  funkcija vraca pokazivac na novokreirani cvor ili NULL
  ako alokacija nije uspesno izvrsena.  
*/
Cvor *napravi_cvor(int br){
  Cvor *novi = (Cvor*) malloc(sizeof(Cvor));
  if(novi == NULL)
    return NULL;
  novi->broj = br;
  novi->sledeci = NULL;
  return novi;
}

/* 
   funkcija oslobadja dinamicku memoriju zauzetu za elemente liste 
   ciji se pocetni cvor nalazi na adresi glava
*/
void oslobodi_listu(Cvor **glava){
  Cvor *pomocni = NULL;
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
void proveri_alokaciju(Cvor** glava, Cvor* novi){
  if(novi == NULL){
    fprintf(stderr, "Neuspela alokacija za nov cvor\n");
    oslobodi_listu(glava);
    exit(EXIT_FAILURE);
  }
}

// funkcija ispisuje sadrzaj liste
void ispisi_listu(Cvor *glava){
  for( ; glava != NULL; glava = glava->sledeci)
    printf("%d ", glava->broj);
  putchar('\n');
}

// funkcija vraca poslednji cvor u listi
Cvor* pronadji_poslednji(Cvor* glava){
  if(glava == NULL)
    return NULL;
  while(glava->sledeci != NULL)
    glava = glava->sledeci;
  return glava;
}

// funkcija dodaje novi cvor na kraj liste
void dodaj_na_kraj(Cvor ** adresa_glave, int broj){
  Cvor *novi = napravi_cvor(broj);
  proveri_alokaciju(adresa_glave, novi);
  if(*adresa_glave == NULL){
    *adresa_glave = novi; 
    return;
  }
  Cvor* poslednji = pronadji_poslednji(*adresa_glave);
  poslednji->sledeci = novi;
}

/* 
   funkcija objedinjuje dve sortirane liste u jednu sortiranu listu
   koju vraca kao rezultat
*/
Cvor *objedini(Cvor **glava1, Cvor **glava2){

  Cvor *l3 = NULL;
  Cvor **tek = &l3;

  if(*glava1 == NULL && *glava2 == NULL)
    return NULL;

 // ako je prva lista prazna, onda je rezultat druga lista
  if(*glava1 == NULL)
    return *glava2; 

  // ako je druga lista prazna, onda je rezultat prva lista
  if(*glava2 == NULL)
    return *glava1; 

// l3 pokazuje na pocetak nove liste, tj. na manji od brojeva glave1 i glave2
  l3 = ((*glava1)->broj < (*glava2)->broj) ? *glava1 : *glava2;


  while(*glava1 != NULL && *glava2 != NULL){
    if((*glava1)->broj < (*glava2)->broj){
      *tek = *glava1;
      *glava1 = (*glava1)->sledeci;
    }
    else{
      *tek = *glava2;
      *glava2 = (*glava2)->sledeci;
    }
    tek = &((*tek)->sledeci);
  }

 /*
  ukoliko smo izasli iz petlje zato sto smo stigli do kraja prve liste
  onda na rezultujucu listu nadovezujemo ostatak druge liste
 */
 if(*glava1 == NULL)
    *tek = *glava2; 

  else if(*glava2 == NULL)
    *tek = *glava1; 

  return l3;

}

int main(int argc, char **argv){

  /* 
   ako je broj argumenata komandne linije razlicit od 3, 
   znaci da je korisnik na pogresan nacin pozvao program i prijavljujemo gresku
 */
  if(argc != 3){
    fprintf(stderr, "Greska! Program se poziva sa: ./a.out dat1.txt dat2.txt!\n");
    exit(EXIT_FAILURE);
  }

  FILE *in1 = NULL;
  in1 = fopen(argv[1], "r");
  if(in1 == NULL){
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  FILE *in2 = NULL;
  in2 = fopen(argv[2], "r");
  if(in2 == NULL){
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s.\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  int broj;
  Cvor *glava1 = NULL;
  Cvor *glava2 = NULL;
  Cvor *l3 = NULL;

  // ucitavamo dve sortirane liste...
  while(fscanf(in1, "%d", &broj) != EOF)
    dodaj_na_kraj(&glava1, broj);
  while(fscanf(in2, "%d", &broj) != EOF)
    dodaj_na_kraj(&glava2, broj); 
  
  // ...objedinjujemo ih u jednu sortiranu listu...
  l3 = objedini(&glava1, &glava2);
  
  //...koju ispisujemo na standardni izlaz
  ispisi_listu(l3);
  oslobodi_listu(&l3);

  fclose(in1);
  fclose(in2);
  return 0;
}
