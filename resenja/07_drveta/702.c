#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

/* Struktura kojom se opisuje cvor stabla: sadrzi rec, njen broj
   pojavljivanja i redom pokazivace na levo i desno podstablo */
typedef struct cvor {
  char *rec;
  int brojac;
  struct cvor *levo;
  struct cvor *desno;
} Cvor;

/* Funkcija koja kreira novi cvora stabla */
Cvor *napravi_cvor(char *rec)
{
  /* Alocira se memorija za novi cvor i proverava se uspesnost
     alokacije. */
  Cvor *novi_cvor = (Cvor *) malloc(sizeof(Cvor));
  if (novi_cvor == NULL)
    return NULL;

  /* Alocira se memorija za zadatu rec: potrebno je rezervisati
     memoriju za svaki karakter reci ukljucujuci i terminirajucu nulu 
   */
  novi_cvor->rec = (char *) malloc((strlen(rec) + 1) * sizeof(char));
  if (novi_cvor->rec == NULL) {
    free(novi_cvor);
    return NULL;
  }

  /* Inicijalizuju se polja u novom cvoru */
  strcpy(novi_cvor->rec, rec);
  novi_cvor->brojac = 1;
  novi_cvor->levo = NULL;
  novi_cvor->desno = NULL;

  /* Vraca se adresa novog cvora */
  return novi_cvor;
}

/* Funkcija koja proverava uspesnost kreiranja novog cvora stabla */
void proveri_alokaciju(Cvor * novi_cvor)
{
  /* Ukoliko je cvor neuspesno kreiran */
  if (novi_cvor == NULL) {
    /* Ispisuje se odgovarajuca poruka i prekida izvrsavanje programa 
     */
    fprintf(stderr, "Malloc greska za novi cvor!\n");
    exit(EXIT_FAILURE);
  }
}

/* Funkcija koja dodaje novu rec u stablo. */
void dodaj_u_stablo(Cvor ** adresa_korena, char *rec)
{
  /* Ako je stablo prazno */
  if (*adresa_korena == NULL) {
    /* Kreira se cvor koji sadrzi zadatu rec */
    Cvor *novi = napravi_cvor(rec);
    proveri_alokaciju(novi);

    /* I proglasava se korenom stabla */
    *adresa_korena = novi;
    return;
  }

  /* U suprotnom se trazi odgovarajuca pozicija za novu rec */

  /* Ako je rec leksikografski manja od reci u korenu ubacuje se u
     levo podstablo */
  if (strcmp(rec, (*adresa_korena)->rec) < 0)
    dodaj_u_stablo(&(*adresa_korena)->levo, rec);

  else
    /* Ako je rec leksikografski veca od reci u korenu ubacuje se u
       desno podstablo */
  if (strcmp(rec, (*adresa_korena)->rec) > 0)
    dodaj_u_stablo(&(*adresa_korena)->desno, rec);

  else
    /* Ako je rec jednaka reci u korenu, uvecava se njen broj
       pojavljivanja */
    (*adresa_korena)->brojac++;
}

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** adresa_korena)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*adresa_korena == NULL)
    return;

  /* Inace ... */
  /* Oslobadja se memorija zauzeta levim podstablom */
  oslobodi_stablo(&(*adresa_korena)->levo);

  /* Oslobadja se memorija zauzeta desnim podstablom */
  oslobodi_stablo(&(*adresa_korena)->desno);

  /* Oslobadja se memorija zauzeta korenom */
  free((*adresa_korena)->rec);
  free(*adresa_korena);

  /* Stablo se proglasava praznim */
  *adresa_korena = NULL;
}

/* Funkcija koja pronalazi cvor koji sadrzi najfrekventniju rec (rec
   sa najvecim brojem pojavljivanja) */
