#include <stdio.h>
#include "liste.h"

int main()
{
  Cvor *glava = NULL;
  double broj;

  /* Ucitavanje se vrsi do kraja ulaza. Elementi se dodaju na kraj
     liste! */
  while (scanf("%lf", &broj) > 0)
    dodaj_na_kraj_liste(&glava, broj);

  dopuni_listu(&glava);

  ispisi_listu(glava);

  oslobodi_listu(&glava);

  return 0;
}
