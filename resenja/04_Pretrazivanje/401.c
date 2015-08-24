#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000000

/* Pri prevodjenju program linkovati sa bibliotekom librt opciom 
   -lrt zbog funkcije clock_gettime() */

/* Funkcija pretrazuje niz celih brojeva duzine n, trazeci u
   njemu element x. Pretraga se vrsi prostom iteracijom kroz
   niz. Ako se element pronadje funkcija vraca indeks pozicije
   na kojoj je pronadjen. Ovaj indeks je uvek nenegativan. Ako
   element nije pronadjen u nizu, funkcija vraca -1, kao
   indikator neuspesne pretrage. */
int linearna_pretraga(int a[], int n, int x)
{
  int i;
  for (i = 0; i < n; i++)
    if (a[i] == x)
      return i;
  return -1;
}

/* Funkcija trazi u sortiranom nizu a[] duzine n broj x. Vraca
   indeks pozicije nadjenog elementa ili -1, ako element nije
   pronadjen */
int binarna_pretraga(int a[], int n, int x)
{
  int levi = 0;
  int desni = n - 1;
  int srednji;
  /* Dokle god je indeks levi levo od indeksa desni */
  while (levi <= desni) {
    /* Racunamo srednji indeks */
    srednji = (levi + desni) / 2;
    /* Ako je srednji element veci od x, tada se x mora nalaziti 
       u levoj polovini niza */
    if (x < a[srednji])
      desni = srednji - 1;
    /* Ako je srednji element manji od x, tada se x mora
       nalaziti u desnoj polovini niza */
    else if (x > a[srednji])
      levi = srednji + 1;
    else
      /* Ako je srednji element jednak x, tada smo pronasli x na 
         poziciji srednji */
      return srednji;
  }
  /* Ako nije pronadjen vracamo -1 */
  return -1;
}

/* Funkcija trazi u sortiranom nizu a[] duzine n broj x. Vraca
   indeks pozicije nadjenog elementa ili -1, ako element nije
   pronadjen */
int interpolaciona_pretraga(int a[], int n, int x)
{
  int levi = 0;
  int desni = n - 1;
  int srednji;
  /* Dokle god je indeks levi levo od indeksa desni...  */
  while (levi <= desni) {
    /* Ako je element manji od pocetnog ili veci od poslednjeg
       clana u delu niza a[levi],...,a[desni] tada nije u tom
       delu niza. Ova provera je neophodna, da se ne bi dogodilo 
       da se prilikom izracunavanja indeksa srednji izadje izvan 
       opsega indeksa [levi,desni] */
    if (x < a[levi] || x > a[desni])
      return -1;
    /* U suprotnom, x je izmedju a[levi] i a[desni], pa ako su
       a[levi] i a[desni] jednaki, tada je jasno da je x jednako 
       ovim vrednostima, pa vracamo indeks levi (ili indeks
       desni, sve jedno je).Ova provera je neophodna, zato sto
       bismo inace prilikom izracunavanja srednji imali deljenje 
       nulom. */
    else if (a[levi] == a[desni])
      return levi;
    /* Racunamo srednji indeks */
    srednji =
        levi +
        ((double) (x - a[levi]) / (a[desni] - a[levi])) *
        (desni - levi);
    /* Napomena: Indeks srednji je uvek izmedju levi i desni,
       ali ce verovatno biti blize trazenoj vrednosti nego da
       smo prosto uvek uzimali srednji element. Ovo se moze
       porediti sa pretragom recnika: ako neko trazi rec na
       slovo 'B', sigurno nece da otvori recnik na polovini, vec 
       verovatno negde blize pocetku. */
    /* Ako je srednji element veci od x, tada se x mora nalaziti 
       u levoj polovini niza */
    if (x < a[srednji])
      desni = srednji - 1;
    /* Ako je srednji element manji od x, tada se x mora
       nalaziti u desnoj polovini niza */
    else if (x > a[srednji])
      levi = srednji + 1;
    else
      /* Ako je srednji element jednak x, tada smo pronasli x na 
         poziciji srednji */
      return srednji;
  }
  /* Ako nije pronadjen vracamo -1 */
  return -1;
}

