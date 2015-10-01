#include <stdio.h>


/************************************************************
  Linearno resenje se zasniva na cinjenici: 
  x^0 = 1 x^k = x * x^(k-1) 
*************************************************************/
int stepen(int x, int k)
{
  // printf("Racunam stepen (%d, %d)\n", x, k); 
  if (k == 0)
    return 1;

  return x * stepen(x, k - 1);
}

/*************************************************************
   Celo telo funkcije se moze ovako kratko zapisati 
   return k == 0 ? 1 : x * stepen(x,k-1);

   Druga verzija prethodne funkcije. Obratiti paznju na
   efikasnost u odnosu na prvu verziju!
 Logaritamsko resenje je zasnovano na cinjenicama: 
   x^0 =1;  
   x^k = x * (x^2 )^(k/2) , za neparno k 
   x^k = (x^2)^(k/2) , za parno k
   Ovom resenju ce biti potrebno manje rekurzivnih poziva da bi
   doslo do rezultata, i stoga je efikasnije. 
*************************************************************/
int stepen2(int x, int k)
{
  // printf("Racunam stepen2 (%d, %d)\n",x,k); 
  if (k == 0)
    return 1;

  /* Ako je stepen paran */
  if ((k % 2) == 0)
    return stepen2(x * x, k / 2);
  /* Inace (ukoliko je stepen neparan) */
  return x * stepen2(x * x, k / 2);
}

/* U prethodnim funkcijama iskomentarisan je poziv funkcije prinf
   koji ispisuje odgovarajucu poruku prilikom svakog ulaska us
   funkciju. Odkomentarisati pozive printf funkcije u obe funkcije da 
   uocite razliku u broju rekurzivnih poziva obe verzije. */

int main()
{
  int x, k;
  scanf("%d%d", &x, &k);

  printf("%d\n", stepen(x, k));
  // printf("\n------------------\n");
  // printf("%d\n",stepen2(2,10));
  return 0;
}
