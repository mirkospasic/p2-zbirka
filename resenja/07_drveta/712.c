#include <stdio.h>
#include <stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* Funkcija koja izracunava dubinu stabla */
int dubina_stabla(Cvor * koren)
{
  /* Dubina praznog stabla je 0 */
  if (koren == NULL)
    return 0;

  /* Izracunava se dubina levog podstabla */
  int dubina_levo = dubina_stabla(koren->levo);

  /* Izracunava se dubina desnog podstabla */
  int dubina_desno = dubina_stabla(koren->desno);

  /* Dubina stabla odgovara vecoj od dubina podstabala - 1 se dodaje
     jer se racuna i koren */
  return dubina_levo >
      dubina_desno ? dubina_levo + 1 : dubina_desno + 1;
}

/* Funkcija koja ispisuje sve elemente na i-tom nivou */
void ispisi_nivo(Cvor * koren, int i)
{
  /* Ideja je slicna ideji iz prethodne funkcije */
  /* Nema vise cvorova, nema spustanja niz stablo */
  if (koren == NULL)
    return;

  /* Ako se stiglo do trazenog nivoa - ispisuje se vrednost */
  if (i == 0) {
    printf("%d ", koren->broj);
    return;
  }
  /* Inace, vrsi se spustanje za jedan nivo nize i u levom i u desnom 
     podstablu */
  ispisi_nivo(koren->levo, i - 1);
  ispisi_nivo(koren->desno, i - 1);
}

/* Funkcija koja ispisuje stablo po nivoima */
void ispisi_stablo_po_nivoima(Cvor * koren)
{
  int i;

  /* Prvo se izracunava dubina stabla */
  int dubina;
  dubina = dubina_stabla(koren);

  /* Ispisuje se nivo po nivo stabla */
  for (i = 0; i < dubina; i++) {
    printf("%d. nivo: ", i);
    ispisi_nivo(koren, i);
    printf("\n");
  }
}

int main(int argc, char **argv)
{
  Cvor *koren;
  int broj;

  /* Citaju se vrednosti sa ulaza i dodaju se u stablo uz proveru
     uspesnosti dodavanja */
  koren = NULL;
  while (scanf("%d", &broj) != EOF) {
    if (dodaj_u_stablo(&koren, broj) == 1) {
      fprintf(stderr, "Neuspelo dodavanje broja %d\n", broj);
      oslobodi_stablo(&koren);
      return 0;
    }
  }

  /* Ispisuje se stablo po nivoima */
  ispisi_stablo_po_nivoima(koren);

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
