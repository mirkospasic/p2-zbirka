#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

/* Maksimalna duzina niza */
#define MAX 1000000

int main(int argc, char *argv[])
{
  /*****************************************************************
     tip_sortiranja == 0 => selectionsort, (podrazumevano)
     tip_sortiranja == 1 => insertionsort, -i opcija komandne linije
     tip_sortiranja == 2 => bubblesort,    -b opcija komandne linije
     tip_sortiranja == 3 => shellsort,     -s opcija komandne linije
     tip_sortiranja == 4 => mergesort,     -m opcija komandne linije
     tip_sortiranja == 5 => quicksort,     -q opcija komandne linije
  ******************************************************************/
  int tip_sortiranja = 0;
  /*****************************************************************
     tip_niza == 0 => slucajno generisani nizovi, (podrazumevano)
     tip_niza == 1 => rastuce sortirani nizovi,   -r opcija
     tip_niza == 2 => opadajuce soritrani nizovi, -o opcija
  ******************************************************************/
  int tip_niza = 0;

  /* Dimenzija niza koji se sortira */
  int dimenzija;
  int i;
  int niz[MAX];

  /* Provera argumenata komandne linije */
  if (argc < 2) {
    fprintf(stderr,
            "Program zahteva bar 2 argumenta komandne linije!\n");
    exit(EXIT_FAILURE);
  }

  /* Ocitavanje opcija i argumenata prilikom poziva programa */
  for (i = 1; i < argc; i++) {
    /* Ako je u pitanju opcija... */
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'i':
        tip_sortiranja = 1;
        break;
      case 'b':
        tip_sortiranja = 2;
        break;
      case 's':
        tip_sortiranja = 3;
        break;
      case 'm':
        tip_sortiranja = 4;
        break;
      case 'q':
        tip_sortiranja = 5;
        break;
      case 'r':
        tip_niza = 1;
        break;
      case 'o':
        tip_niza = 2;
        break;
      default:
        printf("Pogresna opcija -%c\n", argv[i][1]);
        return 1;
        break;
      }
    }
    /* Ako je u pitanju argument, onda je to duzina niza koji treba
       da se sortira */
    else {
      dimenzija = atoi(argv[i]);
      if (dimenzija <= 0 || dimenzija > MAX) {
        fprintf(stderr, "Dimenzija niza neodgovarajuca!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  /* Elementi niza se odredjuju slucajno, ali vodeci racuna o tipu
     niza dobijenom iz komandne linije. srandom() funkcija
     obezbedjuje novi seed za pozivanje random funkcije, i kako
     generisani niz ne bi uvek bio isti seed je postavljen na tekuce
     vreme u sekundama od Nove godine 1970. random()%100 daje brojeve 
     izmedju 0 i 99 */
  srandom(time(NULL));
  if (tip_niza == 0)
    for (i = 0; i < dimenzija; i++)
      niz[i] = random();
  else if (tip_niza == 1)
    for (i = 0; i < dimenzija; i++)
      niz[i] = i == 0 ? random() % 100 : niz[i - 1] + random() % 100;
  else
    for (i = 0; i < dimenzija; i++)
      niz[i] = i == 0 ? random() % 100 : niz[i - 1] - random() % 100;

  /* Ispisivanje elemenata niza */
  /*****************************************************************
    Ovaj deo je iskomentarisan jer sledeci ispis ne treba da se nadje
    na standardnom izlazu. Njegova svrha je samo bila provera da li
    je niz generisan u skladu sa opcijama komandne linije.

    printf("Niz koji sortiramo je:\n");
    for (i = 0; i < dimenzija; i++)
      printf("%d\n", niz[i]);
  ******************************************************************/


  /* Sortiranje niza na odgovarajuci nacin */
  if (tip_sortiranja == 0)
    selectionsort(niz, dimenzija);
  else if (tip_sortiranja == 1)
    insertionsort(niz, dimenzija);
  else if (tip_sortiranja == 2)
    bubblesort(niz, dimenzija);
  else if (tip_sortiranja == 3)
    shellsort(niz, dimenzija);
  else if (tip_sortiranja == 4)
    mergesort(niz, 0, dimenzija - 1);
  else
    quicksort(niz, 0, dimenzija - 1);

  /* Ispis elemenata niza */
  /*****************************************************************
    Ovaj deo je iskomentarisan jer vreme potrebno za njegovo
    izvrsavanje ne bi trebalo da bude ukljuceno u vreme izmereno
    programom time. Takodje, kako je svrha ovog programa da prikaze
    vremena razlicitih algoritama sortiranja, dimenzije nizova ce
    biti, verovatno, ogromne, pa nema smisla imati na izlazu nizove
    od toliko elemenata. Ovaj deo je koriscen u razvoju programa
    zarad testiranja korektnosti. 

    printf("Sortiran niz je:\n");
    for (i = 0; i < dimenzija; i++)
      printf("%d\n", niz[i]); 
  ******************************************************************/

  return 0;
}
