#include<stdio.h>
#include<stdlib.h>

#define MAX_KARAKTERA 100

/* Implementacija funkcije strcpy() iz standardne biblioteke */
void kopiranje_niske(char *dest, char *src)
{
  int i;
  for (i = 0; *(src + i); i++)
    *(dest + i) = *(src + i);
}

/* Implementacija funkcije strcmp() iz standardne biblioteke */
int poredjenje_niski(char *s, char *t)
{
  int i;
  for (i = 0; *(s + i) == *(t + i); i++)
    if (*(s + i) == '\0')
      return 0;
  return *(s + i) - *(t + i);
}

/* Implementacija funkcije strlen() iz standardne biblioteke */
int duzina_niske(char *s)
{
  int i;
  for (i = 0; *(s + i); i++);
  return i;
}

/* Funkcija ispituje da li je niska zadata drugim argumentom
   funkcije sufiks niske zadate prvi argumentom funkcije */
int sufiks_niske(char *niska, char *sufiks)
{
  if (duzina_niske(sufiks) <= duzina_niske(niska) &&
      poredjenje_niski(niska + duzina_niske(niska) -
                       duzina_niske(sufiks), sufiks) == 0)
    return 1;
  return 0;
}

/* Funkcija ispituje da li je niska zadata drugim argumentom
   funkcije prefiks niske zadate prvi argumentom funkcije */
int prefiks_niske(char *niska, char *prefiks)
{
  int i;
  if (duzina_niske(prefiks) <= duzina_niske(niska)) {
    for (i = 0; i < duzina_niske(prefiks); i++)
      if (*(prefiks + i) != *(niska + i))
        return 0;
    return 1;
  } else
    return 0;
}

int main(int argc, char **argv)
{
  /* Ukoliko korisnik nije uneo trazene argumente, prijavljuje se
     greska */
  if (argc < 4) {
    printf("Greska: ");
    printf("Nedovoljan broj argumenata komandne linije.\n");
    printf("Program se poziva sa %s ime_dat suf/pref -s/-p.\n",
           argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *in;
  int br = 0;
  char rec[MAX_KARAKTERA];

  in = fopen(*(argv + 1), "r");
  if (in == NULL) {
    fprintf(stderr, "Greska: ");
    fprintf(stderr, "Neuspesno otvaranje datoteke %s.\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Provera se opcija kojom je pozvan program a zatim se
     ucitavaju reci iz datoteke i broji se koliko njih zadovoljava
     trazeni uslov */
  if (!(poredjenje_niski(*(argv + 3), "-s"))) {
    while (fscanf(in, "%s", rec) != EOF)
      br += sufiks_niske(rec, *(argv + 2));
	printf("Broj reci koje se zavrsavaju na %s je %d.\n", *(argv + 2), br);
  } else if (!(poredjenje_niski(*(argv + 3), "-p"))) {
    while (fscanf(in, "%s", rec) != EOF)
      br += prefiks_niske(rec, *(argv + 2));
    printf("Broj reci koje pocinju na %s je %d.\n", *(argv + 2), br);
  }
  
  fclose(in);
  return 0;
}
