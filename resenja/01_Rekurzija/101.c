#include <stdio.h>
#define MAX_DIM 1000

/********************************************************************
   Ako je n<=0, onda je suma niza jednaka 0 
   Ako je n>0, onda je suma celog niza je jednaka sumi prvih n-1 
   elementa uvecenoj za poslednji element celog niza. 
********************************************************************/
int sumaNiza(int *a, int n)
{
  if (n <= 0)
    return 0;

  return sumaNiza(a, n - 1) + a[n - 1];
}

/********************************************************************
  Funkcija napisana na drugi nacin:
  Ako je n<=0, onda je suma niza jednaka 0 
  Ako je n >0, suma celog niza je jednaka zbiru prvog elementa niza i 
  sume preostalih n-1 elementa.
********************************************************************/
int sumaNiza2(int *a, int n)
{
  if (n <= 0)
    return 0;

  return a[0] + sumaNiza2(a + 1, n - 1);
}

int main()
{
  int a[MAX_DIM];
  int n, i = 0, ind;

  /* Ucitava se redni broj funkcije */
  printf("Unesite redni broj funkcije (1 ili 2):\n");
  scanf("%d", &ind);

  /* Ucitava se broj elemenata niza */
  printf("Unesite dimenziju niza:");
  scanf("%d", &n);

  /* Ucitava se n elemenata niza. */
  printf("Unesite elemente niza:");
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  /* Na osnovu vrednosti promenljive ind ispisuje se rezultat poziva
     funkcije sumaNiza, ondosno sumaNiza2 */
  if (ind == 1)
    printf("Suma elemenata je %d\n", sumaNiza(a, n));
  else
    printf("Suma elemenata je %d\n", sumaNiza2(a, n));

  return 0;
}
