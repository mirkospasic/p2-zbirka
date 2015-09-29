#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "red.h"

#define VREME_ZA_PAUZU 5

int main(int argc, char **argv)
{
  /* Red je prazan. */
  Cvor *pocetak = NULL, *kraj = NULL;
  Zahtev nov_zahtev;
  Zahtev *sledeci = NULL;
  char odgovor[3];
  int broj_usluzenih = 0;
  FILE *izlaz = fopen("izvestaj.txt", "a");

  if (izlaz == NULL) {
    fprintf(stderr, "Neuspesno otvaranje datoteke izvestaj.txt\n");
    exit(EXIT_FAILURE);
  }

  /* Sluzbenik evidentira korisnicke zahteve unosenjem njihovog JMBG
     broja i opisa potrebne usluge. */
  printf("Sluzbenik evidentira korisnicke zahteve:\n");

  /* Neophodan je poziv funkcije getchar da bi se i nov red nakon
     JMBG broja procitao i da bi fgets nakon toga procitala ispravan
     red sa opisom zahteva. */
  printf("\nNovi zahtev [CTRL+D za kraj]\n\tJMBG: ");
  while (scanf("%s", nov_zahtev.jmbg) != EOF) {
    getchar();
    printf("\tOpis problema: ");
    fgets(nov_zahtev.opis, MAX - 1, stdin);
    /* Ako je poslednji karakter nov red, eliminise se. */
    if (nov_zahtev.opis[strlen(nov_zahtev.opis) - 1] == '\n')
      nov_zahtev.opis[strlen(nov_zahtev.opis) - 1] = '\0';
    dodaj_u_red(&pocetak, &kraj, &nov_zahtev);
    printf("\nNovi zahtev [CTRL+D za kraj]\n\tJMBG: ");
  }

  /* Datoteka vise nije potrebna i treba je zatvoriti. */
  fclose(izlaz);

  /* Dokle god ima korisnika u redu, treba ih usluziti. */
  while (1) {
    sledeci = pocetak_reda(pocetak);
    /* Ako nema nikog vise u redu, prekida se petlja. */
    if (sledeci == NULL)
      break;

    printf("\nSledeci je korisnik sa JMBG: %s\n", sledeci->jmbg);
    printf("i zahtevom: %s\n", sledeci->opis);

    skini_sa_reda(&pocetak, &kraj, &nov_zahtev);

    broj_usluzenih++;

    printf("\tDa li ga vracate na kraj reda? [Da/Ne] ");
    scanf("%s", odgovor);

    if (strcmp(odgovor, "Da") == 0)
      dodaj_u_red(&pocetak, &kraj, &nov_zahtev);
    else
      fprintf(izlaz, "JMBG: %s\tZahtev: %s\n", nov_zahtev.jmbg,
              nov_zahtev.opis);

    if (broj_usluzenih == VREME_ZA_PAUZU) {
      printf("\nDa li je kraj smene? [Da/Ne] ");
      scanf("%s", odgovor);

      if (strcmp(odgovor, "Da") == 0)
        break;
      else
        broj_usluzenih = 0;
    }
  }

  /******************************************************************
    Usluzivanje korisnika moze da se izvrsi i na sledeci nacin:
    
    while (skini_sa_reda(&pocetak, &kraj, &nov_zahtev)) {
      printf("\ nSledeci je korisnik sa JMBG brojem: %s\n",
            nov_zahtev.jmbg);
      printf("sa zahtevom: %s\n", nov_zahtev.opis);
      broj_usluzenih++;
      
      printf("\ tDa li ga vracate na kraj reda? [Da/Ne] ");
      scanf("%s", odgovor);
      if (strcmp(odgovor, "Da") == 0)
        dodaj_u_red(&pocetak, &kraj, &nov_zahtev);
      else
        fprintf(izlaz, "JMBG: %s\tZahtev: %s\n",
                nov_zahtev.jmbg, nov_zahtev.opis);
        
      if (broj_usluzenih == VREME_ZA_PAUZU) {
        printf("\nDa li je kraj smene? [Da/Ne] ");
        scanf("%s", odgovor);
        if (strcmp(odgovor, "Da") == 0)
          break;
        else
          broj_usluzenih = 0;
      }
    }
  *****************************************************************/

  /* Ukoliko je sluzbenik prekinuo sa radom, mozda je bilo jos
     neusluzenih korisnika, u tom slucaju treba osloboditi memoriju
     koju zauzima red sa neobradjenim zahtevima korisnika. */
  oslobodi_red(&pocetak, &kraj);

  return 0;
}
