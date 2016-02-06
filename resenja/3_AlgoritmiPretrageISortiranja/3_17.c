#include <stdio.h>
#define MAX_DIM 256

/* Funkcija objedinjuje nizove niz1 i niz2 dimenzija dim1 i dim2, a
   rezultat cuva u nizu dim3 za koji je rezervisano dim3 elemenata */
int merge(int *niz1, int dim1, int *niz2, int dim2, int *niz3,
          int dim3)
{
  int i = 0, j = 0, k = 0;
  /* U slucaju da je dimenzija treceg niza manja od neophodne,
     funkcija vraca -1 */
  if (dim3 < dim1 + dim2)
    return -1;

  /* Vrsi se ucesljavanje nizova sve dok se ne dodje do kraja jednog
     od njih */
  while (i < dim1 && j < dim2) {
    if (niz1[i] < niz2[j])
      niz3[k++] = niz1[i++];
    else
      niz3[k++] = niz2[j++];
  }
  /* Ostatak prvog niza prepisujemo u treci */
  while (i < dim1)
    niz3[k++] = niz1[i++];

  /* Ostatak drugog niza prepisujemo u treci */
  while (j < dim2)
    niz3[k++] = niz2[j++];
  return dim1 + dim2;
}

int main()
{
  int niz1[MAX_DIM], niz2[MAX_DIM], niz3[2 * MAX_DIM];
  int i = 0, j = 0, k, dim3;

  /* Ucitavaju se nizovi sa ulaza sve dok se ne unese nula.
     Pretpostavka je da na ulazu nece biti vise od MAX_DIM elemenata */
  printf("Unesite elemente prvog niza: ");
  while (1) {
    scanf("%d", &niz1[i]);
    if (niz1[i] == 0)
      break;
    i++;
  }
  printf("Unesite elemente drugog niza: ");
  while (1) {
    scanf("%d", &niz2[j]);
    if (niz2[j] == 0)
      break;
    j++;
  }

  /* Poziv trazene funkcije */
  dim3 = merge(niz1, i, niz2, j, niz3, 2 * MAX_DIM);

  /* Ispis niza */
  for (k = 0; k < dim3; k++)
    printf("%d ", niz3[k]);
  printf("\n");

  return 0;
}
