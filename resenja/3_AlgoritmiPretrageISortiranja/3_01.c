#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000000

/* Pri prevodjenju program linkovati sa bibliotekom librt opcijom
   -lrt zbog funkcije clock_gettime() */

/* Linearna pretraga: Funkcija pretrazuje niz a[] celih brojeva
   duzine n, trazeci u njemu prvo pojavljivanje elementa x. Pretraga
   se vrsi prostom iteracijom kroz niz. Ako se element pronadje
   funkcija vraca indeks pozicije na kojoj je pronadjen. Ovaj indeks
   je uvek nenegativan. Ako element nije pronadjen u nizu, funkcija
   vraca -1, kao indikator neuspesne pretrage. */
int linearna_pretraga(int a[], int n, int x)
{
  int i;
  for (i = 0; i < n; i++)
    if (a[i] == x)
      return i;
  return -1;
}

/* Binarna pretraga: Funkcija trazi u sortiranom nizu a[] duzine n
   broj x. Vraca indeks pozicije nadjenog elementa ili -1, ako
   element nije pronadjen. */
int binarna_pretraga(int a[], int n, int x)
{
  int levi = 0;
  int desni = n - 1;
  int srednji;
  /* Dokle god je indeks levi levo od indeksa desni */
  while (levi <= desni) {
    /* Srednji indeks je njihova aritmeticka sredina */
    srednji = (levi + desni) / 2;
    /* Ako je element sa sredisnjim indeksom veci od x, tada se x
       mora nalaziti u levom delu niza */
    if (x < a[srednji])
      desni = srednji - 1;
    /* Ako je element sa sredisnjim indeksom manji od x, tada se x
       mora nalaziti u desnom delu niza */
    else if (x > a[srednji])
      levi = srednji + 1;
    else
      /* Ako je element sa sredisnjim indeksom jednak x, tada je broj
         x pronadjen na poziciji srednji */
      return srednji;
  }
  /* Ako element x nije pronadjen, vraca se -1 */
  return -1;
}

/* Interpolaciona pretraga: Funkcija trazi u sortiranom nizu a[]
   duzine n broj x. Vraca indeks pozicije nadjenog elementa ili -1,
   ako element nije pronadjen */
int interpolaciona_pretraga(int a[], int n, int x)
{
  int levi = 0;
  int desni = n - 1;
  int srednji;
  /* Dokle god je indeks levi levo od indeksa desni...  */
  while (levi <= desni) {
    /* Ako je trazeni element manji od pocetnog ili veci od
       poslednjeg elementa u delu niza a[levi],...,a[desni], tada on
       nije u tom delu niza. Ova provera je neophodna, da se ne bi
       dogodilo da se prilikom izracunavanja indeksa srednji izadje
       izvan opsega indeksa [levi,desni] */
    if (x < a[levi] || x > a[desni])
      return -1;
    /* U suprotnom, x je izmedju a[levi] i a[desni], pa ako su
       a[levi] i a[desni] jednaki, tada je jasno da je trazeni broj x 
       jednak ovim vrednostima, pa se vraca indeks levi (ili indeks
       desni). Ova provera je neophodna, jer bi se u suprotnom
       prilikom izracunavanja indeksa srednji pojavilo deljenje
       nulom. */
    else if (a[levi] == a[desni])
      return levi;
    /* Racunanje srednjeg indeksa */
    srednji =
        levi +
        (int) ((double) (x - a[levi]) / (a[desni] - a[levi]) *
               (desni - levi));
    /* Napomena: Indeks srednji je uvek izmedju levi i desni, ali ce
       verovatno biti blize trazenoj vrednosti nego da je prosto uvek 
       uzimana aritmiticka sredina indeksa levi i desni. Ovo se moze
       porediti sa pretragom recnika: ako neko trazi rec na slovo
       'B', sigurno nece da otvori recnik na polovini, vec verovatno
       negde blize pocetku. */
    /* Ako je element sa indeksom srednji veci od trazenog, tada se
       trazeni element mora nalaziti u levoj polovini niza */
    if (x < a[srednji])
      desni = srednji - 1;
    /* Ako je element sa indeksom srednji manji od trazenog, tada se
       trazeni element mora nalaziti u desnoj polovini niza */
    else if (x > a[srednji])
      levi = srednji + 1;
    else
      /* Ako je element sa indeksom srednji jednak trazenom, onda se
         pretraga zavrsava na poziciji srednji */
      return srednji;
  }
  /* U slucaju neuspesne pretrage vraca se -1 */
  return -1;
}

