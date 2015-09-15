#include<stdio.h>
#include<stdlib.h>

/* Ukljucujemo biblioteku za rad sa stablima */
#include "stabla.h"

/* a) Funkcija koja izracunava broj cvorova stabla */
int broj_cvorova(Cvor * koren)
{

  /* Ako je stablo prazno, broj cvorova je nula */
  if (koren == NULL)
    return 0;

  /* U suprotnom je broj cvorova stabla jednak zbiru broja
     cvorova u levom podstablu i broja cvorova u desnom
     podstablu - 1 dodajemo zato sto treba racunati i koren */
  return broj_cvorova(koren->levo) + broj_cvorova(koren->desno) +
      1;
}

/* b) Funkcija koja izracunava broj listova stabla */
int broj_listova(Cvor * koren)
{

  /* Ako je stablo prazno, broj listova je nula */
  if (koren == NULL)
    return 0;

  /* Proveravamo da li je tekuci cvor list */
  if (koren->levo == NULL && koren->desno == NULL)
    /* i ako jeste vracamo 1 - to ce kasnije zbog rekurzivnih
       poziva uvecati broj listova za 1 */
    return 1;

  /* U suprotnom prebrojavamo listove koje se nalaze u
     podstablima */
  return broj_listova(koren->levo) + broj_listova(koren->desno);
}

/* c) Funckija koja stampa pozitivne vrednosti listova stabla */
void pozitivni_listovi(Cvor * koren)
{

  /* Slucaj kada je stablo prazno */
  if (koren == NULL)
    return;

  /* Ako je cvor list i sadrzi pozitivnu vrednost */
  if (koren->levo == NULL && koren->desno == NULL
      && koren->broj > 0)
    /* Stampamo ga */
    printf("%d ", koren->broj);

  /* Nastavljamo sa stampanjem pozitivnih listova u podstablima */
  pozitivni_listovi(koren->levo);
  pozitivni_listovi(koren->desno);
}


/* d) Funkcija koja izracunava zbir cvorova stabla */
int zbir_cvorova(Cvor * koren)
{

  /* Ako je stablo prazno, zbir cvorova je 0 */
  if (koren == NULL)
    return 0;

  /* Inace, zbir cvorova stabla izracunavamo kao zbir korena i
     svih elemenata u podstablima */
  return koren->broj + zbir_cvorova(koren->levo) +
      zbir_cvorova(koren->desno);
}

/* e) Funckija koja izracunava najveci element stabla. */
Cvor *najveci_element(Cvor * koren)
{

  /* Ako je stablo prazno, obustavljamo pretragu */
  if (koren == NULL)
    return NULL;

  /* Zbog prirode pretrazivackog stabla, sigurni smo da su
     vrednosti vece od korena u desnom podstablu */

  /* Ako desnog podstabla nema */
  if (koren->desno == NULL)
    /* Najveca vrednost je koren */
    return koren;

  /* Inace, najvecu vrednost trazimo jos desno */
  return najveci_element(koren->desno);
}

/* f) Funckija koja izracunava dubinu stabla */
int dubina_stabla(Cvor * koren)
{

  /* Dubina praznog stabla je 0 */
  if (koren == NULL)
    return 0;

  /* Izracunavamo dubinu levog podstabla */
  int dubina_levo = dubina_stabla(koren->levo);

  /* Izracunavamo dubinu desnog podstabla */
  int dubina_desno = dubina_stabla(koren->desno);

  /* dubina stabla odgovara vecoj od dubina podstabala - 1
     dodajemo jer racunamo i koren */
  return dubina_levo >
      dubina_desno ? dubina_levo + 1 : dubina_desno + 1;
}

/* g) Funckija koja izracunava broj cvorova na i-tom nivou */
int broj_cvorova_na_itom_nivou(Cvor * koren, int i)
{
  /* ideja je da ste spustamo kroz stablo sve dok ne stignemo do
     trazenog nivoa */

  /* Ako nema vise cvorova, ne mozemo da se spustamo niz stablo */
  if (koren == NULL)
    return 0;

  /* Ako smo stigli do trazenog nivoa, vracamo 1 - to ce kasnije
     zbog rekurzivnih poziva uvecati broj pojavljivanja za 1 */
  if (i == 0)
    return 1;

  /* inace, spustamo se jedan nivo nize i u levom i u desnom
     postablu */
  return broj_cvorova_na_itom_nivou(koren->levo, i - 1)
      + broj_cvorova_na_itom_nivou(koren->desno, i - 1);
}


