#include <stdio.h>


/************************************************************
  Linearno resenje se zasniva na cinjenici: 
  x^0 = 1 x^k = x * x^(k-1) 
*************************************************************/
int stepen(int x, int k)
{
  if (k == 0)
    return 1;

  return x * stepen(x, k - 1);
}

/*************************************************************
   Celo telo funkcije se moze kratko zapisati 
   return k == 0 ? 1 : x * stepen(x,k-1);

   Druga verzija prethodne funkcije. Obratiti paznju na
   efikasnost u odnosu na prvu verziju!
 Logaritamsko resenje je zasnovano na cinjenicama: 
   x^0 =1;  
   x^k = x * (x^2 )^(k/2) , za neparno k 
   x^k = (x^2)^(k/2) , za parno k
   Ovom resenju ce biti potrebno manje rekurzivnih poziva da bi
   se doslo do rezultata, i stoga je efikasnije. 
*************************************************************/
int stepen2(int x, int k)
{
  if (k == 0)
    return 1;

  /* Ako je stepen paran */
  if ((k % 2) == 0)
    return stepen2(x * x, k / 2);

  /* Inace (ukoliko je stepen neparan) */
  return x * stepen2(x * x, k / 2);
}

int main()
{
  int x, k, ind;

  /* Ucitava se redni broj funkcije koja ce se primeniti */
  printf("Unesite redni broj funkcije (1/2):\n");
  scanf("%d", &ind);

  /* Ucitavaju se vrednosti za x i k */
  printf("Unesite broj x:\n");
  scanf("%d%d", &x);
  printf("Unesite broj k:\n");
  scanf("%d%d", &k);

  /* Ispisuje se vrednost koju vraca odgovarajuca funkcija */
  if (x == 1)
    printf("%d\n", stepen(x, k));
  else
    printf("%d\n", stepen2(x, k));

  return 0;
}
