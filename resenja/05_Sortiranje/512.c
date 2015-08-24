#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTIKALA 100000

typedef struct art {
  long kod;
  char naziv[20];
  char proizvodjac[20];
  float cena;
} Artikal;

int binarna_pretraga(Artikal a[], int n, long x)
{
  int levi = 0;
  int desni = n - 1;

  /* Dokle god je indeks levi levo od indeksa desni */
  while (levi <= desni) {
    /* Racunamo sredisnji indeks */
    int srednji = (levi + desni) / 2;
    /* Ako je sredisnji element veci od x, tada se x mora
       nalaziti u levoj polovini niza */
    if (x < a[srednji].kod)
      desni = srednji - 1;
    /* Ako je sredisnji element manji od x, tada se x mora
       nalaziti u desnoj polovini niza */
    else if (x > a[srednji].kod)
      levi = srednji + 1;
    else
      /* Ako je sredisnji element jednak x, tada smo pronasli x
         na poziciji srednji */
      return srednji;
  }
  /* Ako nije pronadjen vracamo -1 */
  return -1;
}

void selection_sort(Artikal a[], int n)
{
  int i, j;
  int min;
  Artikal pom;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      /* Sortiranje vrsimo po kodovima i onda i poredjenje
         vrsimo nad kodovoima */
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

  /* Otvaranje datoteke */
  if ((fp = fopen("artikli.txt", "r")) == NULL) {
    fprintf(stderr,
            "Neuspesno otvaranje datoteke artikli.txt.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje artikala */
  i = 0;
  while (fscanf(fp, "%ld %s %s %f", &asortiman[i].kod,
                asortiman[i].naziv, asortiman[i].proizvodjac,
                &asortiman[i].cena) == 4)
    i++;

  /* Zatvaranje datoteke */
  fclose(fp);

  n = i;

  /* Sortiracemo celokupan asortiman prodavnice prema kodovima
     jer ce pri kucanju racuna prodavac unositi kod artikla.
     Prilikom kucanja svakog racuna pretrazuje se asortiman, da
     bi se utvrdila cena artikla. Kucanje racuna obuhvata vise
     pretraga asortimana i u interesu nam je da ta operacija
     bude sto efikasnija. Zelimo da koristimo algoritam binarne
     pretrage priliko pretrazivanje po kodu artikla. Iz tog
     razloga, potrebno je da nam asortiman bude sortiran po
     kodovima i to cemo uraditi primenom selection sort
     algoritma. Sortiramo samo jednom na pocetku, ali zato posle 
     brzo mozemo da pretrazujemo prilikom kucanja proizvoljno
     puno racuna. Vreme koje se utrosi na sortiranje na pocetku
     izvrsavanja programa, kasnije se isplati jer za brojna
     trazenja artikla mozemo umesto linearne da koristimo
     efikasniju binarnu pretragu. */

  selection_sort(asortiman, n);

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
    printf("- Za nov racun unesite kod artikla!\n\n");
    if (scanf("%ld", &kod) == EOF)
      break;

    racun = 0;
    while (1) {
      if ((i = binarna_pretraga(asortiman, n, kod)) == -1) {
        printf
            ("\tGRESKA: Ne postoji proizvod sa trazenim kodom!\n");
      } else {
        printf("\tTrazili ste:\t%s %s %12.2f\n",
               asortiman[i].naziv, asortiman[i].proizvodjac,
               asortiman[i].cena);

        racun += asortiman[i].cena;
      }

      printf("Unesite kod artikla [ili 0 za prekid]: \t");
      scanf("%ld", &kod);

      if (kod == 0)
        break;
    }

    printf("\n\tUKUPNO: %.2lf dinara.\n\n", racun);
  }

  printf("Kraj rada kase!\n");

  exit(EXIT_SUCCESS);
}