Cvor *nadji_najfrekventniju_rec(Cvor * koren)
{
  Cvor *max, *max_levo, *max_desno;

  /* Ako je stablo prazno, prekida se sa pretragom */
  if (koren == NULL)
    return NULL;

  /* Pronalazi se najfrekventnija rec u levom podstablu */
  max_levo = nadji_najfrekventniju_rec(koren->levo);

  /* Pronalazi se najfrekventnija rec u desnom podstablu */
  max_desno = nadji_najfrekventniju_rec(koren->desno);

  /* Trazi se maksimum vrednosti pojavljivanja reci iz levog
     podstabla, korena i desnog podstabla */
  max = koren;
  if (max_levo != NULL && max_levo->brojac > max->brojac)
    max = max_levo;
  if (max_desno != NULL && max_desno->brojac > max->brojac)
    max = max_desno;

  /* Vraca se adresa cvora sa najvecim brojem pojavljivanja */
  return max;
}

/* Funkcija koja ispisuje reci iz stabla u leksikografskom poretku
   pracene brojem pojavljivanja */
void prikazi_stablo(Cvor * koren)
{
  /* Ako je stablo prazno, zavrsava se sa ispisom */
  if (koren == NULL)
    return;

  /* Zbog leksikografskog poretka, prvo se ispisuju sve reci iz levog 
     podstabla */
  prikazi_stablo(koren->levo);

  /* Zatim rec iz korena */
  printf("%s: %d\n", koren->rec, koren->brojac);

  /* I nastavlja se sa ispisom reci iz desnog podstabla */
  prikazi_stablo(koren->desno);
}

/* Funkcija ucitava sledecu rec iz zadate datoteke f i upisuje je u
   niz rec. Maksimalna duzina reci je odredjena argumentom max.
   Funkcija vraca EOF ako u datoteci nema vise reci ili 0 u
   suprotnom. Rec je niz malih ili velikih slova. */
int procitaj_rec(FILE * f, char rec[], int max)
{
  /* Karakter koji se cita */
  int c;

  /* Indeks pozicije na koju se smesta procitani karakter */
  int i = 0;

  /* Sve dok ima mesta za jos jedan karakter u nizu i dokle se god
     nije stiglo do kraja datoteke... */
  while (i < max - 1 && (c = fgetc(f)) != EOF) {
    /* Proverava se da li je procitani karakter slovo */
    if (isalpha(c))
      /* Ako jeste, smesta se u niz - pritom se vrsi konverzija u
         mala slova jer program treba da bude neosetljiv na razliku
         izmedju malih i velikih slova */
      rec[i++] = tolower(c);

    else
      /* Ako nije, proverava se da li je procitano barem jedno slovo
         nove reci */
      /* Ako jeste, prekida se sa citanjem */
    if (i > 0)
      break;

    /* U suprotnom se ide na sledecu iteraciju */
  }

  /* Dodaje se na rec terminirajuca nula */
  rec[i] = '\0';

  /* Vraca se 0 ako je procitana rec, tj. EOF u suprotnom */
  return i > 0 ? 0 : EOF;
}

int main(int argc, char **argv)
{
  Cvor *koren = NULL, *max;
  FILE *f;
  char rec[MAX];

  /* Provera da li je navedeno ime datoteke prilikom pokretanja
     programa */
  if (argc < 2) {
    fprintf(stderr, "Nedostaje ime ulazne datoteke!\n");
    exit(EXIT_FAILURE);
  }

  /* Priprema datoteke za citanje */
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "fopen() greska pri otvaranju %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  /* Ucitavanje reci iz datoteke i smestanje u binarno stablo
     pretrage. */
  while (procitaj_rec(f, rec, MAX) != EOF)
    dodaj_u_stablo(&koren, rec);

  /* Posto je citanjem reci zavrseno, zatvara se datoteka */
  fclose(f);

  /* Prikazuju se sve reci iz teksta i brojevi njihovih
     pojavljivanja. */
  prikazi_stablo(koren);

  /* Pronalazi se najfrekventnija rec */
  max = nadji_najfrekventniju_rec(koren);

  /* Ako takve reci nema... */
  if (max == NULL)

    /* Ispisuje se odgovarajuce obavestenje */
    printf("U tekstu nema reci!\n");

  else
    /* Inace, ispisuje se broj pojavljivanja reci */
    printf("Najcesca rec: %s (pojavljuje se %d puta)\n",
           max->rec, max->brojac);

  /* Oslobadja se dinamicki alociran prostor za stablo */
  oslobodi_stablo(&koren);

  return 0;
}
