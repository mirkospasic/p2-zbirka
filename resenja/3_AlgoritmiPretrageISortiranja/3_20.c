#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000
#define MAX_DUZINA 16

/* Struktura koja reprezentuje jednog gradjanina */
typedef struct gr {
  char ime[MAX_DUZINA];
  char prezime[MAX_DUZINA];
} Gradjanin;

/* Funkcija sortira niz gradjana rastuce po imenima */
void sort_ime(Gradjanin a[], int n)
{
  int i, j;
  int min;
  Gradjanin pom;

  for (i = 0; i < n - 1; i++) {
    /* Unutrasnja petlja pronalazi poziciju min, na kojoj se nalazi
       najmanji od elemenata a[i].ime,...,a[n-1].ime. */
    min = i;
    for (j = i + 1; j < n; j++)
      if (strcmp(a[j].ime, a[min].ime) < 0)
        min = j;
    /* Zamena elemenata na pozicijama (i) i min. Ovo se radi samo
       ako su (i) i min razliciti, inace je nepotrebno. */
    if (min != i) {
      pom = a[i];
      a[i] = a[min];
      a[min] = pom;
    }
  }
}

/* Funkcija sortira niz gradjana rastuce po prezimenima */
void sort_prezime(Gradjanin a[], int n)
{
  int i, j;
  int min;
  Gradjanin pom;

  for (i = 0; i < n - 1; i++) {
    /* Unutrasnja petlja pronalazi poziciju min, na kojoj se nalazi
       najmanji od elemenata a[i].prezime,...,a[n-1].prezime. */
    min = i;
    for (j = i + 1; j < n; j++)
      if (strcmp(a[j].prezime, a[min].prezime) < 0)
        min = j;
    /* Zamena elemenata na pozicijama (i) i min. Ovo se radi samo
       ako su (i) i min razliciti, inace je nepotrebno. */
    if (min != i) {
      pom = a[i];
      a[i] = a[min];
      a[min] = pom;
    }
  }
}

/* Pretraga niza gradjana */
int linearna_pretraga(Gradjanin a[], int n, Gradjanin * x)
{
  int i;
  for (i = 0; i < n; i++)
    if (strcmp(a[i].ime, x->ime) == 0
        && strcmp(a[i].prezime, x->prezime) == 0)
      return i;
  return -1;
}


int main()
{
  Gradjanin spisak1[MAX], spisak2[MAX];
  int isti_rbr = 0;
  int i, n;
  FILE *fp = NULL;

  /* Otvaranje datoteke */
  if ((fp = fopen("biracki-spisak.txt", "r")) == NULL) {
    fprintf(stderr,
            "Greska: Neupesno otvaranje datoteke za citanje.\n");
    exit(EXIT_FAILURE);
  }

  /* Citanje sadrzaja */
  for (i = 0;
       fscanf(fp, "%s %s", spisak1[i].ime,
              spisak1[i].prezime) != EOF; i++)
    spisak2[i] = spisak1[i];
  n = i;

  /* Zatvaranje datoteke */
  fclose(fp);

  sort_ime(spisak1, n);

  /*****************************************************************
    Ovaj deo je iskomentarisan jer se u zadatku ne trazi ispis
    sortiranih nizova. Koriscen je samo u fazi testiranja programa.

    printf("Biracki spisak [uredjen prema imenima]:\n");
    for(i=0; i<n; i++)
      printf(" %d. %s %s\n",i,spisak1[i].ime, spisak1[i].prezime);         
  ******************************************************************/

  sort_prezime(spisak2, n);

  /*****************************************************************
    Ovaj deo je iskomentarisan jer se u zadatku ne trazi ispis
    sortiranih nizova. Koriscen je samo u fazi testiranja programa.

    printf("Biracki spisak [uredjen prema prezimenima]:\n");
    for(i=0; i<n; i++)
      printf(" %d. %s %s\n",i,spisak2[i].ime, spisak2[i].prezime);         
  ******************************************************************/

  /* Linearno pretrazivanje nizova */
  for (i = 0; i < n; i++)
    if (i == linearna_pretraga(spisak2, n, &spisak1[i]))
      isti_rbr++;

  /* Alternativno (efikasnije) resenje */
  /*****************************************************************
    for(i=0; i<n ;i++)
      if( strcmp(spisak2[i].ime, spisak1[i].ime) == 0 &&
          strcmp(spisak1[i].prezime, spisak2[i].prezime)==0)
    isti_rbr++;
  ******************************************************************/

  /* Ispis rezultata */
  printf("%d\n", isti_rbr);

  exit(EXIT_SUCCESS);
}
