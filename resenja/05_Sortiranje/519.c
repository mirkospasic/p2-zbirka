#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#define MAX_NISKI 1000
#define MAX_DUZINA 30

/******************************************************************
  Niz nizova karaktera ovog potpisa
  char niske[3][4];
  se moze graficki predstaviti ovako:
  ----------------------------------------------------
  | a | b | c |\0 || d | e | \0|   || f | g | h | \0||
  ----------------------------------------------------
  Dakle kao tri reci (abc, de, fgh), nadovezane jedna na drugu. Za
  svaku je rezervisano po 4 karaktera ukljucujuci \0. Druga rec sa
  nalazi na adresi koja je za 4 veca od prve reci, a za 4 manja od
  adrese na kojoj se nalazi treca rec. Adresa i-te reci je niske[i]
  i ona je tipa char*.
  
  Kako pokazivaci a i b u sledecoj funkciji sadrze adrese elemenata
  koji trebaju biti uporedjeni, (npr. pri porecenju prve i poslednje
  reci, pokazivac a ce pokazivati na slovo 'a', a pokazivac b na
  slovo 'f') treba ih kastovati na char*, i pozvati funkciju strcmp
  nad njima.
*******************************************************************/
int poredi_leksikografski(const void *a, const void *b)
{
  return strcmp((char *) a, (char *) b);
}

/* Funkcija slicna prethodnoj, osim sto elemente ne uporedjuje
   leksikografski, vec po duzini */
int poredi_duzine(const void *a, const void *b)
{
  return strlen((char *) a) - strlen((char *) b);
}

int main()
{
  int i;
  size_t n;
  FILE *fp = NULL;
  char niske[MAX_NISKI][MAX_DUZINA];
  char *p = NULL;
  char x[MAX_DUZINA];

  /* Otvaranje datoteke */
  if ((fp = fopen("niske.txt", "r")) == NULL) {
    fprintf(stderr, "Neupesno otvaranje datoteke niske.txt.\n");
    exit(EXIT_FAILURE);
  }

  /* Citanje sadrzaja datoteke */
  for (i = 0; fscanf(fp, "%s", niske[i]) != EOF; i++);

  /* Zatvaranje datoteke */
  fclose(fp);
  n = i;

  /* Sortiranje niski leksikografski. Biblioteckoj funkciji qsort
     prosledjuje se funkcija kojom se zadaje kriterijum poredjenja 2
     niske po duzini */
  qsort(niske, n, MAX_DUZINA * sizeof(char), &poredi_leksikografski);

  printf("Leksikografski sortirane niske:\n");
  for (i = 0; i < n; i++)
    printf("%s ", niske[i]);
  printf("\n");

  /* Unos trazene niske */
  printf("Uneti trazenu nisku: ");
  scanf("%s", x);

  /* Binarna pretraga */
  /* Prosledjuje se pokazivac na funkciju poredi_leksikografski jer
     je niz vec sortiran leksikografski. */
  p = bsearch(&x, niske, n, MAX_DUZINA * sizeof(char),
              &poredi_leksikografski);

  if (p != NULL)
    printf("Niska \"%s\" je pronadjena u nizu na poziciji %ld\n",
           p, (p - (char *) niske) / MAX_DUZINA);
  else
    printf("Niska nije pronadjena u nizu\n");

  /* Linearna pretraga */
  p = lfind(&x, niske, &n, MAX_DUZINA * sizeof(char),
            &poredi_leksikografski);

  if (p != NULL)
    printf("Niska \"%s\" je pronadjena u nizu na poziciji %ld\n",
           p, (p - (char *) niske) / MAX_DUZINA);
  else
    printf("Niska nije pronadjena u nizu\n");

  /* Sortiranje po duzini */
  qsort(niske, n, MAX_DUZINA * sizeof(char), &poredi_duzine);

  printf("Niske sortirane po duzini:\n");
  for (i = 0; i < n; i++)
    printf("%s ", niske[i]);
  printf("\n");

  exit(EXIT_SUCCESS);
}
