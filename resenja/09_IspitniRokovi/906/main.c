#include <stdio.h>
#include "stabla.h"

int f3(Cvor * koren, int n)
{
  if (koren == NULL || n < 0)
    return 0;
  if (n == 0) {
    if (koren->levi == NULL && koren->desni != NULL)
      return 1;
    if (koren->levi != NULL && koren->desni == NULL)
      return 1;
    return 0;
  }
  return f3(koren->levi, n - 1) + f3(koren->desni, n - 1);
}

int main()
{
  Cvor *koren;
  int n;

  scanf("%d", &n);

  if (ucitaj_stablo(&koren) == 1) {
    fprintf(stderr, "Neuspelo kreiranje stabla!\n");
    oslobodi_stablo(&koren);
    return 0;
  }

  printf("%d\n", f3(koren, n));

  oslobodi_stablo(&koren);

  return 0;
}
