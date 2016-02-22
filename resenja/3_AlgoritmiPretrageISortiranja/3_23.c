#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTIKALA 100000

/* Struktura koja predstavlja jedan artikal */
typedef struct art {
  long kod;
  char naziv[20];
  char proizvodjac[20];
  float cena;
} Artikal;

/* Funkcija koja u nizu artikala binarnom pretragom nalazi onaj sa
   trazenim bar kodom */
int binarna_pretraga(Artikal a[], int n, long x)
{
  int levi = 0;
  int desni = n - 1;

  /* Dokle god je indeks levi levo od indeksa desni */
  while (levi <= desni) {
    /* Racuna se sredisnji indeks */
    int srednji = (levi + desni) / 2;
    /* Ako je sredisnji element veci od trazenog, tada se trazeni
       mora nalaziti u levoj polovini niza */
    if (x < a[srednji].kod)
      desni = srednji - 1;
    /* Ako je sredisnji element manji od trazenog, tada se trazeni
       mora nalaziti u desnoj polovini niza */
    else if (x > a[srednji].kod)
      levi = srednji + 1;
    else
      /* Ako je sredisnji element jednak trazenom, tada je artikal
         sa bar kodom x pronadjen na poziciji srednji */
      return srednji;
  }
  /* Ako nije pronadjen artikal za trazenim bar kodom, vraca se -1 */
  return -1;
}

/* Funkcija koja sortira niz artikala po bar kodovima rastuce */
void selection_sort(Artikal a[], int n)
{
  int i, j;
  int min;
  Artikal pom;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (a[j].kod < a[min].kod)
        min = j;
    if (min != i) {
      pom = a[i];
      a[i] = a[min];
      a[min] = pom;
    }
  }
}

int main()
{
  Artikal asortiman[MAX_ARTIKALA];
  long kod;
  int i, n;
  float racun;
  FILE *fp = NULL;

  /* Otvara se datoteka */
  if ((fp = fopen("artikli.txt", "r")) == NULL) {
    fprintf(stderr,
            "Greska: Neuspesno otvaranje datoteke artikli.txt.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavaju se artikali */
  i = 0;
  while (fscanf(fp, "%ld %s %s %f", &asortiman[i].kod,
                asortiman[i].naziv, asortiman[i].proizvodjac,
                &asortiman[i].cena) == 4)
    i++;

  /* Zatvara se datoteka */
  fclose(fp);

  n = i;

  /* Sortira se celokupan asortiman prodavnice prema kodovima jer
     ce pri kucanju racuna prodavac unositi kod artikla. Prilikom
     kucanja svakog racuna pretrazuje se asortiman, da bi se
     utvrdila cena artikla. Kucanje racuna obuhvata vise pretraga
     asortimana i cilj je da ta operacija bude sto efikasnija.
     Zato se koristi algoritam binarne pretrage prilikom
     pretrazivanja po kodu artikla. Iz tog razloga, potrebno je da
     asortiman bude sortiran po kodovima i to ce biti uradjeno
     primenom selection sort algoritma. Sortiranje se vrsi samo
     jednom na pocetku, ali se zato posle artikli mogu brzo
     pretrazivati prilikom kucanja proizvoljno puno racuna. Vreme
     koje se utrosi na sortiranje na pocetku izvrsavanja programa,
     kasnije se isplati jer se za brojna trazenja artikla umesto
     linearne moze koristiti efikasnija binarna pretraga. */
  selection_sort(asortiman, n);

  /* Ispis stanja u prodavnici */
  printf
      ("Asortiman:\nKOD                Naziv artikla     Ime proizvodjaca       Cena\n");
  for (i = 0; i < n; i++)
    printf("%10ld %20s %20s %12.2f\n", asortiman[i].kod,
           asortiman[i].naziv, asortiman[i].proizvodjac,
           asortiman[i].cena);

  kod = 0;
  while (1) {
    printf("---------------------------\n");
    printf("- Za kraj za kraj rada kase, pritisnite CTRL+D!\n");
    printf("- Za nov racun unesite kod artikla:\n\n");
    /* Unos bar koda provog artikla sledeceg kupca */
    if (scanf("%ld", &kod) == EOF)
      break;
    /* Trenutni racun novog kupca */
    racun = 0;
    /* Za sve artikle trenutnog kupca */
    while (1) {
      /* Vrsi se njihov pronalazak u nizu */
      if ((i = binarna_pretraga(asortiman, n, kod)) == -1) {
        printf
            ("\tGreska: Ne postoji proizvod sa trazenim kodom!\n");
      } else {
        printf("\tTrazili ste:\t%s %s %12.2f\n",
               asortiman[i].naziv, asortiman[i].proizvodjac,
               asortiman[i].cena);
        /* I dodaje se cena na ukupan racun */
        racun += asortiman[i].cena;
      }
      /* Unos bar koda sledeceg artikla trenutnog kupca, ili 0 ako
         on nema vise artikla */
      printf("Unesite kod artikla [ili 0 za prekid]: \t");
      scanf("%ld", &kod);
      if (kod == 0)
        break;
    }
    /* Stampa se ukupan racun trenutnog kupca */
    printf("\n\tUKUPNO: %.2lf dinara.\n\n", racun);
  }

  printf("Kraj rada kase!\n");

  exit(EXIT_SUCCESS);
}
