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
  /* Alociramo memoriju za novi cvor */
  Cvor *novi_cvor = (Cvor *) malloc(sizeof(Cvor));
  if (novi_cvor == NULL)
    return NULL;

  /* Inicijalizujemo polja u novom cvoru */
  strcpy(novi_cvor->ime_i_prezime, ime_i_prezime);
  strcpy(novi_cvor->telefon, telefon);
  novi_cvor->levo = NULL;
  novi_cvor->desno = NULL;

  /* Vracamo adresu novog cvora */
  return novi_cvor;
}


/* Funkcija koja proverava uspesnost kreiranja novog cvora
   stabla */
void proveri_alokaciju(Cvor * novi_cvor)
{
  /* Ukoliko je cvor neuspesno kreiran */
  if (novi_cvor == NULL) {
    /* Ispisuje se odgovarajuca poruka i prekida izvrsavanje
       programa */
    fprintf(stderr, "Malloc greska za novi cvor!\n");
    exit(EXIT_FAILURE);
  }
}


/* Funkcija koja dodaje novu osobu i njen broj telefona u
   stablo. */
void
dodaj_u_stablo(Cvor ** adresa_korena, char *ime_i_prezime,
               char *telefon)
{
  /* Ako je stablo prazno */
  if (*adresa_korena == NULL) {
    /* Kreiramo novi cvor */
    Cvor *novi = napravi_cvor(ime_i_prezime, telefon);
    proveri_alokaciju(novi);

    /* i proglasavamo ga korenom stabla */
    *adresa_korena = novi;
    return;
  }

  /* U suprotnom trazimo odgovarajucu poziciju za novi unos */
  /* Kako pretragu treba vrsiti po imenu i prezimenu, stablo
     treba da bude pretrazivacko po ovom polju */
  /* Ako je zadato ime i prezime leksikografski manje od imena i 
     prezimena sadrzanog u korenu, podatke dodajemo u levo
     podstablo */
  if (strcmp(ime_i_prezime, (*adresa_korena)->ime_i_prezime)
      < 0)
    dodaj_u_stablo(&(*adresa_korena)->levo, ime_i_prezime,
                   telefon);

  else
    /* Ako je zadato ime i prezime leksikografski vece od imena
       i prezimena sadrzanog u korenu, podatke kodajemo u desno
       podstablo */
  if (strcmp(ime_i_prezime, (*adresa_korena)->ime_i_prezime) > 0)
    dodaj_u_stablo(&(*adresa_korena)->desno, ime_i_prezime,
                   telefon);
}


/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** adresa_korena)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*adresa_korena == NULL)
    return;

  /* Inace ... */
  /* Oslobadjamo memoriju zauzetu levim podstablom */
  oslobodi_stablo(&(*adresa_korena)->levo);

  /* Oslobadjamo memoriju zauzetu desnim podstablom */
  oslobodi_stablo(&(*adresa_korena)->desno);

  /* Oslobadjamo memoriju zauzetu korenom */
  free(*adresa_korena);

  /* Proglasavamo stablo praznim */
  *adresa_korena = NULL;
}


/* Funkcija koja ispisuje imenik u leksikografskom poretku */
/* Napomena: ova funkcija nije trazena u zadatku ali se moze
   koristiti za proveru da li je stablo lepo kreirano ili ne */
void prikazi_stablo(Cvor * koren)
{
  /* Ako je stablo prazno, zavrsavamo sa ispisom */
  if (koren == NULL)
    return;

  /* Zbog leksikografskog poretka, prvo ispisujemo podatke iz
     levog podstabla */
  prikazi_stablo(koren->levo);

  /* Zatim ispisujemo podatke iz korena */
  printf("%s: %s\n", koren->ime_i_prezime, koren->telefon);

  /* I nastavljamo sa ispisom podataka iz desnog podstabla */
  prikazi_stablo(koren->desno);
}


/* Funkcija ucitava sledeci kontakt iz zadate datoteke i upisuje 
   ime i prezime i broj telefona u odgovarajuce nizove.
   Maksimalna duzina imena i prezimena odredjena je konstantom
   MAX_IME_PREZIME, a maksimalna duzina broja telefona
   konstantom MAX_CIFARA. Funkcija vraca EOF ako nema vise
   kontakata ili 0 u suprotnom. */
