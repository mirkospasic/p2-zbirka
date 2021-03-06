#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IME_DATOTEKE 50
#define MAX_CIFARA 13
#define MAX_IME_I_PREZIME 100

/* Struktura kojom se opisuje cvor stabla: sadrzi ime i prezime,
   broj telefona i redom pokazivace na levo i desno podstablo */
typedef struct cvor {
  char ime_i_prezime[MAX_IME_I_PREZIME];
  char telefon[MAX_CIFARA];
  struct cvor *levo;
  struct cvor *desno;
} Cvor;

/* Funkcija koja kreira novi cvora stabla */
Cvor *napravi_cvor(char *ime_i_prezime, char *telefon)
{
  /* Alocira se memorija za novi cvor i proverava se uspesnost
     alokacije */
  Cvor *novi_cvor = (Cvor *) malloc(sizeof(Cvor));
  if (novi_cvor == NULL)
    return NULL;

  /* Inicijalizuju se polja novog cvora */
  strcpy(novi_cvor->ime_i_prezime, ime_i_prezime);
  strcpy(novi_cvor->telefon, telefon);
  novi_cvor->levo = NULL;
  novi_cvor->desno = NULL;

  /* Vraca se adresa novog cvora */
  return novi_cvor;
}

/* Funkcija koja dodaje novu osobu i njen broj telefona u stablo.
   Ukoliko je dodavanje uspesno povratna vrednost funkcije je 0,
   dok je u suprotnom povratna vrednost 1 */
int
dodaj_u_stablo(Cvor ** adresa_korena, char *ime_i_prezime,
               char *telefon)
{
  /* Ako je stablo prazno */
  if (*adresa_korena == NULL) {
    /* Kreira se novi cvor */
    Cvor *novi_cvor = napravi_cvor(ime_i_prezime, telefon);
    /* Proverava se uspesnost kreiranja novog cvora */
    if (novi_cvor == NULL) {
      /* Ako je doslo do greske, vraca se odgovarajuca vrednost */
      return 1;
    }

    /* Inace, novi cvor se proglasava korenom stabla */
    *adresa_korena = novi_cvor;

    /* I vraca se indikator uspesnog dodavanja */
    return 0;
  }

  /* Ako stablo nije prazno, trazi se odgovarajuca pozicija za novi
     unos. Kako pretragu treba vrsiti po imenu i prezimenu, stablo
     treba da bude pretrazivacko po ovom polju.

     Ako je zadato ime i prezime leksikografski manje od imena i
     prezimena koje se nalazi u korenu, podaci se dodaju u levo
     podstablo */
  if (strcmp(ime_i_prezime, (*adresa_korena)->ime_i_prezime)
      < 0)
    return dodaj_u_stablo(&(*adresa_korena)->levo, ime_i_prezime,
                          telefon);
  else
    /* Ako je zadato ime i prezime leksikografski vece od imena i
       prezimena sadrzanog u korenu, podaci se dodaju u desno
       podstablo */
  if (strcmp(ime_i_prezime, (*adresa_korena)->ime_i_prezime) > 0)
    return dodaj_u_stablo(&(*adresa_korena)->desno, ime_i_prezime,
                          telefon);

  /* Pretostavka zadatka je da nema istih imena i prezimena u
     datoteci, pa se sledeca naredba nikada neci ni izvrsiti */
  return 0;
}

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** adresa_korena)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*adresa_korena == NULL)
    return;

  /* Oslobadja se memorija zauzeta levim podstablom */
  oslobodi_stablo(&(*adresa_korena)->levo);

  /* Oslobadja se memorija zauzeta desnim podstablom */
  oslobodi_stablo(&(*adresa_korena)->desno);

  /* Oslobadja se memorija zauzeta korenom */
  free(*adresa_korena);

  /* Stablo se proglasava praznim */
  *adresa_korena = NULL;
}

/* Funkcija koja ispisuje imenik u leksikografskom poretku */
/* Napomena: ova funkcija nije trazena u zadatku ali se moze
   koristiti za proveru da li je stablo uspesno kreirano. */
void prikazi_stablo(Cvor * koren)
{
  /* Ako je stablo prazno, zavrsava se sa ispisom */
  if (koren == NULL)
    return;

  /* Zbog leksikografskog poretka, prvo se ispisuju podaci iz levog
     podstabla */
  prikazi_stablo(koren->levo);

  /* Zatim se ispisuju podaci iz korena */
  printf("%s: %s\n", koren->ime_i_prezime, koren->telefon);

  /* I nastavlja se sa ispisom podataka iz desnog podstabla */
  prikazi_stablo(koren->desno);
}

/* Funkcija ucitava sledeci kontakt iz zadate datoteke i upisuje
   ime i prezime i broj telefona u odgovarajuce nizove. Vraca EOF
   ako nema vise kontakata ili 0 u suprotnom. Maksimalna duzina
   imena i prezimena odredjena je konstantom MAX_IME_PREZIME, a
   maksimalna duzina broja telefona konstantom MAX_CIFARA.  */
