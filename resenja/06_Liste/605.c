#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

#define OTVORENA 1
#define ZATVORENA 2

#define VAN_ETIKETE 0
#define PROCITANO_MANJE 1
#define U_ETIKETI 2

/* Struktura kojim se predstavlja cvor liste sadrzi ime etikete i
   pokazivac na sledeci cvor. */
typedef struct cvor {
  char etiketa[MAX];
  struct cvor *sledeci;
} Cvor;

/* Funkcija kreira novi cvor, upisuje u njega etiketu i vraca njegovu 
   adresu ili NULL ako alokacija nije bila uspesna. */
Cvor *napravi_cvor(char *etiketa)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja u novom cvoru */
  if (strlen(etiketa) >= MAX) {
    fprintf(stderr, "Etiketa je preduga, bice skracena.\n");
    etiketa[MAX - 1] = '\0';
  }
  strcpy(novi->etiketa, etiketa);
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja memoriju zauzetu stekom. */
void oslobodi_stek(Cvor ** adresa_vrha)
{
  Cvor *pomocni;
  while (*adresa_vrha != NULL) {
    pomocni = *adresa_vrha;
    *adresa_vrha = (*adresa_vrha)->sledeci;
    free(pomocni);
  }
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi i
   ukoliko alokacija nije bila uspesna, oslobadja se sva prethodno
   zauzeta memorija za listu ciji se pokazivac vrh nalazi na adresi
   adresa_vrha. */
void proveri_alokaciju(Cvor ** adresa_vrha, Cvor * novi)
{
  if (novi == NULL) {
    fprintf(stderr, "Neuspela alokacija za nov cvor\n");
    oslobodi_stek(adresa_vrha);
    exit(EXIT_FAILURE);
  }
}

/* Funkcija postavlja na vrh steka novu etiketu. */
void potisni_na_stek(Cvor ** adresa_vrha, char *etiketa)
{
  Cvor *novi = napravi_cvor(etiketa);
  proveri_alokaciju(adresa_vrha, novi);
  novi->sledeci = *adresa_vrha;
  *adresa_vrha = novi;
}

/* Funkcija skida sa vrha steka etiketu. Ako je drugi argument
   pokazivac razlicit od NULL, tada u niz karaktera na koji on
   pokazuje upisuje ime etikete koja je upravo skinuta sa steka dok u 
   suprotnom ne radi nista. Funkcija vraca 0 ako je stek prazan (pa
   samim tim nije bilo moguce skinuti vrednost sa steka) ili 1 u
   suprotnom. */
int skini_sa_steka(Cvor ** adresa_vrha, char *etiketa)
{
  Cvor *pomocni;

  /* Pokusaj skidanja vrednost sa vrha praznog steka rezultuje
     greskom i vraca se 0. */
  if (*adresa_vrha == NULL)
    return 0;

  /* Ako adresa na koju se smesta etiketa nije NULL, onda se na tu
     adresu kopira etiketa sa vrha steka. */
  if (etiketa != NULL)
    strcpy(etiketa, (*adresa_vrha)->etiketa);

  /* Element sa vrha steka se uklanja. */
  pomocni = *adresa_vrha;
  *adresa_vrha = (*adresa_vrha)->sledeci;
  free(pomocni);

  return 1;
}

/* Funkcija vraca pokazivac na string koji sadrzi etiketu na vrhu
   steka. Ukoliko je stek prazan, vraca NULL. */
char *vrh_steka(Cvor * vrh)
{
  if (vrh == NULL)
    return NULL;
  return vrh->etiketa;
}

/* Funkcija prikazuje stek pocev od vrha prema dnu. */
void prikazi_stek(Cvor * vrh)
{
  for (; vrh != NULL; vrh = vrh->sledeci)
    printf("<%s>\n", vrh->etiketa);
}

/* Funkcija iz datoteke kojoj odgovara pokazivac f cita sledecu
   etiketu, i upisuje je u nisku na koju pokazuje pokazivac etiketa.
   Vraca EOF u slucaju da se dodje do kraja datoteke pre nego sto se
   procita etiketa. Vraca OTVORENA, ako je procitana otvorena
   etiketa, odnosno ZATVORENA, ako je procitana zatvorena etiketa. */
int uzmi_etiketu(FILE * f, char *etiketa)
{
  int c;
  int i = 0;
  /* Stanje predstavlja informaciju dokle se stalo sa citanjem
     etikete. Inicijalizuje se vrednoscu VAN_ETIKETE jer jos uvek
     nije zapoceto citanje. */
  /* Tip predstavlja informaciju o tipu etikete. Uzima vrednosti
     OTVORENA ili ZATVORENA. */
  int stanje = VAN_ETIKETE;
  int tip;

  /* HTML je neosetljiv na razliku izmedju malih i velikih slova, dok 
     to u C-u ne vazi. Zato ce sve etikete biti prevedene u zapis
     samo malim slovima. */
  while ((c = fgetc(f)) != EOF) {
    switch (stanje) {
    case VAN_ETIKETE:
      if (c == '<')
        stanje = PROCITANO_MANJE;
      break;
    case PROCITANO_MANJE:
      if (c == '/') {
        /* Cita se zatvorena etiketa. */
        tip = ZATVORENA;
      } else {
        if (isalpha(c)) {
          /* Cita se otvorena etiketa */
          tip = OTVORENA;
          etiketa[i++] = tolower(c);
        }
      }
      /* Od sada se cita etiketa i zato se menja stanje. */
      stanje = U_ETIKETI;
      break;
    case U_ETIKETI:
      if (isalpha(c) && i < MAX - 1) {
        /* Ako je procitani karakter slovo i nije premasena
           dozvoljena duzina etikete, procitani karakter se smanjuje
           i smesta u etiketu. */
        etiketa[i++] = tolower(c);
      } else {
        /* Inace, staje se sa citanjem etikete. Korektno se zavrsava
           niska koja sadrzi procitanu etiketu i vraca se njen tip. */
        etiketa[i] = '\0';
        return tip;
      }
      break;
    }
  }
  /* Doslo se do kraja datoteke pre nego sto je procitana naredna
     etiketa i vraca se EOF. */
  return EOF;
}

int main(int argc, char **argv)
{
  /* Na pocetku, stek je prazan i etikete su uparene jer nijedna jos
     nije procitana. */
  Cvor *vrh = NULL;
  char etiketa[MAX];
  int tip;
  int uparene = 1;
  FILE *f = NULL;

  /* Ime datoteke se preuzima iz komandne linije. */
  if (argc < 2) {
    fprintf(stderr, "Koriscenje: %s ime_html_datoteke\n", argv[0]);
    exit(0);
  }

  /* Datoteka se otvara za citanje. */
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke %s.\n",
            argv[1]);
    exit(1);
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
        potisni_na_stek(&vrh, etiketa);
    }
    /* Ako je zatvorena etiketa, tada je uslov dobre uparenosti da je 
       u pitanju zatvaranje etikete koja je poslednja otvorena, a jos 
       uvek nije zatvorena. Ona se mora nalaziti na vrhu steka. Ako
       je taj uslov ispunjen, skida se sa steka, jer je upravo
       zatvorena. U suprotnom, pronadjena je nepravilnost i etikete
       nisu pravilno uparene. */
    else if (tip == ZATVORENA) {
      if (vrh_steka(vrh) != NULL
          && strcmp(vrh_steka(vrh), etiketa) == 0)
        skini_sa_steka(&vrh, NULL);
      else {
        printf("Etikete nisu pravilno uparene\n");
        printf("(nadjena je etiketa </%s>", etiketa);
        if (vrh_steka(vrh) != NULL)
          printf(", a poslednja otvorena je <%s>)\n", vrh_steka(vrh));
        else
          printf(" koja nije otvorena)\n");
        uparene = 0;
        break;
      }
    }
  }
  /* Zavrseno je citanje datoteke i zatvara se. */
  fclose(f);

  /* Ako do sada nije pronadjeno pogresno uparivanje, stek bi trebalo 
     da bude prazan. Ukoliko nije, tada postoje etikete koje su
     ostale otvorene. */
  if (uparene) {
    if (vrh_steka(vrh) == NULL)
      printf("Etikete su pravilno uparene!\n");
    else {
      printf("Etikete nisu pravilno uparene\n");
      printf("(etiketa <%s> nije zatvorena)\n", vrh_steka(vrh));
      /* Oslobadja se memorija zauzeta stekom. */
      oslobodi_stek(&vrh);
    }
  }
  return 0;
}