int main(int argc, char **argv)
{
  int a[MAX];
  int n, i, x;
  struct timespec vreme1, vreme2, vreme3, vreme4, vreme5, vreme6;
  FILE *f;
  /* Provera argumenata komandne linije */
  if (argc != 3) {
    fprintf(stderr,
            "koriscenje programa: %s dim_niza trazeni_br\n", argv[0]);
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
  /* Elementi niza se generisu slucajno, tako da je svaki sledeci
     veci od prethodnog. srandom() funkcija obezbedjuje novi seed za
     pozivanje random() funkcije. Kako generisani niz ne bi uvek isto 
     izgledao, seed se postavlja na tekuce vreme u sekundama od Nove
     godine 1970. random()%100 daje brojeve izmedju 0 i 99 */
  srandom(time(NULL));
  for (i = 0; i < n; i++)
    a[i] = i == 0 ? random() % 100 : a[i - 1] + random() % 100;
  /* Lineara pretraga */
  printf("Linearna pretraga:\n");
  /* Vreme proteklo od Nove godine 1970 */
  clock_gettime(CLOCK_REALTIME, &vreme1);
  i = linearna_pretraga(a, n, x);
  /* Novo vreme i razlika sa prvim predstavlja vreme utroseno za
     linearnu pretragu */
  clock_gettime(CLOCK_REALTIME, &vreme2);
  if (i == -1)
    printf("Element nije u nizu\n");
  else
    printf("Element je u nizu na poziciji %d\n", i);
  /* Binarna pretraga */
  printf("Binarna pretraga:\n");
  clock_gettime(CLOCK_REALTIME, &vreme3);
  i = binarna_pretraga(a, n, x);
  clock_gettime(CLOCK_REALTIME, &vreme4);
  if (i == -1)
    printf("Element nije u nizu\n");
  else
    printf("Element je u nizu na poziciji %d\n", i);
  /* Interpolaciona pretraga */
  printf("Interpolaciona pretraga:\n");
  clock_gettime(CLOCK_REALTIME, &vreme5);
  i = interpolaciona_pretraga(a, n, x);
  clock_gettime(CLOCK_REALTIME, &vreme6);
  if (i == -1)
    printf("Element nije u nizu\n");
  else
    printf("Element je u nizu na poziciji %d\n", i);
  /* Podaci o izvrsavanju programa bivaju upisani u log fajl */
  if ((f = fopen("vremena.txt", "a")) == NULL) {
    fprintf(stderr, "Neuspesno otvaranje log fajla.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(f, "Dimenzija niza: %d\n", n);
  fprintf(f, "\tLinearna:%10ld ns\n",
          (vreme2.tv_sec - vreme1.tv_sec) * 1000000000 +
          vreme2.tv_nsec - vreme1.tv_nsec);
  fprintf(f, "\tBinarna: %19ld ns\n",
          (vreme4.tv_sec - vreme3.tv_sec) * 1000000000 +
          vreme4.tv_nsec - vreme3.tv_nsec);
  fprintf(f, "\tInterpolaciona: %12ld ns\n\n",
          (vreme6.tv_sec - vreme5.tv_sec) * 1000000000 +
          vreme6.tv_nsec - vreme5.tv_nsec);
  /* Zatvaranje datoteke */
  fclose(f);
  exit(EXIT_SUCCESS);
}
