#include<stdio.h>
#include<string.h>
/* Niska moze imati najvise 32 karaktera + 1 za terminalnu nulu */
#define MAX_DIM 33

int palindrom(char s[], int n)
{
  if ((n == 1) || (n == 0))
    return 1;
  return (s[n - 1] == s[0]) && palindrom(s + 1, n - 2);
}

int main()
{
  char s[MAX_DIM];
  int n;

  scanf("%s", s);

  /* Odredjuje se duzina niske */
  n = strlen(s);

  /* Ispisuje se poruka da li je niska palindrom ili
     nije */
  if (palindrom(s, n))
    printf("da\n");
  else
    printf("ne\n");

  return 0;
}
