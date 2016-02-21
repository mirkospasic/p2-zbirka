#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

/* Struktura sa svim informacijama o pojedinacnom studentu */
typedef struct {
  char ime[21];
  char prezime[26];
  int prisustvo;
  int zadaci;
} Student;

/* Funkcija za sortiranje niza struktura po prezimenu leksikografski
   rastuce */
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

/* Funkcija za sortiranje niza struktura po ukupnom broju uradjenih
   zadataka opadajuce, a ukoliko neki studenti imaju isti broj
   uradjenih zadataka sortiraju se po duzini imena rastuce. */
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

 /* Funkcija za sortiranje niza struktura opadajuce po broju casova
    na kojima su bili. Ukoliko neki studenti imaju isti broj casova,
    sortiraju se opadajuce po broju uradjenih zadataka, a ukoliko se
    i po broju zadataka poklapaju, njihovo sortiranje ce biti po
    prezimenu opadajuce. */
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

  /* Otvara se datoteka za citanje */
  if ((fp = fopen("aktivnost.txt", "r")) == NULL) {
    fprintf(stderr,
            "Greska: Neupesno otvaranje datoteke aktivnost.txt.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitava se sadrzaj */
  for (i = 0;
       fscanf(fp, "%s%s%d%d", praktikum[i].ime,
              praktikum[i].prezime, &praktikum[i].prisustvo,
              &praktikum[i].zadaci) != EOF; i++);
  /* Zatvara se datoteka */
  fclose(fp);
  br_studenata = i;

  /* Kreira se prvi spisak studenata po prvom kriterijumu */
  sort_ime_leksikografski(praktikum, br_studenata);
  /* Otvara se datoteka za pisanje */
  if ((fp = fopen("dat1.txt", "w")) == NULL) {
    fprintf(stderr,
            "Greska: Neupesno otvaranje datoteke dat1.txt.\n");
    exit(EXIT_FAILURE);
  }
  /* Upisuje se niz u datoteku */
  fprintf
      (fp, "Studenti sortirani po imenu leksikografski rastuce:\n");
  for (i = 0; i < br_studenata; i++)
    fprintf(fp, "%s %s  %d  %d\n", praktikum[i].ime,
            praktikum[i].prezime, praktikum[i].prisustvo,
            praktikum[i].zadaci);
  /* Zatvara se datoteka */
  fclose(fp);

  /* Kreira se drugi spisak studenata po drugom kriterijumu */
  sort_zadatke_pa_imena(praktikum, br_studenata);
  /* Otvara se datoteka za pisanje */
  if ((fp = fopen("dat2.txt", "w")) == NULL) {
    fprintf(stderr,
            "Greska: Neupesno otvaranje datoteke dat2.txt.\n");
    exit(EXIT_FAILURE);
  }
  /* Upisuje se niz u datoteku */
  fprintf(fp, "Studenti sortirani po broju zadataka opadajuce,\n");
  fprintf(fp, "pa po duzini imena rastuce:\n");
  for (i = 0; i < br_studenata; i++)
    fprintf(fp, "%s %s  %d  %d\n", praktikum[i].ime,
            praktikum[i].prezime, praktikum[i].prisustvo,
            praktikum[i].zadaci);
  /* Zatvara se datoteka */
  fclose(fp);

  /* Kreira se treci spisak studenata po trecem kriterijumu */
  sort_prisustvo_pa_zadatke_pa_prezimena(praktikum, br_studenata);
  /* Otvara se datoteka za pisanje */
  if ((fp = fopen("dat3.txt", "w")) == NULL) {
    fprintf(stderr,
            "Greska: Neupesno otvaranje datoteke dat3.txt.\n");
    exit(EXIT_FAILURE);
  }
  /* Upisuje se niz u datoteku */
  fprintf(fp, "Studenti sortirani po prisustvu opadajuce,\n");
  fprintf(fp, "pa po broju zadataka,\n");
  fprintf(fp, "pa po prezimenima leksikografski opadajuce:\n");
  for (i = 0; i < br_studenata; i++)
    fprintf(fp, "%s %s  %d  %d\n", praktikum[i].ime,
            praktikum[i].prezime, praktikum[i].prisustvo,
            praktikum[i].zadaci);
  /* Zatvara se datoteka */
  fclose(fp);

  exit(EXIT_SUCCESS);
}
