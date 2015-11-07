#include <stdio.h>
unsigned int Rotiraj(unsigned int x, unsigned int n) 
{
  int i;
  unsigned int maska = 1;
  /* Formiranje maske sa n jedinica na kraju 000...00001111 */ 
  for (i = 1; i < n; i++)
    maska = (maska << 1) | 1;
  return (x >> n) | ((maska & x) << (sizeof(unsigned) * 8 - n));} int main() 
{
  unsigned int x, n;
  
  /*Ucitavanje brojeva sa standardnog ulaza */
  scanf("%u%u", &x, &n);
  
  /* Ispisivanje rezultata */
  printf("%u\n", Rotiraj(x, n));
  return 0;}


