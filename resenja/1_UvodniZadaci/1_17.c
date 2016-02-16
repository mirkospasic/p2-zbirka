#include <stdio.h>
#include <stdlib.h>

/********************************************************************
  Resenje linearne slozenosti: 
  x^0 = 1 
  x^k = x * x^(k-1) 
********************************************************************/
int stepen(int x, int k)
{
  if (k == 0)
    return 1;

  return x * stepen(x, k - 1);
  /* kraci zapis: return k == 0 ? 1 : x * stepen(x,k-1); */
}

/********************************************************************
   Resenje logaritamske slozenosti: 
   x^0 =1;  
   x^k = x * (x^2 )^(k/2) , za neparno k 
   x^k = (x^2)^(k/2) , za parno k
   Ovom resenju ce biti potrebno manje rekurzivnih poziva da bi
   se doslo do rezultata, i stoga je efikasnije. 
********************************************************************/
int stepen_2(int x, int k)
{
  if (k == 0)
    return 1;

  /* Ako je stepen paran */
  if ((k % 2) == 0)
    return stepen_2(x * x, k / 2);

  /* Inace (ukoliko je stepen neparan) */
  return x * stepen_2(x * x, k / 2);
}

int main()
{
  int x, k, ind;

  /* Ucitava se redni broj funkcije koja ce se primeniti */
  printf("Unesite redni broj funkcije (1/2):\n");
  scanf("%d", &ind);

  /* Ucitavaju se vrednosti za x i k */
  printf("Unesite broj x:\n");
  scanf("%d", &x);
  printf("Unesite broj k:\n");
  scanf("%d", &k);

  /* Ispisuje se vrednost koju vraca odgovarajuca funkcija */
  if (x == 1)
    printf("%d\n", stepen(x, k));
  else if (x == 2)
    printf("%d\n", stepen_2(x, k));
  else {
    fprintf(stderr, "Neodgovarajuci redni broj funkcije!\n");
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
}
