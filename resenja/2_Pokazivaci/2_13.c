#include <stdio.h>
#include <stdlib.h>

#define MAX_V 10
#define MAX_K 10

/* Funkcija proverava da li su ispisani svi elementi iz matrice,
   odnosno da li se narusio prirodan poredak medju granicama */
int kraj_ispisa(int vrh, int dno, int levo, int desno)
{
  return !(vrh <= dno && levo <= desno);
}

/* Funkcija spiralno ispisuje elemente matrice */
void ispisi_matricu_spiralno(int a[][MAX_K], int n, int m)
{
  int i, j, vrh, dno, levo, desno;

  vrh = levo = 0;
  dno = n - 1;
  desno = m - 1;

  while (!kraj_ispisa(vrh, dno, levo, desno)) {
    for (j = levo; j <= desno; j++)
      printf("%d ", a[vrh][j]);

    /* Spusta se prvi red za naredni krug ispisa */
    vrh++;

    if (kraj_ispisa(vrh, dno, levo, desno))
      break;

    for (i = vrh; i <= dno; i++)
      printf("%d ", a[i][desno]);

    /* Pomera se desna kolona za naredni krug ispisa blize levom
       kraju */
    desno--;

    if (kraj_ispisa(vrh, dno, levo, desno))
      break;

    /* Ispisuje se donja vrsta */
    for (j = desno; j >= levo; j--)
      printf("%d ", a[dno][j]);

    /* Podize se donja vrsta za naredni krug ispisa */
    dno--;

    if (kraj_ispisa(vrh, dno, levo, desno))
      break;

    /* Ispisuje se prva kolona */
    for (i = dno; i >= vrh; i--)
      printf("%d ", a[i][levo]);

    /* Priprema se leva kolona za naredni krug ispisa */
    levo++;
  }
  putchar('\n');
}

/* Funkcija ucitava matricu */
void ucitaj_matricu(int a[][MAX_K], int n, int m)
{
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &a[i][j]);
}

int main()
{
  int a[MAX_V][MAX_K];
  int m, n;

  printf("Unesite broj vrsta i broj kolona:\n");
  scanf("%d %d", &n, &m);

  if (n > MAX_V || n <= 0 || m > MAX_K || m <= 0) {
    fprintf(stderr, "Greska: neodgovarajuce dimenzije ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);
  }

  printf("Unesite elemente matrice po vrstama:\n");
  ucitaj_matricu(a, n, m);

  printf("Spiralno ispisana matrica: ");
  ispisi_matricu_spiralno(a, n, m);

  exit(EXIT_SUCCESS);
}
