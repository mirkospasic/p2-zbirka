#include<stdio.h>
#include<stdlib.h>

/* Ukljucuje se biblioteka za rad sa stablima */
#include "stabla.h"

/* a) Funkcija koja izracunava broj cvorova stabla */
int broj_cvorova(Cvor * koren)
{
  /* Ako je stablo prazno, broj cvorova je nula */
  if (koren == NULL)
    return 0;

  /* U suprotnom je broj cvorova stabla jednak zbiru broja
     cvorova u levom podstablu i broja cvorova u desnom
     podstablu - 1 se dodaje zato sto treba racunati i koren */
  return broj_cvorova(koren->levo) + broj_cvorova(koren->desno) +
      1;
}

/* b) Funkcija koja izracunava broj listova stabla */
int broj_listova(Cvor * koren)
{
  /* Ako je stablo prazno, broj listova je nula */
  if (koren == NULL)
    return 0;

  /* Proverava se da li je tekuci cvor list */
  if (koren->levo == NULL && koren->desno == NULL)
    /* Ako jeste vraca se 1 - to ce kasnije zbog rekurzivnih
       poziva uvecati broj listova za 1 */
    return 1;

  /* U suprotnom se prebrojavaju listovi koje se nalaze u
     podstablima */
  return broj_listova(koren->levo) + broj_listova(koren->desno);
}

/* c) Funkcija koja stampa pozitivne vrednosti listova stabla */
void pozitivni_listovi(Cvor * koren)
{
  /* Slucaj kada je stablo prazno */
  if (koren == NULL)
    return;

  /* Ako je cvor list i sadrzi pozitivnu vrednost */
  if (koren->levo == NULL && koren->desno == NULL
      && koren->broj > 0)
    /* Stampa se */
    printf("%d ", koren->broj);

  /* Nastavlja se sa stampanjem pozitivnih listova u podstablima 
   */
  pozitivni_listovi(koren->levo);
  pozitivni_listovi(koren->desno);
}

/* d) Funkcija koja izracunava zbir cvorova stabla */
int zbir_svih_cvorova(Cvor * koren)
{
  /* Ako je stablo prazno, zbir cvorova je 0 */
  if (koren == NULL)
    return 0;

  /* Inace, zbir cvorova stabla izracunava se kao zbir korena i
     svih elemenata u podstablima */
  return koren->broj + zbir_svih_cvorova(koren->levo) +
      zbir_svih_cvorova(koren->desno);
}

/* e) Funkcija koja izracunava najveci element stabla */
Cvor *najveci_element(Cvor * koren)
{
  /* Ako je stablo prazno, obustavlja se pretraga */
  if (koren == NULL)
    return NULL;

  /* Zbog prirode pretrazivackog stabla, vrednosti vece od
     korena se nalaze u desnom podstablu */

  /* Ako desnog podstabla nema */
  if (koren->desno == NULL)
    /* Najveca vrednost je koren */
    return koren;

  /* Inace, najveca vrednost se trazi desno */
  return najveci_element(koren->desno);
}

/* f) Funkcija koja izracunava dubinu stabla */
int dubina_stabla(Cvor * koren)
{
  /* Dubina praznog stabla je 0 */
  if (koren == NULL)
    return 0;

  /* Izracunava se dubina levog podstabla */
  int dubina_levo = dubina_stabla(koren->levo);

  /* Izracunava se dubina desnog podstabla */
  int dubina_desno = dubina_stabla(koren->desno);

  /* Dubina stabla odgovara vecoj od dubina podstabala - 1 se
     dodaje jer se racuna i koren */
  return dubina_levo >
      dubina_desno ? dubina_levo + 1 : dubina_desno + 1;
}

/* g) Funkcija koja izracunava broj cvorova na i-tom nivou
   stabla */
int broj_cvorova_na_itom_nivou(Cvor * koren, int i)
{
  /* Ideja je spustanje kroz stablo sve dok se ne stigne do
     trazenog nivoa */

  /* Ako nema vise cvorova, nema spustanja niz stablo */
  if (koren == NULL)
    return 0;

  /* Ako se stiglo do trazenog nivoa, vraca se 1 - to ce kasnije 
     zbog rekurzivnih poziva uvecati broj cvorova za 1 */
  if (i == 0)
    return 1;

  /* Inace, spusta se jedan nivo nize i u levom i u desnom
     postablu */
  return broj_cvorova_na_itom_nivou(koren->levo, i - 1)
      + broj_cvorova_na_itom_nivou(koren->desno, i - 1);
}

