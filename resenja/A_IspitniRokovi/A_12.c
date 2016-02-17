#include <stdio.h>
#include <stdlib.h>
/* Ime datoteke nije duze od 30 karaktera */
#define MAX 31

/* Funkcija alocira memorijski prostor za matricu sa n vrsta i m
   kolona */
float **alociraj_matricu(int n, int m)
{
  float **matrica = NULL;
  int i, j;

  /* Alocira se prostor za niz vrsta matrice */
  matrica = (float **) malloc(n * sizeof(float *));
  /* Ako alokacija nije prosla uspesno, povratna vrednost funkcije
     ce biti NULL, sto mora biti provereno u main funkciji */
  if (matrica == NULL)
    return NULL;

  /* Alocira se prostor za svaku vrstu matrice */
  for (i = 0; i < n; i++) {
    matrica[i] = (float *) malloc(m * sizeof(float));
    /* Ako alokacija nije prosla uspesno, oslobadjaju se svi
       prethodno alocirani resursi, i povratna vrednost je NULL */
    if (matrica[i] == NULL) {
      for (j = 0; j < i; j++)
        free(matrica[j]);
      free(matrica);
      return NULL;
    }
  }
  return matrica;
}

/* Funkcija oslobadja alocirani memorijski prostor */
float **dealociraj_matricu(float **matrica, int n)
{
  int i;
  /* Oslobadja se prostor rezervisan za svaku vrstu */
  for (i = 0; i < n; i++)
    free(matrica[i]);

  /* Oslobadja se memorija za niz pokazivaca na vrste */
  free(matrica);

  /* Matrica postaje prazna, tj. nealocirana */
  return NULL;
}

/* Funkcija prebrojava koliko se puta pojavljuje broj x u i-toj
   vrsti matrice A, gde je m broj elemenata u vrsti */
int prebroj_u_itoj_vrsti(float **A, int i, int m, int x)
{
  int j;
  int broj = 0;
  for (j = 0; j < m; j++) {
    if (A[i][j] == x)
      broj++;
  }
  return broj;
}

/* Funkcija vraca indeks vrste matrice A u kojoj se realan broj x
   pojavljuje najmanje puta */
int indeks_vrste(float x, float **A, int n, int m)
{
  /* Indeks vrste sa minimalnim brojem pojavljivanja broja x */
  int min;
  /* Broj pojavljivanja broja x u vrsti sa indeksom min */
  int min_broj;
  /* Promenljiva u kojoj ce se racunati broj pojavljivanja broja x u 
     tekucnoj vrsti */
  int broj_u_vrsti;
  /* Pomocne promenljive */
  int i;

  /* Promenljiva min se inicijalizuje na nulu, a min_broj na broj
     pojavljivanja broja x u nultoj vrsti */
  min = 0;
  min_broj = prebroj_u_itoj_vrsti(A, 0, m, x);

  /* Za svaku vrstu (osim nulte) se racuna broj pojavljivanja broja
     x u njoj, pa ukoliko je taj broj manji od trenutno najmanjeg
     azuriraju se promenljive min i min_broj */
  for (i = 1; i < n; i++) {
    broj_u_vrsti = prebroj_u_itoj_vrsti(A, i, m, x);
    if (broj_u_vrsti < min_broj) {
      min_broj = broj_u_vrsti;
      min = i;
    }
  }

  /* Funkcija vraca odgovarajuci indeks vrste */
  return min;
}

int main()
{
  FILE *in;
  char datoteka[MAX];
  float broj;
  float **A = NULL;
  int i, j, m, n;

  /* Sa standardnog ulaza se ucitava ime datoteke i realan broj */
  scanf("%s", datoteka);
  scanf("%f", &broj);

  /* Otvaranje datoteke za citanje */
  in = fopen(datoteka, "r");

  /* Provera da li je datoteka uspesno otvorena */
  if (in == NULL) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Dimenzije matrice se ucitavaju iz datoteke (prva dva cela broja
     u datoteci). U slucaju neuspesnog ucitavanja, na standardni
     izlaz za greske se ispisuje -1 i prekida se program. */
  if (fscanf(in, "%d %d", &n, &m) == EOF) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Provera da li su ucitani brojevi m i n pozitivni */
  if (n <= 0 || m <= 0) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Alokacija matrice */
  A = alociraj_matricu(n, m);

  /* Provera da li je alokacija uspela */
  if (A == NULL) {
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje elemenata matrice iz datoteke */
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      fscanf(in, "%f", &A[i][j]);
  }

  /* Zatvaranje datoteke */
  fclose(in);

  /* Ispisivanje rezultata poziva funkcije */
  printf("%d\n", indeks_vrste(broj, A, n, m));

  /* Oslobadjanje memorije koju je zauzimala matrica */
  A = dealociraj_matricu(A, n);

  exit(EXIT_SUCCESS);
}
