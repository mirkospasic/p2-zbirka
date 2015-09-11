#include<stdio.h>
#include<stdlib.h>

/* Ukljucujemo biblioteku za rad sa stablima */
#include "stabla.h"

/* Funckija koja izracunava dubinu stabla */
int dubina_stabla(Cvor * koren)
{

  /* Dubina praznog stabla je 0 */
  if (koren == NULL)
    return 0;

  /* Izracunavamo dubinu levog podstabla */
  int dubina_levo = dubina_stabla(koren->levo);

  /* Izracunavamo dubinu desnog podstabla */
  int dubina_desno = dubina_stabla(koren->desno);

  /* Dubina stabla odgovara vecoj od dubina podstabala - 1
     dodajemo jer racunamo i koren */
  return dubina_levo >
      dubina_desno ? dubina_levo + 1 : dubina_desno + 1;
}

/* Funckija koja ispisuje sve elemente na i-tom nivou */
void ispisi_nivo(Cvor * koren, int i)
{
  /* Ideja je slicna ideji iz prethodne funkcije */

  /* Nema vise cvorova, ne mozemo da se spustamo kroz stablo */
  if (koren == NULL)
    return;

  /* Ako smo na trazenom nivou - ispisujemo vrednost */
  if (i == 0) {
    printf("%d ", koren->broj);
    return;
  }
  /* Inace, spustamo se jedan nivo nize i u levom i u desnom
     podstablu */
  ispisi_nivo(koren->levo, i - 1);
  ispisi_nivo(koren->desno, i - 1);
}

/* Funkcija koja ispisuje stablo po nivoima */
void ispisi_stablo_po_nivoima(Cvor * koren)
{

  int i;

  /* Prvo izracunavamo dubinu stabla */
  int dubina;
  dubina = dubina_stabla(koren);

  /* Ispisujemo nivo po nivo stabla */
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

  /* Citamo vrednosti sa ulaza i dodajemo ih u stablo */
  koren = NULL;
  while (scanf("%d", &broj) != EOF) {
    dodaj_u_stablo(&koren, broj);
  }

  /* Ispisujemo stablo po nivoima */
  ispisi_stablo_po_nivoima(koren);

  /* Oslobadjamo memoriju zauzetu stablom */
  oslobodi_stablo(&koren);

  /* Prekidamo izvrsavanje programa */
  return 0;
}
