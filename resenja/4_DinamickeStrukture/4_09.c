#include "stek.h"

int main(int argc, char **argv)
{
  /* Na pocetku, stek je prazan i etikete su uparene jer nijedna
     jos nije procitana. */
  Cvor *vrh = NULL;
  char etiketa[MAX];
  int tip;
  int uparene = 1;
  FILE *f = NULL;

  /* Ime datoteke se preuzima iz komandne linije. */
  if (argc < 2) {
    fprintf(stderr, "Greska:");
    fprintf(stderr,
            "Program se poziva sa:\n %s ime_html_datoteke\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Datoteka se otvara za citanje */
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Greska: Neuspesno otvaranje datoteke %s.\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Cita se etiketa po etiketa, sve dok ih ima u datoteci. */
  while ((tip = uzmi_etiketu(f, etiketa)) != EOF) {
    /* Ako je otvorena etiketa, stavlja se na stek. Izuzetak su
       etikete <br>, <hr> i <meta> koje nemaju sadrzaj, pa ih nije
       potrebno zatvoriti. U HTML-u postoje jos neke etikete koje
       koje nemaju sadrzaj (npr link). Zbog jednostavnosti
       pretpostavlja se da njih nema u HTML dokumentu. */
    if (tip == OTVORENA) {
      if (strcmp(etiketa, "br") != 0
          && strcmp(etiketa, "hr") != 0
          && strcmp(etiketa, "meta") != 0)
        if (potisni_na_stek(&vrh, etiketa) == 1) {
          fprintf(stderr,
                  "Greska: Neuspesna alokacija memorije za nov cvor\n");
          oslobodi_stek(&vrh);
          exit(EXIT_FAILURE);
        }
    }
    /* Ako je zatvorena etiketa, tada je uslov dobre uparenosti da
       je u pitanju zatvaranje etikete koja je poslednja otvorena,
       a jos uvek nije zatvorena. Ona se mora nalaziti na vrhu
       steka. Ako je taj uslov ispunjen, skida se sa steka, jer je
       upravo zatvorena. U suprotnom, pronadjena je nepravilnost i
       etikete nisu pravilno uparene. */
    else if (tip == ZATVORENA) {
      if (vrh_steka(vrh) != NULL
          && strcmp(vrh_steka(vrh), etiketa) == 0)
        skini_sa_steka(&vrh, NULL);
      else {
        printf("Etikete nisu pravilno uparene\n");
        printf("(nadjena je etiketa </%s>", etiketa);
        if (vrh_steka(vrh) != NULL)
          printf(", a poslednja otvorena je <%s>)\n",
                 vrh_steka(vrh));
        else
          printf(" koja nije otvorena)\n");
        uparene = 0;
        break;
      }
    }
  }
  /* Zavrseno je citanje i datoteka se zatvara */
  fclose(f);

  /* Ako do sada nije pronadjeno pogresno uparivanje, stek bi
     trebalo da bude prazan. Ukoliko nije, tada postoje etikete
     koje su ostale otvorene */
  if (uparene) {
    if (vrh_steka(vrh) == NULL)
      printf("Etikete su pravilno uparene!\n");
    else {
      printf("Etikete nisu pravilno uparene\n");
      printf("(etiketa <%s> nije zatvorena)\n", vrh_steka(vrh));
      /* Oslobadja se memorija zauzeta stekom */
      oslobodi_stek(&vrh);
    }
  }

  exit(EXIT_SUCCESS);
}
