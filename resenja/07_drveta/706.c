#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NISKA 51

/* Struktura koja opisuje jedan cvor stabla: sadrzi ime i prezime
   osobe, dan i mesec rodjenja i redom pokazivace na levo i desno
   podstablo */
typedef struct cvor_stabla {
  char ime[MAX_NISKA];
  char prezime[MAX_NISKA];
  int dan;
  int mesec;
  struct cvor_stabla *levo;
  struct cvor_stabla *desno;
} Cvor;

/* Funkcija koja kreira novi cvor */
Cvor *napravi_cvor(char ime[], char prezime[], int dan, int mesec)
{
  /* Alocira se memorija */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizuju se polja strukture */
  strcpy(novi->ime, ime);
  strcpy(novi->prezime, prezime);
  novi->dan = dan;
  novi->mesec = mesec;
  novi->levo = NULL;
  novi->desno = NULL;

  /* Vraca se adresa novog cvora */
  return novi;
}

/* Funkcija koja proverava uspesnost alokacije */
void proveri_alokaciju(Cvor * novi_cvor)
{
  /* Ako memorija nije uspesno alocirana */
  if (novi_cvor == NULL) {
    /* Ispisuje se poruka i prekida se sa izvrsavanjem programa */
    fprintf(stderr, "Malloc greska za novi cvor!\n");
    exit(EXIT_FAILURE);
  }
}

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** koren)
{
  /* Stablo je prazno */
  if (*koren == NULL)
    return;

  /* Oslobadja se memorija zauzeta levim podstablom (ako postoji) */
  if ((*koren)->levo)
    oslobodi_stablo(&(*koren)->levo);

  /* Oslobadja se memorija zauzeta desnim podstablom (ako postoji) */
  if ((*koren)->desno)
    oslobodi_stablo(&(*koren)->desno);

  /* Oslobadja se memorija zauzeta korenom */
  free(*koren);

  /* Proglasava se stablo praznim */
  *koren = NULL;
}

/* Funkcija koja dodaje novi cvor u stablo - stablo treba da bude
   uredjeno po datumu - prvo po mesecu, a zatim po danu */
void dodaj_u_stablo(Cvor ** koren, char ime[], char prezime[],
                    int dan, int mesec)
{
  /* Ako je stablo prazno */
  if (*koren == NULL) {

    /* Kreira se novi cvor */
    Cvor *novi_cvor = napravi_cvor(ime, prezime, dan, mesec);
    proveri_alokaciju(novi_cvor);

    /* I proglasava se korenom */
    *koren = novi_cvor;

    return;
  }

  /* Stablo se uredjuje po mesecu, a zatim po danu u okviru istog
     meseca */
  if (mesec < (*koren)->mesec)
    dodaj_u_stablo(&(*koren)->levo, ime, prezime, dan, mesec);
  else if (mesec == (*koren)->mesec && dan < (*koren)->dan)
    dodaj_u_stablo(&(*koren)->levo, ime, prezime, dan, mesec);
  else
    dodaj_u_stablo(&(*koren)->desno, ime, prezime, dan, mesec);
}

/* Funkcija vrsi pretragu stabla i vraca cvor sa trazenim datumom.  */
Cvor *pretrazi(Cvor * koren, int dan, int mesec)
{
  /* Stablo je prazno, obustavlja se pretraga */
  if (koren == NULL)
    return NULL;

  /* Ako je trazeni datum u korenu */
  if (koren->dan == dan && koren->mesec == mesec)
    return koren;

  /* Ako je mesec trazenog datuma manji od meseca sadrzanog u korenu
     ili ako su meseci isti ali je dan trazenog datuma manji od
     aktuelnog datuma, pretrazuje se levo podstablo - pre toga se
     svakako proverava da li leva grana postoji - ako ne postoji
     treba vratiti prvi sledeci, a to je bas vrednost uocenog korena */
  if (mesec < koren->mesec
      || (mesec == koren->mesec && dan < koren->dan)) {
    if (koren->levo == NULL)
      return koren;
    else
      return pretrazi(koren->levo, dan, mesec);
  }

  /* Inace se nastavlja pretraga u desnom delu */
  return pretrazi(koren->desno, dan, mesec);
}

