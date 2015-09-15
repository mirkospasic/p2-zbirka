#include <stdio.h>
#include <stdlib.h>

#define MAX 64

/* Funkcija proverava da li je relacija refleksivna. Relacija je
   refleksivna ako je svaki element u relaciji sam sa sobom,
   odnosno ako se u matrici relacije na glavnoj dijagonali nalaze 
   jedinice */
int refleksivnost(int m[][MAX], int n)
{
  int i;

  /* Obilazimo glavnu dijagonalu matrice. Za elemente na glavnoj 
     dijagonali vazi da je indeks vrste jednak indeksu kolone */
  for (i = 0; i < n; i++) {
    if (m[i][i] != 1)
      return 0;
  }

  return 1;
}

/* Funkcija odredjuje refleksivno zatvorenje zadate relacije.
   Ono je odredjeno matricom koja sadrzi sve elemente polazne
   matrice dopunjene jedinicama na glavnoj dijagonali */
void ref_zatvorenje(int m[][MAX], int n, int zatvorenje[][MAX])
{
  int i, j;

  /* Prepisujemo vrednosti elemenata matrice pocetne matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      zatvorenje[i][j] = m[i][j];

  /* Postavljamo na glavnoj dijagonali jedinice */
  for (i = 0; i < n; i++)
    zatvorenje[i][i] = 1;
}

/* Funkcija proverava da li je relacija simetricna. Relacija je
   simetricna ako za svaki par elemenata vazi: ako je element
   "i" u relaciji sa elementom "j", onda je i element "j" u
   relaciji sa elementom "i". Ovakve matrice su simetricne u
   odnosu na glavnu dijagonalu */
int simetricnost(int m[][MAX], int n)
{
  int i, j;

  /* Obilazimo elemente ispod glavne dijagonale matrice i
     uporedjujemo ih sa njima simetricnim elementima */
  for (i = 0; i < n; i++)
    for (j = 0; j < i; j++)
      if (m[i][j] != m[j][i])
        return 0;

  return 1;
}

/* Funkcija odredjuje simetricno zatvorenje zadate relacije. Ono 
   je odredjeno matricom koja sadrzi sve elemente polazne
   matrice dopunjene tako da matrica postane simetricna u odnosu 
   na glavnu dijagonalu */
void sim_zatvorenje(int m[][MAX], int n, int zatvorenje[][MAX])
{
  int i, j;

  /* Prepisujemo vrednosti elemenata matrice m */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      zatvorenje[i][j] = m[i][j];

  /* Odredjujemo simetricno zatvorenje matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (zatvorenje[i][j] == 1)
        zatvorenje[j][i] = 1;
}


/* Funkcija proverava da li je relacija tranzitivna. Relacija je 
   tranzitivna ako ispunjava sledece svojstvo: ako je element
   "i" u relaciji sa elementom "j" i element "j" u relaciji sa
   elementom "k", onda je i element "i" u relaciji sa elementom
   "k" */
int tranzitivnost(int m[][MAX], int n)
{
  int i, j, k;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      /* Pokusavamo da pronadjemo element koji narusava *
         tranzitivnost */
      for (k = 0; k < n; k++)
        if (m[i][k] == 1 && m[k][j] == 1 && m[i][j] == 0)
          return 0;

  return 1;
}


/* Funkcija odredjuje refleksivno-tranzitivno zatvorenje zadate
   relacije koriscenjem Varsalovog algoritma */
void tran_zatvorenje(int m[][MAX], int n, int zatvorenje[][MAX])
{
  int i, j, k;

  /* Kopiramo pocetnu matricu u matricu rezultata */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      zatvorenje[i][j] = m[i][j];

  /* Primenom Varsalovog algoritma odredjujemo
     refleksivno-tranzitivno zatvorenje matrice */
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
  int n, i, j, k;

  /* Ako korisnik nije uneo trazene argumente, prijavljujemo
     gresku */
  if (argc < 2) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s ime_dat.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaramo datoteku za citanje */
  ulaz = fopen(argv[1], "r");
  if (ulaz == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke %s.\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo dimenziju matrice */
  fscanf(ulaz, "%d", &n);

  /* Proveravamo da li je prekoraceno ogranicenje */
  if (n > MAX || n <= 0) {
    fprintf(stderr, "Greska: neodgovarajuca dimenzija ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo element po element matrice */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      fscanf(ulaz, "%d", &m[i][j]);

  /* Ispisujemo trazene vrednosti */
  printf("Refleksivnost: %s\n",
         refleksivnost(m, n) == 1 ? "da" : "ne");

  printf("Simetricnost: %s\n",
         simetricnost(m, n) == 1 ? "da" : "ne");

  printf("Tranzitivnost: %s\n",
         tranzitivnost(m, n) == 1 ? "da" : "ne");

  printf("Refleksivno zatvorenje:\n");
  ref_zatvorenje(m, n, pomocna);
  pisi_matricu(pomocna, n);

  printf("Simetricno zatvorenje:\n");
  sim_zatvorenje(m, n, pomocna);
  pisi_matricu(pomocna, n);

  printf("Refleksivno-tranzitivno zatvorenje:\n");
  tran_zatvorenje(m, n, pomocna);
  pisi_matricu(pomocna, n);

  /* Zatvaramo datoteku */
  fclose(ulaz);

  return 0;
}