int procitaj_kontakt(FILE * f, char *ime_i_prezime,
                     char *telefon)
{
  int c;
  int i = 0;

  /* Linije datoteke koje obradjujemo su formata Ime Prezime
     BrojTelefona */
  /* Preskacemo eventualne praznine sa pocetka linije datoteke */
  while ((c = fgetc(f)) != EOF && isspace(c));

  /* Prvo procitano slovo upisujemo u ime i prezime */
  if (!feof(f))
    ime_i_prezime[i++] = c;

  /* Naznaka kraja citanja imena i prezimena ce biti pojava prve 
     cifre, tako da cemo citanje forsirati sve dok ne naidjemo
     na cifru. Pri tom cemo voditi racuna da li ima dovoljno
     mesta za smestanje procitanog karaktera i da slucajno ne
     dodjemo do kraja datoteke */
  while (i < MAX_IME_I_PREZIME - 1 && (c = fgetc(f)) != EOF) {
    if (!isdigit(c))
      ime_i_prezime[i++] = c;

    else if (i > 0)
      break;
  }

  /* Upisujemo terminirajucu nulu na mesto poslednjeg procitanog 
     blanko karaktera */
  ime_i_prezime[--i] = '\0';

  /* I pocinjemo sa citanjem broja telefona */
  i = 0;

  /* Upisujemo cifru koju smo vec procitali */
  telefon[i++] = c;

  /* I citamo peostale cifre - naznaka kraja ce nam biti pojava
     karaktera cije prisustvo nije dozvoljeno u broju telefona */
  while (i < MAX_CIFARA - 1 && (c = fgetc(f)) != EOF)
    if (c == '/' || c == '-' || isdigit(c))
      telefon[i++] = c;

    else
      break;

  /* Upisujemo terminirajucu nulu */
  telefon[i] = '\0';

  /* Vracamo 0 ako smo procitali kontakt, EOF u suprotnom */
  return !feof(f) ? 0 : EOF;
}


/* Funkcija koja trazi u imeniku osobu sa zadatim imenom i
   prezimenom */
Cvor *pretrazi_imenik(Cvor * koren, char *ime_i_prezime)
{
  /* Ako je imenik prazan, zavrsavamo sa pretragom */
  if (koren == NULL)
    return NULL;

  /* Ako je trazeno ime i prezime sadrzano u korenu, takodje
     zavrsavamo sa pretragom */
  if (strcmp(koren->ime_i_prezime, ime_i_prezime) == 0)
    return koren;

  /* Ako je zadato ime i prezime leksikografski manje od
     vrednosti u korenu pretragu nastavljamo levo */
  if (strcmp(ime_i_prezime, koren->ime_i_prezime) < 0)
    return pretrazi_imenik(koren->levo, ime_i_prezime);

  else
    /* u suprotnom, pretragu nastavljamo desno */
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

  /* Ucitavamo ime datoteke i pripremamo je za citanje */
  printf("Unesite ime datoteke: ");
  scanf("%s", ime_datoteke);
  if ((f = fopen(ime_datoteke, "r")) == NULL) {
    fprintf(stderr, "fopen() greska prilikom otvaranja
%s\n", ime_datoteke);
    exit(EXIT_FAILURE);
  }

  /* Ucitavamo podatke iz datoteke i smestamo kontakte u binarno 
     stablo pretrage. */
  while (procitaj_kontakt(f, ime_i_prezime, telefon) != EOF)
    dodaj_u_stablo(&koren, ime_i_prezime, telefon);

  /* Posto smo zavrsili sa citanjem podataka zatvaramo datoteku */
  fclose(f);

  /* Omogucavamo pretragu imenika */
  while (1) {
    /* Ucitavamo ime i prezime */
    printf("Unesite ime i prezime: ");
    i = 0;
    while ((c = getchar()) != '\n')
      ime_i_prezime[i++] = c;
    ime_i_prezime[i] = '\0';

    /* Ako je korisnik uneo naznaku za kraj pretrage,
       obustavljamo funkcionalnost */
    if (strcmp(ime_i_prezime, "KRAJ") == 0)
      break;

    /* Inace, ispisujemo rezultat pretrage */
    trazeni = pretrazi_imenik(koren, ime_i_prezime);
    if (trazeni == NULL)
      printf("Broj nije u imeniku!\n");

    else
      printf("Broj je: %s \n", trazeni->telefon);
  }

  /* Oslobadjamo memoriju zauzetu imenikom */
  oslobodi_stablo(&koren);

  /* Zavrsavamo sa programom */
  return 0;
}