/* Funkcija koja pronalazi najmanji datum u stablu */
Cvor *pronadji_najmanji_datum(Cvor * koren)
{
  /* Stablo je prazno, obustavlja se pretraga */
  if (koren == NULL)
    return NULL;

  /* Ako ne postoji leva grana korena, zbog uredjenja stabla koren
     sadrzi najmanji datum */
  if (koren->levo == NULL)
    return koren;
  else
    /* Inace, trazimo manji datum u levom podstablu */
    return pronadji_najmanji_datum(koren->levo);
}

/* Funkcija koja za dati dan i mesec odredjuje nisku formata DD.MM. */
void datum_u_nisku(int dan, int mesec, char datum[])
{
  if (dan < 10) {
    datum[0] = '0';
    datum[1] = dan + '0';
  } else {
    datum[0] = dan / 10 + '0';
    datum[1] = dan % 10 + '0';
  }
  datum[2] = '.';

  if (mesec < 10) {
    datum[3] = '0';
    datum[4] = mesec + '0';
  } else {
    datum[3] = mesec / 10 + '0';
    datum[4] = mesec % 10 + '0';
  }
  datum[5] = '.';
  datum[6] = '\0';
}

int main(int argc, char **argv)
{
  FILE *in;
  Cvor *koren;
  Cvor *slavljenik;
  char ime[MAX_NISKA], prezime[MAX_NISKA];
  int dan, mesec;
  char datum[7];

  /* Provera da li je zadato ime ulazne datoteke */
  if (argc < 2) {
    /* Ako nije, ispisuje se poruka i prekida se sa izvrsavanjem
       programa */
    fprintf(stderr, "Nedostaje ime ulazne datoteke!\n");
    exit(EXIT_FAILURE);
  }

  /* Inace, priprema se datoteka za citanje */
  in = fopen(argv[1], "r");
  if (in == NULL) {
    fprintf(stderr, "Greska: Neuspesno otvaranje datoteke %s.\n",
            argv[1]);
    exit(EXIT_FAILURE);
  }

  /* I stablo se popunjava podacima */
  koren = NULL;
  while (fscanf
         (in, "%s %s %d.%d.", ime, prezime, &dan, &mesec) != EOF)
    dodaj_u_stablo(&koren, ime, prezime, dan, mesec);

  /* Datoteka se zatvara */
  fclose(in);

  /* Omogucuje se pretraga podataka */
  while (1) {

    /* Ucitava se novi datum */
    printf("Unesite datum: ");
    if (scanf("%d.%d.", &dan, &mesec) == EOF)
      break;

    /* Pretrazuje se stablo */
    slavljenik = pretrazi(koren, dan, mesec);

    /* Ispisuju se pronadjeni podaci */

    /* Ako slavljenik nije pronadjen, to moze znaci da: */
    /* 1. drvo je prazno */
    if (slavljenik == NULL && koren == NULL) {
      printf("Nema podataka o ovom ni o sledecem rodjendanu.\n");
      continue;
    }
    /* 2. posle datuma koji je unesen, nema podataka u stablu - u
       ovom slucaju se pretraga vrsi pocevsi od naredne godine i
       ispisuje se najmanji datum */
    if (slavljenik == NULL) {
      slavljenik = pronadji_najmanji_datum(koren);
      datum_u_nisku(slavljenik->dan, slavljenik->mesec, datum);
      printf("Slavljenik: %s %s %s\n", slavljenik->ime,
             slavljenik->prezime, datum);
      continue;
    }

    /* Ako je slavljenik pronadjen, razlikuju se slucajevi: */
    /* 1. Pronadjeni su tacni podaci */
    if (slavljenik->dan == dan && slavljenik->mesec == mesec) {
      printf("Slavljenik: %s %s\n", slavljenik->ime,
             slavljenik->prezime);
      continue;
    }

    /* 2. Pronadjeni su podaci o prvom sledecem rodjendanu */
    datum_u_nisku(slavljenik->dan, slavljenik->mesec, datum);
    printf("Slavljenik: %s %s %s\n", slavljenik->ime,
           slavljenik->prezime, datum);
  }

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
