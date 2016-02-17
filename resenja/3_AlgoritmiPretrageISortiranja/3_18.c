#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *fin1 = NULL, *fin2 = NULL;
  FILE *fout = NULL;
  char ime1[11], ime2[11];
  char prezime1[16], prezime2[16];
  int kraj1 = 0, kraj2 = 0;

  /* Ako nema dovoljno arguemenata komandne linije */
  if (argc < 3) {
    fprintf(stderr, "koriscenje programa: %s datoteka1 datoteka2\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke zadate prvim argumentom komandne linije */
  fin1 = fopen(argv[1], "r");
  if (fin1 == NULL) {
    fprintf(stderr, "Neuspesno otvaranje datoteke %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke zadate drugim argumentom komandne linije */
  fin2 = fopen(argv[2], "r");
  if (fin2 == NULL) {
    fprintf(stderr, "Neuspesno otvaranje datoteke %s\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  /* Otvaranje datoteke za upis rezultata */
  fout = fopen("ceo-tok.txt", "w");
  if (fout == NULL) {
    fprintf(stderr,
            "Neuspesno otvaranje datoteke ceo-tok.txt za pisanje\n");
    exit(EXIT_FAILURE);
  }

  /* Citanje narednog studenta iz prve datoteke */
  if (fscanf(fin1, "%s%s", ime1, prezime1) == EOF)
    kraj1 = 1;

  /* Citanje narednog studenta iz druge datoteke */
  if (fscanf(fin2, "%s%s", ime2, prezime2) == EOF)
    kraj2 = 1;

  /* Sve dok nije dostignut kraj neke datoteke */
  while (!kraj1 && !kraj2) {
    int tmp = strcmp(ime1, ime2);
    if (tmp < 0 || (tmp == 0 && strcmp(prezime1, prezime2) < 0)) {
      /* Ime i prezime iz prve datoteke je leksikografski ranije, i
         biva upisano u izlaznu datoteku */
      fprintf(fout, "%s %s\n", ime1, prezime1);
      /* Citanje narednog studenta iz prve datoteke */
      if (fscanf(fin1, "%s%s", ime1, prezime1) == EOF)
        kraj1 = 1;
    } else {
      /* Ime i prezime iz druge datoteke je leksikografski ranije, i
         biva upisano u izlaznu datoteku */
      fprintf(fout, "%s %s\n", ime2, prezime2);
      /* Citanje narednog studenta iz druge datoteke */
      if (fscanf(fin2, "%s%s", ime2, prezime2) == EOF)
        kraj2 = 1;
    }
  }

  /* Ako se iz prethodne petlje izaslo zato sto je dostignut kraj
     druge datoteke, onda ima jos studenata u prvoj datoteci, koje
     treba prepisati u izlaznu, redom, jer su vec sortirani po
     imenu. */
  while (!kraj1) {
    fprintf(fout, "%s %s\n", ime1, prezime1);
    if (fscanf(fin1, "%s%s", ime1, prezime1) == EOF)
      kraj1 = 1;
  }

  /* Ako se iz prve petlje izaslo zato sto je dostignut kraj prve
     datoteke, onda ima jos studenata u drugoj datoteci, koje treba
     prepisati u izlaznu, redom, jer su vec sortirani po imenu. */
  while (!kraj2) {
    fprintf(fout, "%s %s\n", ime2, prezime2);
    if (fscanf(fin2, "%s%s", ime2, prezime2) == EOF)
      kraj2 = 1;
  }

  /* Zatvaranje datoteka */
  fclose(fin1);
  fclose(fin2);
  fclose(fout);

  exit(EXIT_SUCCESS);
}
