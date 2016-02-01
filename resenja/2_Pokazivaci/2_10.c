#include <stdio.h>
#include <stdlib.h>

#define MAX 64

/* Funkcija proverava da li je relacija refleksivna. Relacija je
   refleksivna ako je svaki element u relaciji sa sobom, odnosno ako
   se u matrici relacije na glavnoj dijagonali nalaze jedinice */
int refleksivnost(int m[][MAX], int n)
{
  int i;

  for (i = 0; i < n; i++) {
    if (m[i][i] != 1)
      return 0;
  }

  return 1;
}

/* Funkcija odredjuje refleksivno zatvorenje zadate relacije. Ono je
   odredjeno matricom koja sadrzi sve elemente polazne matrice
   dopunjene jedinicama na glavnoj dijagonali */
void ref_zatvorenje(int m[][MAX], int n, int zatvorenje[][MAX])
{
  int i, j;

  /* Prepisuju se vrednosti elemenata pocetne matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      zatvorenje[i][j] = m[i][j];

  /* Na glavnoj dijagonali se postavljaju jedinice */
  for (i = 0; i < n; i++)
    zatvorenje[i][i] = 1;
}

/* Funkcija proverava da li je relacija simetricna. Relacija je
   simetricna ako za svaki par elemenata vazi: ako je element "i" u
   relaciji sa elementom "j", onda je i element "j" u relaciji sa
   elementom "i". Ovakve matrice su simetricne u odnosu na glavnu
   dijagonalu */
int simetricnost(int m[][MAX], int n)
{
  int i, j;

  /* Obilaze se elementi ispod glavne dijagonale matrice i uporedjuju 
     se sa njima simetricnim elementima */
  for (i = 0; i < n; i++)
    for (j = 0; j < i; j++)
      if (m[i][j] != m[j][i])
        return 0;

  return 1;
}

/* Funkcija odredjuje simetricno zatvorenje zadate relacije. Ono je
   odredjeno matricom koja sadrzi sve elemente polazne matrice
   dopunjene tako da matrica postane simetricna u odnosu na glavnu
   dijagonalu */
void sim_zatvorenje(int m[][MAX], int n, int zatvorenje[][MAX])
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      zatvorenje[i][j] = m[i][j];

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (zatvorenje[i][j] == 1)
        zatvorenje[j][i] = 1;
}


/* Funkcija proverava da li je relacija tranzitivna. Relacija je
   tranzitivna ako ispunjava sledece svojstvo: ako je element "i" u
   relaciji sa elementom "j" i element "j" u relaciji sa elementom
   "k", onda je i element "i" u relaciji sa elementom "k" */
int tranzitivnost(int m[][MAX], int n)
{
  int i, j, k;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      /* Ispituje se da li postoji element koji narusava *
         tranzitivnost */
      for (k = 0; k < n; k++)
        if (m[i][k] == 1 && m[k][j] == 1 && m[i][j] == 0)
          return 0;

  return 1;
}


/* Funkcija odredjuje refleksivno-tranzitivno zatvorenje zadate
   relacije koriscenjem Varsalovog algoritma */
void ref_tran_zatvorenje(int m[][MAX], int n, int zatvorenje[][MAX])
{
  int i, j, k;

  /* Prepisuju se vrednosti elemenata pocetne matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      zatvorenje[i][j] = m[i][j];

  /* Odredjuje se reflektivno zatvorenje matrice */
  for (i = 0; i < n; i++)
    zatvorenje[i][i] = 1;

  /* Primenom Varsalovog algoritma odredjuje se tranzitivno
     zatvorenje matrice */
  for (k = 0; k < n; k++)
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        if ((zatvorenje[i][k] == 1) && (zatvorenje[k][j] == 1)
            && (zatvorenje[i][j] == 0))
          zatvorenje[i][j] = 1;
}

/* Funkcija ispisuje elemente matrice */
void pisi_matricu(int m[][MAX], int n)
{
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", m[i][j]);
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  FILE *ulaz;
  int m[MAX][MAX];
  int pomocna[MAX][MAX];
  int n, i, j;

  /* Ako korisnik nije uneo trazene argumente, prijavljuje se greska */
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

  /* Ucitava se dimenzija matrice */
  fscanf(ulaz, "%d", &n);

  /* Proverava se da li je doslo do prekoracenja dimenzije */
  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitava se element po element matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fscanf(ulaz, "%d", &m[i][j]);

  /* Ispisuje se rezultat */
  printf("Relacija %s refleksivna.\n",
         refleksivnost(m, n) == 1 ? "jeste" : "nije");

  printf("Relacija %s simetricna.\n",
         simetricnost(m, n) == 1 ? "jeste" : "nije");

  printf("Relacija %s tranzitivna.\n",
         tranzitivnost(m, n) == 1 ? "jeste" : "nije");

  printf("Refleksivno zatvorenje relacije:\n");
  ref_zatvorenje(m, n, pomocna);
  pisi_matricu(pomocna, n);

  printf("Simetricno zatvorenje relacije:\n");
  sim_zatvorenje(m, n, pomocna);
  pisi_matricu(pomocna, n);

  printf("Refleksivno-tranzitivno zatvorenje relacije:\n");
  ref_tran_zatvorenje(m, n, pomocna);
  pisi_matricu(pomocna, n);

  /* Zatvara se datoteka */
  fclose(ulaz);

  exit(EXIT_SUCCESS);
}