/* h) Funkcija koja ispisuje sve elemente na i-tom nivou */
void ispis_nivo(Cvor * koren, int i)
{
  /* Ideja je slicna ideji iz prethodne funkcije */

  /* Nema vise cvorova, nema spustanja kroz stablo */
  if (koren == NULL)
    return;

  /* Ako se stiglo do trazenog nivoa - ispisuje se vrednost */
  if (i == 0) {
    printf("%d ", koren->broj);
    return;
  }
  /* Inace, spustanje se nastavlja za jedan nivo nize i u levom
     i u desnom podstablu */
  ispis_nivo(koren->levo, i - 1);
  ispis_nivo(koren->desno, i - 1);
}

/* i) Funkcija koja izracunava maksimalnu vrednost na i-tom
   nivou stabla */
Cvor *najveci_element_na_itom_nivou(Cvor * koren, int i)
{
  /* Ako je stablo prazno, obustavlja se pretraga */
  if (koren == NULL)
    return NULL;

  /* Ako se stiglo do trazenog nivoa, takodje se prekida
     pretraga */
  if (i == 0)
    return koren;

  /* Pronalazi se maksimum sa i-tog nivoa levog podstabla */
  Cvor *a = najveci_element_na_itom_nivou(koren->levo, i - 1);

  /* Pronalazi se maksimum sa i-tog nivoa desnog podstabla */
  Cvor *b = najveci_element_na_itom_nivou(koren->desno, i - 1);

  /* Trazi se i vraca maksimum izracunatih vrednosti */
  if (a == NULL && b == NULL)
    return NULL;
  if (a == NULL)
    return b;
  if (b == NULL)
    return a;
  return a->broj > b->broj ? a : b;
}

/* j) Funkcija koja izracunava zbir cvorova na i-tom nivou */
int zbir_cvorova_na_itom_nivou(Cvor * koren, int i)
{
  /* Ako je stablo prazno, zbir je nula */
  if (koren == NULL)
    return 0;

  /* Ako se stiglo do trazenog nivoa, vraca se vrednost */
  if (i == 0)
    return koren->broj;

  /* Inace, spustanje se nastavlja za jedan nivo nize i traze se 
     sume iz levog i desnog podstabla */
  return zbir_cvorova_na_itom_nivou(koren->levo, i - 1)
      + zbir_cvorova_na_itom_nivou(koren->desno, i - 1);
}


/* k) Funkcija koja izracunava zbir svih vrednosti u stablu koje 
   su manje ili jednake od date vrednosti x */
int zbir_manjih_od_x(Cvor * koren, int x)
{
  /* Ako je stablo prazno, zbir je nula */
  if (koren == NULL)
    return 0;

  /* Ako je vrednost u korenu manja od trazene vrednosti, zbog
     prirode pretrazivackog stabla treba obici i levo i desno
     podstablo */
  if (koren->broj <= x)
    return koren->broj + zbir_manjih_od_x(koren->levo, x) +
        zbir_manjih_od_x(koren->desno, x);

  /* Inace, racuna se samo suma vrednosti iz levog podstabla jer
     medju njima jedino moze biti onih koje zadovoljavaju uslov */
  return zbir_manjih_od_x(koren->levo, x);
}

int main(int argc, char **argv)
{
  /* Analiza argumenata komandne linije */
  if (argc != 3) {
    fprintf(stderr,
            "Greska! Program se poziva sa: ./a.out nivo broj_za_pretragu\n");
    exit(EXIT_FAILURE);
  }
  int i = atoi(argv[1]);
  int x = atoi(argv[2]);

  /* Kreira se stablo */
  Cvor *koren = NULL;
  int broj;
  while (scanf("%d", &broj) != EOF)
    dodaj_u_stablo(&koren, broj);

  /* ispisuju se rezultati rada funkcija */
  printf("Broj cvorova: %d\n", broj_cvorova(koren));
  printf("Broj listova: %d\n", broj_listova(koren));
  printf("Pozitivni listovi: ");
  pozitivni_listovi(koren);
  printf("\n");
  printf("Zbir cvorova: %d\n", zbir_svih_cvorova(koren));
  if (najveci_element(koren) == NULL)
    printf("Najveci element: ne postoji\n");
  else
    printf("Najveci element: %d\n",
           najveci_element(koren)->broj);

  printf("Dubina stabla: %d\n", dubina_stabla(koren));

  printf("Broj cvorova na %d. nivou: %d\n", i,
         broj_cvorova_na_itom_nivou(koren, i));
  printf("Elementi na %d. nivou: ", i);
  ispis_nivo(koren, i);
  printf("\n");
  if (najveci_element_na_itom_nivou(koren, i) == NULL)
    printf("Nema elemenata na %d. nivou!\n", i);
  else
    printf("Maksimalni element na %d. nivou: %d\n", i,
           najveci_element_na_itom_nivou(koren, i)->broj);

  printf("Zbir elemenata na %d. nivou: %d\n", i,
         zbir_cvorova_na_itom_nivou(koren, i));
  printf("Zbir elemenata manjih ili jednakih od %d: %d\n", x,
         zbir_manjih_od_x(koren, x));

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
