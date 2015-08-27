#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#define MAX_NISKI 1000
#define MAX_DUZINA 30

/* Naredne dve funkcije bice koriscene za sortiranje niza nizova 
   karaktera. Svaka od njih ce biti pozivana za poredjenje dva
   elementa takvog niza, tj dva niza karaktera. Prilikom poziva
   ove funkcije za poredjenje, npr i-tog i j-tog elementa slale
   bi se, kao i inace adrese elemenata. Kako adresa niza i samo
   ime niza imaju istu vrednost, pa i slanje &niske[i] u pozivu
   funkcije je isto kao da se salje niske[i] i nije neophodno
   dalje dereferenciranje da bi se doslo do i-te niske niza. */

/* Funkcija koju koristimo za poredjenje na dve niske iz niza a
   i b su const void pokazivaci, ali kako mi znamo da cemo ovu
   funkciju koristiti za poredjenje dve niske iz niza
   eksplicitno im menjamo tipove u (char *) To je neophodno jer
   poredimo niske leksikografski i funkciji strcmp moramo
   proslediti bas char* pokazivace, da bi uporedila 2 niske. */
int poredi_leksikografski(const void *a, const void *b)
{
  return strcmp((char *) a, (char *) b);
}

/* Funkcija koju cemo prosledjivati za sortiranje niski po
   duzini. Dakle a i b ce biti uvek adrese niski koje se porede. 
   Menjamo im, eksplicitno, tip u char* jer nam treba duzina
   svake od niski, a to cemo dobiti pozivom funkcije strlen koja 
   ocekuje bas char * pokazivac. */
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

  /* Sortiramo niske leksikografski, tako sto biblioteckoj
     funkciji qsort prosledjujemo funkciju kojom se zadaje
     kriterijum poredjenja 2 niske po duzini */
  qsort(niske, n, MAX_DUZINA * sizeof(char),
        &poredi_leksikografski);

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
  p = bsearch(&x, niske, n, MAX_DUZINA * sizeof(char),
              &poredi_leksikografski);

  if (p != NULL)
    printf("Niska \"%s\" je pronadjena u nizu na poziciji %ld\n",
           p, (p - (char *) niske) / MAX_DUZINA);
  else
    printf("Niska nije pronadjena u nizu\n");

  /* Linearna pretraga */
  /* Prosledjujemo pokazivac na funkciju poredi_leksikografski
     jer nam je niz sortiran leksikografski. */
  p = lfind(&x, niske, &n, MAX_DUZINA * sizeof(char),
            &poredi_leksikografski);

  if (p != NULL)
    printf("Niska \"%s\" je pronadjena u nizu na poziciji %ld\n",
           p, (p - (char *) niske) / MAX_DUZINA);
  else
    printf("Niska nije pronadjena u nizu\n");

  /* Sada ih sortiramo po duzini i ovaj put saljemo drugu
     funkciju poredjenja */
  qsort(niske, n, MAX_DUZINA * sizeof(char), &poredi_duzine);

  printf("Niske sortirane po duzini:\n");
  for (i = 0; i < n; i++)
    printf("%s ", niske[i]);
  printf("\n");

  exit(EXIT_SUCCESS);
}