int procitaj_kontakt(FILE * f, char *ime_i_prezime, char *telefon)
{
  /* Karakter koji se cita */
  int c;

  /* Indeks pozicije na koju se smesta procitani karakter */
  int i = 0;

  /* Linije datoteke koje se obradjuju su formata Ime Prezime
     BrojTelefona */

  /* Preskacu se eventualne praznine sa pocetka linije datoteke */
  while ((c = fgetc(f)) != EOF && isspace(c));

  /* Prvo procitano slovo se upisuje u ime i prezime */
  if (!feof(f))
    ime_i_prezime[i++] = c;

  /* Naznaka kraja citanja imena i prezimena ce biti pojava prve
     cifre tako da se citanje vrsi sve dok se ne naidje na cifru.
     Pritom treba voditi racuna da li ima dovoljno mesta za
     smestanje procitanog karaktera i da se slucajno ne dodje do
     kraja datoteke */
  while (i < MAX_IME_I_PREZIME - 1 && (c = fgetc(f)) != EOF) {
    if (!isdigit(c))
      ime_i_prezime[i++] = c;
    else if (i > 0)
      break;
  }

  /* Upisuje se terminirajuca nula na mesto poslednjeg procitanog
     blanko karaktera */
  ime_i_prezime[--i] = '\0';

  /* I pocinje se sa citanjem broja telefona */
  i = 0;

  /* Upisuje se cifra koja je vec procitana */
  telefon[i++] = c;

  /* I citaju se preostale cifre. Naznaka kraja ce biti pojava
     karaktera cije prisustvo nije dozvoljeno u broju telefona */
  while (i < MAX_CIFARA - 1 && (c = fgetc(f)) != EOF)
    if (c == '/' || c == '-' || isdigit(c))
      telefon[i++] = c;
    else
      break;

  /* Upisuje se terminirajuca nula */
  telefon[i] = '\0';

  /* Vraca se 0 ako je uspesno procitan kontakt ili EOF u suprotnom 
   */
  return !feof(f) ? 0 : EOF;
}

/* Funkcija koja trazi u imeniku osobu sa zadatim imenom i
   prezimenom */
Cvor *pretrazi_imenik(Cvor * koren, char *ime_i_prezime)
{
  /* Ako je imenik prazan, zavrsava se sa pretragom */
  if (koren == NULL)
    return NULL;

  /* Ako je trazeno ime i prezime sadrzano u korenu, takodje se
     zavrsava sa pretragom */
  if (strcmp(koren->ime_i_prezime, ime_i_prezime) == 0)
    return koren;

  /* Ako je zadato ime i prezime leksikografski manje od vrednosti
     u korenu pretraga se nastavlja levo */
  if (strcmp(ime_i_prezime, koren->ime_i_prezime) < 0)
    return pretrazi_imenik(koren->levo, ime_i_prezime);
  else
    /* U suprotnom, pretraga se nastavlja desno */
    return pretrazi_imenik(koren->desno, ime_i_prezime);
}

int main(int argc, char **argv)
{
  char ime_datoteke[MAX_IME_DATOTEKE];
  Cvor *koren = NULL;
  Cvor *trazeni;
  FILE *f;
  char ime_i_prezime[MAX_IME_I_PREZIME];
  char telefon[MAX_CIFARA];
  char c;
  int i;

  /* Ucitava se ime datoteke i vrsi se njena priprema za citanje */
  printf("Unesite ime datoteke: ");
  scanf("%s", ime_datoteke);
  getchar();
  if ((f = fopen(ime_datoteke, "r")) == NULL) {
    fprintf(stderr, "Greska: Neuspesno otvaranje datoteke %s.\n",
            ime_datoteke);
    exit(EXIT_FAILURE);
  }

  /* Citaju se podaci iz datoteke i smestanju u binarno stablo
     pretrage uz proveru uspesnosti dodavanja */
  while (procitaj_kontakt(f, ime_i_prezime, telefon) != EOF)
    if (dodaj_u_stablo(&koren, ime_i_prezime, telefon) == 1) {
      fprintf(stderr,
              "Greska: Neuspelo dodavanje podataka za osobu %s.\n",
              ime_i_prezime);
      oslobodi_stablo(&koren);
      exit(EXIT_FAILURE);
    }

  /* Datoteka se zatvara */
  fclose(f);

  /* Omogucava se pretraga imenika */
  while (1) {
    /* Ucitava se ime i prezime */
    printf("Unesite ime i prezime: ");
    i = 0;
    while ((c = getchar()) != '\n')
      ime_i_prezime[i++] = c;
    ime_i_prezime[i] = '\0';

    /* Ako je korisnik uneo naznaku za kraj pretrage, obustavlja se
       pretraga */
    if (strcmp(ime_i_prezime, "KRAJ") == 0)
      break;

    /* Inace se ispisuje rezultat pretrage */
    trazeni = pretrazi_imenik(koren, ime_i_prezime);
    if (trazeni == NULL)
      printf("Broj nije u imeniku!\n");
    else
      printf("Broj je: %s \n", trazeni->telefon);
  }

  /* Oslobadja se memorija zauzeta imenikom */
  oslobodi_stablo(&koren);

  exit(EXIT_SUCCESS);
}
