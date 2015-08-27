#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#define MAX_NISKI 1000
#define MAX_DUZINA 30

/************************************************************
  Niz pokazivaca na karaktere ovog potpisa
  char *niske[3];
  posle alokacije u main-u se moze graficki predstaviti ovako:
  -----                    -----------------
  | X | --------------->   | a | b | c | \0|
  -----                    =================
  | Y | --------------->   | d | e | \0|
  -----                    =================
  | Z | --------------->   | f | g | h | \0|
  -----                    -----------------
  Sa leve strane je vertikalno prikazan niz pokazivaca, gde
  je i-ti njegov element pokazivac koji pokazuje na alocirane
  karaktere i-te reci. Njegov tip je char*.

  Kako pokazivaci a i b u sledecoj funkciji sadrze adrese
  elemenata koji trebaju biti uporedjeni (recimo adresu od X
  i adresu od Z), i kako su X i Z tipa char*, onda a i b su
  tipa char**, pa ih tako moramo i kastovati. Da bi uporedili
  leksikografski elemente X i Z, moramo uporediti stringove
  na koje oni pokazuju, pa zato u sledecoj funkciji pozivamo
  strcmp() nad onim na sta pokazuju a i b, kastovani na
  odgovarajuci tip.
*************************************************************/
int poredi_leksikografski(const void *a, const void *b)
{
  return strcmp(*(char **) a, *(char **) b);
}

/* Funkcija slicna prethodnoj, osim sto elemente ne uporedjuje
   leksikografski, vec po duzini */
int poredi_duzine(const void *a, const void *b)
{
  return strlen(*(char **) a) - strlen(*(char **) b);
}

/* Ovo je funkcija poredjenja za bsearch. Pokazivac b pokazuje
   na element u nizu sa kojim se poredi, pa njega treba
   kastovati na char** i dereferencirati, (videti obrazlozenje
   za prvu funkciju u ovom zadatku, a pokazivac a pokazuje na
   element koji se trazi. U main funkciji je to x, koji je tipa
   char*, tako da pokazivac a ovde samo kastujemo i ne
   dereferenciramo. */
int poredi_leksikografski_b(const void *a, const void *b)
{
  return strcmp((char *) a, *(char **) b);
}

int main()
{
  int i;
  size_t n;
  FILE *fp = NULL;
  char *niske[MAX_NISKI];
  char **p = NULL;
  char x[MAX_DUZINA];

  /* Otvaranje datoteke */
  if ((fp = fopen("niske.txt", "r")) == NULL) {
    fprintf(stderr, "Neupesno otvaranje datoteke niske.txt.\n");
    exit(EXIT_FAILURE);
  }

  /* Citanje sadrzaja datoteke */
  i = 0;
  while (fscanf(fp, "%s", x) != EOF) {
    /* Alociranje dovoljne memorije za i-tu nisku */
    if ((niske[i] = malloc(strlen(x) * sizeof(char))) == NULL) {
      fprintf(stderr, "Greska pri alociranju niske\n");
      exit(EXIT_FAILURE);
    }
    /* Kopiranje procitane niske na svoje mesto */
    strcpy(niske[i], x);
    i++;
  }

  /* Zatvaranje datoteke */
  fclose(fp);
  n = i;

  /* Sortiramo niske leksikografski, tako sto biblioteckoj
     funkciji qsort prosledjujemo funkciju kojom se zadaje
     kriterijum poredjenja 2 niske po duzini */
  qsort(niske, n, sizeof(char *), &poredi_leksikografski);

  printf("Leksikografski sortirane niske:\n");
  for (i = 0; i < n; i++)
    printf("%s ", niske[i]);
  printf("\n");

  /* Unosimo trazeni nisku */
  printf("Uneti trazenu nisku: ");
  scanf("%s", x);

  /* Binarna pretraga */
  /* Prosledjujemo pokazivac na funkciju poredi_leksikografski
     jer nam je niz sortiran leksikografski. */
  p = bsearch(x, niske, n, sizeof(char *),
              &poredi_leksikografski_b);

  if (p != NULL)
    printf("Niska \"%s\" je pronadjena u nizu na poziciji %ld\n",
           *p, p - niske);
  else
    printf("Niska nije pronadjena u nizu\n");

  /* Linearna pretraga */
  /* Prosledjujemo pokazivac na funkciju poredi_leksikografski
     jer nam je niz sortiran leksikografski. */
  p = lfind(x, niske, &n, sizeof(char *),
            &poredi_leksikografski_b);

  if (p != NULL)
    printf("Niska \"%s\" je pronadjena u nizu na poziciji %ld\n",
           *p, p - niske);
  else
    printf("Niska nije pronadjena u nizu\n");

  /* Sada ih sortiramo po duzini i ovaj put saljemo drugu
     funkciju poredjenja */
  qsort(niske, n, sizeof(char *), &poredi_duzine);

  printf("Niske sortirane po duzini:\n");
  for (i = 0; i < n; i++)
    printf("%s ", niske[i]);
  printf("\n");

  /* Oslobadjanje zauzete memorije */
  for (i = 0; i < n; i++)
    free(niske[i]);

  exit(EXIT_SUCCESS);
}
