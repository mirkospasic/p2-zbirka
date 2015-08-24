#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define MAX 500

/* Struktura koja nam je neophodna za sve informacije o
   pojedinacnom studentu */
typedef struct {
  char ime[21];
  char prezime[21];
  int bodovi;
} Student;

/* Funkcija poredjenja koju cemo koristiti za sortiranje po
   broju bodova, a studente sa istim brojevem bodova dodatno
   sortiramo leksikografski po prezimenu */
int compare(const void *a, const void *b)
{
  Student *prvi = (Student *) a;
  Student *drugi = (Student *) b;

  if (prvi->bodovi > drugi->bodovi)
    return -1;
  else if (prvi->bodovi < drugi->bodovi)
    return 1;
  else
    /* Jednaki su po broju bodova, treba ih uporediti po
       prezimenu */
    return strcmp(prvi->prezime, drugi->prezime);
}

/* Funkcija za poredjenje koje ce porediti samo po broju bodova
   Prvi parametar je ono sto trazimo u nizu, ovde je to broj
   bodova, a drugi parametar ce biti element niza ciji se bodovi 
   porede. */
int compare_za_bsearch(const void *a, const void *b)
{
  int bodovi = *(int *) a;
  Student *s = (Student *) b;
  return s->bodovi - bodovi;
}

/* Funkcija za poredjenje koje ce porediti samo po prezimenu
   Prvi parametar je ono sto trazimo u nizu, ovde je to prezime, 
   * a drugi parametar ce biti element niza cije se prezime
   poredi. */
int compare_za_linearna_prezimena(const void *a, const void *b)
{
  char *prezime = (char *) a;
  Student *s = (Student *) b;
  return strcmp(prezime, s->prezime);
}


int main(int argc, char *argv[])
{
  Student kolokvijum[MAX];
  int i;
  size_t br_studenata = 0;
  Student *nadjen = NULL;
  FILE *fp = NULL;
  int bodovi;
  char prezime[21];

  /* Ako je program pozvan sa nedovoljnim brojem argumenata
     informisemo korisnika kako se program koristi i prekidamo
     izvrsavanje. */
  if (argc < 2) {
    fprintf(stderr,
            "Program se poziva sa:\n%s datoteka_sa_rezultatima\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke */
  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Neupesno otvaranje datoteke %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje sadrzaja */
  for (i = 0;
       fscanf(fp, "%s%s%d", kolokvijum[i].ime,
              kolokvijum[i].prezime,
              &kolokvijum[i].bodovi) != EOF; i++);

  /* Zatvaranje datoteke */
  fclose(fp);
  br_studenata = i;

  /* Sortiramo niz studenata po broju bodova, pa unutar grupe
     studenata sa istim brojem bodova sortiranje se vrsi po
     prezimenu */
  qsort(kolokvijum, br_studenata, sizeof(Student), &compare);

  printf("Studenti sortirani po broju poena opadajuce, ");
  printf("pa po prezimenu rastuce:\n");
  for (i = 0; i < br_studenata; i++)
    printf("%s %s  %d\n", kolokvijum[i].ime,
           kolokvijum[i].prezime, kolokvijum[i].bodovi);

  /* Pretrazivanje studenata po broju bodova se vrsi binarnom
     pretragom jer je niz sortiran po broju bodova. */
  printf("Unesite broj bodova: ");
  scanf("%d", &bodovi);

  nadjen =
      bsearch(&bodovi, kolokvijum, br_studenata, sizeof(Student),
              &compare_za_bsearch);

  if (nadjen != NULL)
    printf
        ("Pronadjen je student sa unetim  brojem bodova: %s %s %d\n",
         nadjen->ime, nadjen->prezime, nadjen->bodovi);
  else
    printf("Nema studenta sa unetim brojem bodova\n");

  /* Pretraga po prezimenu se mora vrsiti linearnom pretragom
     jer nam je niz sortiran po bodovima, globalno gledano. */
  printf("Unesite prezime: ");
  scanf("%s", prezime);

  nadjen =
      lfind(prezime, kolokvijum, &br_studenata, sizeof(Student),
            &compare_za_linearna_prezimena);

  if (nadjen != NULL)
    printf
        ("Pronadjen je student sa unetim prezimenom: %s %s %d\n",
         nadjen->ime, nadjen->prezime, nadjen->bodovi);
  else
    printf("Nema studenta sa unetim prezimenom\n");

  return 0;
}
