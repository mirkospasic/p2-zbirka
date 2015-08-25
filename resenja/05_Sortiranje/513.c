#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

/* Struktura koja nam je neophodna za sve informacije o
   pojedinacnom studentu */
typedef struct {
  char ime[20];
  char prezime[25];
  int prisustvo;
  int zadaci;
} Student;

/* Funkcija kojom sortiramo niz struktura po prezimenu
   leksikografski rastuce */
void sort_ime_leksikografski(Student niz[], int n)
{
  int i, j;
  int min;
  Student pom;

  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (strcmp(niz[j].ime, niz[min].ime) < 0)
        min = j;

    if (min != i) {
      pom = niz[min];
      niz[min] = niz[i];
      niz[i] = pom;
    }
  }
}

/* Funkcija kojom sortiramo niz struktura po ukupnom broju
   uradjenih zadataka opadajuce, ukoliko neki studenti imaju
   isti broj uradjenih zadataka sortiraju se po duzini imena
   rastuce. */
void sort_zadatke_pa_imena(Student niz[], int n)
{
  int i, j;
  int max;
  Student pom;
  for (i = 0; i < n - 1; i++) {
    max = i;
    for (j = i + 1; j < n; j++)
      if (niz[j].zadaci > niz[max].zadaci)
        max = j;
      else if (niz[j].zadaci == niz[max].zadaci
               && strlen(niz[j].ime) < strlen(niz[max].ime))
        max = j;
    if (max != i) {
      pom = niz[max];
      niz[max] = niz[i];
      niz[i] = pom;
    }
  }
}

 /* Funkcija kojom sortiramo niz struktura po broju casova na
    kojima su bili opadajuce, a ukoliko * neki studenti imaju
    isti broj casova, sortiraju se opadajuce po broju uradjenih
    zadataka, * a ukoliko se i po broju zadataka poklapaju
    sortirati ih po prezimenu opadajuce. */
void sort_prisustvo_pa_zadatke_pa_prezimena(Student niz[], int n)
{
  int i, j;
  int max;
  Student pom;
  for (i = 0; i < n - 1; i++) {
    max = i;
    for (j = i + 1; j < n; j++)
      if (niz[j].prisustvo > niz[max].prisustvo)
        max = j;
      else if (niz[j].prisustvo == niz[max].prisustvo
               && niz[j].zadaci > niz[max].zadaci)
        max = j;
      else if (niz[j].prisustvo == niz[max].prisustvo
               && niz[j].zadaci == niz[max].zadaci
               && strcmp(niz[j].prezime, niz[max].prezime) > 0)
        max = j;
    if (max != i) {
      pom = niz[max];
      niz[max] = niz[i];
      niz[i] = pom;
    }
  }
}



int main(int argc, char *argv[])
{
  Student praktikum[MAX];
  int i, br_studenata = 0;

  FILE *fp = NULL;

  /* Otvaranje datoteke za citanje */
  if ((fp = fopen("aktivnost.txt", "r")) == NULL) {
    fprintf(stderr,
            "Neupesno otvaranje datoteke aktivnost.txt.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje sadrzaja */
  for (i = 0;
       fscanf(fp, "%s%s%d%d", praktikum[i].ime,
              praktikum[i].prezime, &praktikum[i].prisustvo,
              &praktikum[i].zadaci) != EOF; i++);

  fclose(fp);
  br_studenata = i;

  /* Kreiramo prvi spisak studenata na kom su sortirani
     leksikografski po imenu rastuce */
  sort_ime_leksikografski(praktikum, br_studenata);
  /* Otvaranje datoteke za pisanje */
  if ((fp = fopen("dat1.txt", "w")) == NULL) {
    fprintf(stderr, "Neupesno otvaranje datoteke dat1.txt.\n");
    exit(EXIT_FAILURE);
  }
  fprintf
      (fp,
       "Studenti sortirani po imenu leksikografski rastuce:\n");
  for (i = 0; i < br_studenata; i++)
    fprintf(fp, "%s %s  %d  %d\n", praktikum[i].ime,
            praktikum[i].prezime, praktikum[i].prisustvo,
            praktikum[i].zadaci);
  fclose(fp);

  /* Na drugom su sortirani po ukupnom broju uradjenih zadataka
     opadajuce, ukoliko neki studenti imaku isti broj uradjenih
     zadataka sortiraju se po duzini imena rastuce. */
  sort_zadatke_pa_imena(praktikum, br_studenata);
  /* Otvaranje datoteke za pisanje */
  if ((fp = fopen("dat2.txt", "w")) == NULL) {
    fprintf(stderr, "Neupesno otvaranje datoteke dat2.txt.\n");
    exit(EXIT_FAILURE);
  }
  fprintf(fp,
          "Studenti sortirani po broju zadataka opadajuce,\n");
  fprintf(fp, "pa po duzini imena rastuce:\n");
  for (i = 0; i < br_studenata; i++)
    fprintf(fp, "%s %s  %d  %d\n", praktikum[i].ime,
            praktikum[i].prezime, praktikum[i].prisustvo,
            praktikum[i].zadaci);
  fclose(fp);

  /* Na trecem spisku su sortirani po broju casova na kojima su
     bili opadajuce, a ukoliko neki studenti imaju isti broj
     casova, sortiraju se opadajuce po broju uradjenih zadataka,
     a ukoliko se i po broju zadataka poklapaju sortirati ih po
     prezimenu opadajuce. */
  sort_prisustvo_pa_zadatke_pa_prezimena(praktikum,
                                         br_studenata);
  /* Otvaranje datoteke za pisanje */
  if ((fp = fopen("dat3.txt", "w")) == NULL) {
    fprintf(stderr, "Neupesno otvaranje datoteke dat3.txt.\n");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "Studenti sortirani po prisustvu opadajuce,\n");
  fprintf(fp, "pa po broju zadataka,\n");
  fprintf(fp, "pa po prezimenima leksikografski opadajuce:\n");
  for (i = 0; i < br_studenata; i++)
    fprintf(fp, "%s %s  %d  %d\n", praktikum[i].ime,
            praktikum[i].prezime, praktikum[i].prisustvo,
            praktikum[i].zadaci);
  fclose(fp);

  return 0;
}