/* h) Funckija koja ispisuje sve elemente na i-tom nivou */
void ispis_nivo(Cvor * koren, int i)
{
  /* ideja je slicna ideji iz prethodne funkcije */

  /* nema vise cvorova, ne mozemo da se spustamo kroz stablo */
  if (koren == NULL)
    return;

  /* ako smo na trazenom nivou - ispisujemo vrednost */
  if (i == 0) {
    printf("%d ", koren->broj);
    return;
  }
  /* inace, spustamo se jedan nivo nize i u levom i u desnom
     podstablu */
  ispis_nivo(koren->levo, i - 1);
  ispis_nivo(koren->desno, i - 1);
}

/* i) Funkcija koja izracunava maksimalnu vrednost na i-tom
   nivou stabla */
Cvor *max_nivo(Cvor * koren, int i)
{

  /* Ako je stablo prazno, obustavljamo pretragu */
  if (koren == NULL)
    return NULL;

  /* Ako smo na trazenom nivou, takodje prekidamo pretragu */
  if (i == 0)
    return koren;

  /* Pronalazimo maksimum sa i-tog nivoa levog podstabla */
  Cvor *a = max_nivo(koren->levo, i - 1);

  /* Pronalazimo maksimum sa i-tog nivoa desnog podstabla */
  Cvor *b = max_nivo(koren->desno, i - 1);

  /* Trazimo i vracamo maksimum izracunatih vrednosti */
  if (a == NULL && b == NULL)
    return NULL;
  if (a == NULL)
    return b;
  if (b == NULL)
    return a;
  return a->broj > b->broj ? a : b;
}

/* j) Funkcija koja izracunava zbir cvorova na i-tom nivou */
int zbir_nivo(Cvor * koren, int i)
{

  /* Ako je stablo prazno, zbir je nula */
  if (koren == NULL)
    return 0;

  /* Ako smo na trazenom nivou, vracamo vrednost */
  if (i == 0)
    return koren->broj;

  /* Inace, spustamo se jedan nivo nize i trazimo sume iz levog
     i desnog podstabla */
  return zbir_nivo(koren->levo, i - 1) + zbir_nivo(koren->desno,
                                                   i - 1);
}


/* k) Funkcija koja izracunava zbir svih vrednosti u stablu koje 
   su manje ili jednake od date vrednosti x */
int suma(Cvor * koren, int x)
{

  /* Ako je stablo prazno, zbir je nula */
  if (koren == NULL)
    return 0;

  /* Ako je vrednost u korenu manja od trazene vrednosti, zbog
     prirode pretrazivackog stabla treba obici i levo i desno
     podstablo */
  if (koren->broj < x)
    return koren->broj + suma(koren->levo,
                              x) + suma(koren->desno, x);

  /* Inace, racunamo samo sumu vrednosti iz levog podstabla jer
     medju njima jedino moze biti onih koje zadovoljavaju uslov */
  return suma(koren->levo, x);
}


int main(int argc, char **argv)
{

  /* Analiziramo argumente komandne linije */
  if (argc != 3) {
    fprintf(stderr, "Greska! Program se poziva sa: ./a.out nivo
broj_za_pretragu\n");
    exit(EXIT_FAILURE);
  }
  int i = atoi(argv[1]);
  int x = atoi(argv[2]);

  /* Kreiramo stablo */
  Cvor *koren = NULL;
  int broj;
  while (scanf("%d", &broj) != EOF)
    dodaj_u_stablo(&koren, broj);

  /* ispisujemo rezultat rada funkcija */
  printf("broj cvorova: %d\n", br_cvorova(koren));
  printf("broj listova: %d\n", br_listova(koren));
  printf("pozitivni listovi: ");
  pozitivni_listovi(koren);
  printf("zbir cvorova: %d\n", suma_cvorova(koren));

  if (najveci_element(koren) == NULL)
    printf("najveci element: ne postoji\n");
  else
    printf("najveci element: %d\n",
           najveci_element(koren)->broj);

  printf("dubina stabla: %d\n", dubina_stabla(koren));
  printf("\n");
  printf("broj cvorova na %d. nivou: %d\n", i,
         cvorovi_nivo(koren, i));
  printf("elementi na %d. nivou: ", i);
  ispis_nivo(koren, i);
  printf("\n");
  if (max_nivo(koren, i) == NULL)
    printf("Nema elemenata na %d. nivou!\n", i);
  else
    printf("maksimalni na %d. nivou: %d\n", i,
           max_nivo(koren, i)->broj);

  printf("zbir na %d. nivou: %d\n", i, zbir_nivo(koren, i));
  printf("zbir elemenata manjih ili jednakih od %d: %d\n", x,
         suma(koren, x));

  /* Oslobadjamo memoriju zauzetu stablom */
  oslobodi_stablo(&koren);

  /* Prekidamo izvrsavanje programa */
  return 0;
}
