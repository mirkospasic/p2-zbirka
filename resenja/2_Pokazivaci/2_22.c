#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Funkcija izvrsava trazene transformacije nad matricom */
void izmeni(float **a, int n)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (i < j)
        a[i][j] /= 2;
      else if (i > j)
        a[i][j] *= 2;
}

/* Funkcija izracunava zbir apsolutnih vrednosti elemenata ispod
   sporedne dijagonale. Element se nalazi ispod sporedne dijagonale
   ukoliko je zbir indeksa vrste i indeksa kolone elementa veci od
   n-1 */
float zbir_ispod_sporedne_dijagonale(float **m, int n)
{
  int i, j;
  float zbir = 0;

  for (i = 0; i < n; i++)
    for (j = n - i; j < n; j++)
      if (i + j > n - 1)
        zbir += fabs(m[i][j]);

  return zbir;
}

/* Funkcija ucitava elemente kvadratne matrice dimenzije n x n iz
   zadate datoteke */
void ucitaj_matricu(FILE * ulaz, float **m, int n)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fscanf(ulaz, "%f", &m[i][j]);
}

/* Funkcija ispisuje elemente kvadratne matrice dimenzije n x n na
   standardni izlaz */
void ispisi_matricu(float **m, int n)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%.2f ", m[i][j]);
    printf("\n");
  }
}

/* Funkcija alocira memoriju za kvadratnu matricu dimenzije n x n */
float **alociraj_memoriju(int n)
{
  int i, j;
  float **m;

  m = (float **) malloc(n * sizeof(float *));
  if (m == NULL) {
    fprintf(stderr, "Greska: Neupesna alokacija memorije.\n");
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < n; i++) {
    m[i] = (float *) malloc(n * sizeof(float));

    if (m[i] == NULL) {
      fprintf(stderr, "Greska: Neupesna alokacija memorije.\n");
      for (j = 0; j < i; j++)
        free(m[i]);
      free(m);
      exit(EXIT_FAILURE);
    }
  }
  return m;
}

/* Funkcija oslobadja memoriju zauzetu kvadratnom matricom
   dimenzije n x n */
void oslobodi_memoriju(float **m, int n)
{
  int i;

  for (i = 0; i < n; i++)
    free(m[i]);
  free(m);
}

int main(int argc, char *argv[])
{
  FILE *ulaz;
  float **a;
  int n;

  /* Ukoliko korisnik nije uneo trazene argumente, prijavljuje se
     greska */
  if (argc < 2) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s ime_dat.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvara se datoteka za citanje */
  ulaz = fopen(argv[1], "r");
  if (ulaz == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Cita se dimenzija matrice */
  fscanf(ulaz, "%d", &n);

  /* Rezervise se memorija */
  a = alociraj_memoriju(n);

  /* Ucitavaju se elementi matrice */
  ucitaj_matricu(ulaz, a, n);

  float zbir = zbir_ispod_sporedne_dijagonale(a, n);

  /* Poziva se funkcija za transformaciju matrice */
  izmeni(a, n);

  /* Ispisuju se rezultati */
  printf("Zbir apsolutnih vrednosti ispod sporedne dijagonale ");
  printf("je %.2f.\n", zbir);

  printf("Transformisana matrica je:\n");
  ispisi_matricu(a, n);

  /* Oslobadja se memorija */
  oslobodi_memoriju(a, n);

  /* Zatvara se datoteka */
  fclose(ulaz);

  exit(EXIT_SUCCESS);
}
