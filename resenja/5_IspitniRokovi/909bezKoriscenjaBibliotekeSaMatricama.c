#include <stdio.h>
#include <stdlib.h>

/* Funkcija dinamicki alocira prostor za kvadratnu matricu dimenzije 
   n  */
int **alociraj_matricu(int n)
{
  int **matrica = NULL;
  int i, j;

  /* Alocira se prostor za niz vrsti matrice */
  matrica = (int **) malloc(n * sizeof(int *));
  /* Ako alokacija nije prosla uspesno, povratna vrednost funkcije ce
     biti NULL, sto mora biti provereno u main funkciji */
  if (matrica == NULL)
    return NULL;

  /* Alocira se prostor za svaku vrstu matrice */
  for (i = 0; i < n; i++) {
    matrica[i] = (int *) malloc(n * sizeof(int));
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

/* Funkcija oslobadja dinamicki alociranu memoriju */
int **dealociraj_matricu(int **matrica, int n)
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

/* Funkcija ucitava sa standardnog ulaza elemente matrice */
void ucitaj_matricu(int **matrica, int n)
{
  int i, j;
  /* Elementi matrice se ucitacaju po vrstama */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%d", &matrica[i][j]);
}


/* Funkcija racuna zbir elemenata v-te vrste */
int zbir_vrste(int **M, int n, int v)
{
  int j, zbir = 0;
  for (j = 0; j < n; j++)
    zbir += M[v][j];
  return zbir;
}

/* Funkcija racuna zbir elemenata k-te kolone */
int zbir_kolone(int **M, int n, int k)
{
  int i, zbir = 0;
  for (i = 0; i < n; i++)
    zbir += M[i][k];
  return zbir;
}

/* Funkcija proverava da li je kvadrat koji joj se prosledjuje kao 
   argument magican. Ukoliko jeste magican funkcija vraca 1, inace 0. 
   Argument funkcije zbir ce sadrzati zbir elemenata neke vrste ili 
   kolone ukoliko je kvadrat magican. */ 
int magicni_kvadrat(int **M, int n, int *zbirmagicnog) 
{
  int i, j;
  int zbir = 0, zbir_pom;
  /* Promenljivu zbir inicijalizujemo na zbir 0-te vreste */
  zbir = zbir_vrste(M, n, 0);
  
  /* Racunaju se zbirovi u ostalim vrstama i ako neki razlikuje od 
     vrednosti promeljive zbir funkcija vraca 1 */
  for (i = 1; i < n; i++) {
    zbir_pom = zbir_vrste(M, n, i);
    if (zbir_pom != zbir)
      return 0;
  }
  /* Racunaju se zbirovi u svim kolonama i ako neki razlikuje od 
     vrednosti promeljive zbir funkcija vraca 1 */
  for (j = 0; j < n; j++) {
    zbir_pom = zbir_kolone(M, n, j);
    if (zbir_pom != zbir)
      return 0;
  }
  /* Inace su zbirovi svih vrsta i kolona jednaki, postavlja se 
     vresnost u zbirmagicnog i funkcija vraca 1 */
  *zbirmagicnog = zbir;
  return 1;
}

int main() 
{
  int n, i, j;
  int **matrica = NULL;
  int zbir = 0, zbirmagicnog = 0;
  scanf("%d", &n);
  
  /* Provera da li je n strogo pozitivan */ 
  if (n <= 0) {
    printf("-1\n");
    exit(EXIT_FAILURE);
  }
  
  /* Dinamicka alokacija matrice dimenzije nxn */ 
  matrica = alociraj_matricu(n);
  if (matrica == NULL) {
    printf("-1\n");
    exit(EXIT_FAILURE);  
  }
 
  /* Ucitavanje elemenata matrice sa standardnog ulaza */ 
  ucitaj_matricu(matrica, n);
      
  /* Ispisivanje rezultata na osnovu fukcije magicni_kvadrat */ 
  if (magicni_kvadrat(matrica, n, &zbirmagicnog)) {
    printf("%d\n", zbirmagicnog);
  } else
    printf("-\n");
  
  /* Oslobadjanje dinamicki alocirane memorije */ 
  matrica = dealociraj_matricu(matrica, n);
  
  return 0;
}

