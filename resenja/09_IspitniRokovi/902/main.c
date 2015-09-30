#include <stdio.h>
#include "stabla.h"

int sumirajN(Cvor * koren, int n)
{
  if (koren == NULL)
    return 0;

  if (n == 0)
    return koren->broj;

  return sumirajN(koren->levo, n - 1) + sumirajN(koren->desno, n - 1);
}

int main()
{
  Cvor *koren = NULL;
  int n;
  int nivo;

  scanf("%d", &nivo);

  while (1) {
    scanf("%d", &n);
    /* Ukoliko je korisnik uneo 0, prekida se dalje citanje. */
    if (n == 0)
      break;

    /* Ako nije, dodaje se procitani broj u stablo. */
    dodaj_u_stablo(&koren, n);
  }

  /* Ispisuje se rezultat rada trazene funkcije */
  printf("%d\n", sumirajN(koren, nivo));

  /* Oslobadja se memorija */
  oslobodi_stablo(&koren);

  return 0;
}
