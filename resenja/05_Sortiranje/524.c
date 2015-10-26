#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 21

/* Struktura koja predstavlja jednog studenta */
typedef struct student {
  char nalog[8];
  char ime[MAX];
  char prezime[MAX];
  int poeni;
} Student;

/* Funkcija poredi studente prema broju poena, rastuce */
int uporedi_poeni(const void *a, const void *b)
{
  Student s = *(Student *) a;
  Student t = *(Student *) b;
  return s.poeni - t.poeni;
}

/* Funkcija poredi studente prvo prema godini, zatim prema smeru i na 
   kraju prema indeksu */
int uporedi_nalog(const void *a, const void *b)
{
  Student s = *(Student *) a;
  Student t = *(Student *) b;
  /* Za svakog studenta iz naloga se izdvaja godina upisa, smer i
     broj indeksa */
  int godina1 = (s.nalog[2] - '0') * 10 + s.nalog[3] - '0';
  int godina2 = (t.nalog[2] - '0') * 10 + t.nalog[3] - '0';
  char smer1 = s.nalog[1];
  char smer2 = t.nalog[1];
  int indeks1 =
      (s.nalog[4] - '0') * 100 + (s.nalog[5] - '0') * 10 +
      s.nalog[6] - '0';
  int indeks2 =
      (t.nalog[4] - '0') * 100 + (t.nalog[5] - '0') * 10 +
      t.nalog[6] - '0';
  if (godina1 != godina2)
    return godina1 - godina2;
  else if (smer1 != smer2)
    return smer1 - smer2;
  else
    return indeks1 - indeks2;
}

int uporedi_bsearch(const void *a, const void *b)
{
  /* Nalog studenta koji se trazi */
  char *nalog = (char *) a;
  /* Kljuc pretrage */
  Student s = *(Student *) b;

  int godina1 = (nalog[2] - '0') * 10 + nalog[3] - '0';
  int godina2 = (s.nalog[2] - '0') * 10 + s.nalog[3] - '0';
  char smer1 = nalog[1];
  char smer2 = s.nalog[1];
  int indeks1 =
      (nalog[4] - '0') * 100 + (nalog[5] - '0') * 10 + nalog[6] - '0';
  int indeks2 =
      (s.nalog[4] - '0') * 100 + (s.nalog[5] - '0') * 10 +
      s.nalog[6] - '0';
  if (godina1 != godina2)
    return godina1 - godina2;
  else if (smer1 != smer2)
    return smer1 - smer2;
  else
    return indeks1 - indeks2;
}

int main(int argc, char **argv)
{
  Student *nadjen = NULL;
  char nalog_trazeni[8];
  Student niz_studenata[100];
  int i = 0, br_studenata = 0;
  FILE *in = NULL, *out = NULL;

  /* Ako je broj argumenata komandne linije razlicit i od 2 i od 3,
     korisnik nije ispravno pozvao program i prijavljuje se greska. */
  if (argc != 2 && argc != 3) {
    fprintf(stderr,
            "Greska! Program se poziva sa: ./a.out -opcija [nalog]\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke za citanje */
  in = fopen("studenti.txt", "r");
  if (in == NULL) {
    fprintf(stderr,
            "Greska prilikom otvarnja datoteke studenti.txt!\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke za pisanje */
  out = fopen("izlaz.txt", "w");
  if (out == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke izlaz.txt!\n");
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje studenta iz ulazne datoteke sve do njenog kraja */
  while (fscanf
         (in, "%s %s %s %d", niz_studenata[i].nalog,
          niz_studenata[i].ime, niz_studenata[i].prezime,
          &niz_studenata[i].poeni) != EOF)
    i++;

  br_studenata = i;

  /* Ako je prisutna opcija -p, vrsi se sortiranje po poenima */
  if (strcmp(argv[1], "-p") == 0)
    qsort(niz_studenata, br_studenata, sizeof(Student),
          &uporedi_poeni);
  /* A ako je prisutna opcija -n, vrsi se sortiranje po nalogu */
  else if (strcmp(argv[1], "-n") == 0)
    qsort(niz_studenata, br_studenata, sizeof(Student),
          &uporedi_nalog);

  /* Sortirani studenti se ispisuju u izlaznu datoteku */
  for (i = 0; i < br_studenata; i++)
    fprintf(out, "%s %s %s %d\n", niz_studenata[i].nalog,
            niz_studenata[i].ime, niz_studenata[i].prezime,
            niz_studenata[i].poeni);

  /* Ukoliko je u komandnoj liniji uz opciju -n naveden i nalog
     studenta... */
  if (argc == 3 && (strcmp(argv[1], "-n") == 0)) {
    strcpy(nalog_trazeni, argv[2]);

    /* ... pronalazi se student sa tim nalogom... */
    nadjen =
        (Student *) bsearch(nalog_trazeni, niz_studenata,
                            br_studenata, sizeof(Student),
                            &uporedi_bsearch);

    if (nadjen == NULL)
      printf("Nije nadjen!\n");
    else
      printf("%s %s %s %d\n", nadjen->nalog, nadjen->ime,
             nadjen->prezime, nadjen->poeni);
  }

  /* Zatvaranje datoteka */
  fclose(in);
  fclose(out);

  return 0;
}
