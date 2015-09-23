#include <stdio.h>
#define MAX_DIM 1000

/* 
   Ako je n==0, onda je suma(a,0) = 0 Ako je n>0, onda je
   suma(a,n) = a[n-1] + suma(a,n-1) Suma celog niza je jednaka
   sumi prvih n-1 elementa uvecenoj za poslednji element celog
   niza. */
int sumaNiza(int *a, int n)
{
  /* Nije postavljena stroga jednakost n==0, za slucaj da korisnik
     prilikom prvog poziva, posalje negativan broj za velicinu
     niza. */
  if (n <= 0)
    return 0;

  return a[n - 1] + sumaNiza(a, n - 1);
}

/* 
   Funkcija napisana na drugi nacin:
   n==0, suma(a,0) = 0 n >0, suma(a,n) = a[0]+suma(a+1,n-1) Suma 
   celog niza je jednaka zbiru prvog elementa niza i sume
   preostalih n-1 elementa. */
int sumaNiza2(int *a, int n)
{
  if (n <= 0)
    return 0;

  return a[0] + sumaNiza2(a + 1, n - 1);
}

int main()
{
  int a[MAX_DIM];
  int n, i = 0;

  /* Ucitavamo broj elemenata niza */
  scanf("%d", &n);

  /* Ucitavamo n elemenata niza. */
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  printf("Suma elemenata je %d\n", sumaNiza(a, n));
  // printf("Suma elemenata je %d\n",sumaNiza2(a, n));

  return 0;
}