/* Funkcija main */
int main(int argc, char **argv)
{
  int a[MAX];
  int n, i, x;
  struct timespec time1, time2, time3, time4, time5, time6;
  FILE *f;

  /* Provera argumenata komandne linije */
  if (argc != 3) {
    fprintf(stderr,
            "koriscenje programa: %s dim_niza trazeni_br\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Dimenzija niza */
  n = atoi(argv[1]);
  if (n > MAX || n <= 0) {
    fprintf(stderr, "Dimenzija niza neodgovarajuca\n");
    exit(EXIT_FAILURE);
  }

  /* Broj koji se trazi */
  x = atoi(argv[2]);

  /* Elemente niza odredjujemo slucajno, tako da je svaki
     sledeci veci od prethodnog. srandom() funkcija obezbedjuje
     novi seed za pozivanje random() funkcije. Kako nas niz ne
     bi uvek isto izgledao seed smo postavili na tekuce vreme u
     sekundama od Nove godine 1970. random()%100 daje brojeve
     izmedju 0 i 99 */
  srandom(time(NULL));
  for (i = 0; i < n; i++)
    a[i] = i == 0 ? random() % 100 : a[i - 1] + random() % 100;

  /* Lineara pretraga */
  printf("Linearna pretraga\n");
  /* Racunamo vreme proteklo od Nove godine 1970 */
  clock_gettime(CLOCK_REALTIME, &time1);
  /* Pretrazujemo niz */
  i = linearna_pretraga(a, n, x);
  /* Racunamo novo vreme i razlika predstavlja vreme utroseno za 
     lin pretragu */
  clock_gettime(CLOCK_REALTIME, &time2);
  if (i == -1)
    printf("Element nije u nizu\n");
  else
    printf("Element je u nizu na poziciji %d\n", i);
  printf("---------------------------------\n");

  /* Binarna pretraga */
  printf("Binarna pretraga\n");
  clock_gettime(CLOCK_REALTIME, &time3);
  i = binarna_pretraga(a, n, x);
  clock_gettime(CLOCK_REALTIME, &time4);
  if (i == -1)
    printf("Element nije u nizu\n");
  else
    printf("Element je u nizu na poziciji %d\n", i);
  printf("---------------------------------\n");

  /* Interpolaciona pretraga */
  printf("Interpolaciona pretraga\n");
  clock_gettime(CLOCK_REALTIME, &time5);
  i = interpolaciona_pretraga(a, n, x);
  clock_gettime(CLOCK_REALTIME, &time6);
  if (i == -1)
    printf("Element nije u nizu\n");
  else
    printf("Element je u nizu na poziciji %d\n", i);
  printf("---------------------------------\n");

  /* Upisujemo podatke o izvrsavanju programa u log fajl */
  if ((f = fopen("vremena.txt", "a")) == NULL) {
    fprintf(stderr, "Neuspesno otvaranje log fajla.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(f, "Dimenzija niza od %d elemenata.\n", n);
  fprintf(f, "\tLinearna pretraga:%10ld ns\n",
          (time2.tv_sec - time1.tv_sec) * 1000000000 +
          time2.tv_nsec - time1.tv_nsec);
  fprintf(f, "\tBinarna: %19ld ns\n",
          (time4.tv_sec - time3.tv_sec) * 1000000000 +
          time4.tv_nsec - time3.tv_nsec);
  fprintf(f, "\tInterpolaciona: %12ld ns\n\n",
          (time6.tv_sec - time5.tv_sec) * 1000000000 +
          time6.tv_nsec - time5.tv_nsec);

  fclose(f);

  return 0;
}
