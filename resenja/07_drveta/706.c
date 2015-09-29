#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NISKA 51
#define MAX_DATUM 3

/* Struktura koja opisuje jedan cvor stabla: sadrzi ime i
   prezime osobe, dan, mesec i godinu rodjenja i redom
   pokazivace na levo i desno podstablo */
typedef struct cvor_stabla {
  char ime[MAX_NISKA];
  char prezime[MAX_NISKA];
  int dan;
  int mesec;
  int godina;
  struct cvor_stabla *levo;
  struct cvor_stabla *desno;
} Cvor;

/* Funkcija koja kreira novi cvor */
Cvor *napravi_cvor(char ime[], char prezime[], int dan,
                   int mesec, int godina)
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
  novi->godina = godina;
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

  /* Oslobadja se memorija zauzeta levim podstablom (ako
     postoji) */
  if ((*koren)->levo)
    oslobodi_stablo(&(*koren)->levo);

  /* Oslobadja se memorija zauzeta desnim podstablom (ako
     postoji) */
  if ((*koren)->desno)
    oslobodi_stablo(&(*koren)->desno);

  /* Oslobadja se memorija zauzeta korenom */
  free(*koren);

  /* Proglasava se stablo praznim */
  *koren = NULL;
}

/* Funkcija koja dodaje novi cvor u stablo - stablo treba da
   bude uredjeno po datumu */
void dodaj_u_stablo(Cvor ** koren, char ime[], char prezime[],
                    int dan, int mesec, int godina)
{
  /* Ako je stablo prazno */
  if (*koren == NULL) {

    /* Kreira se novi cvor */
    Cvor *novi_cvor =
        napravi_cvor(ime, prezime, dan, mesec, godina);
    proveri_alokaciju(novi_cvor);

    /* I proglasava se korenom */
    *koren = novi_cvor;

    return;
  }

  /* Kako se ne unosi godina za pretragu, stablo se uredjuje
     samo po mesecu (i danu u okviru istog meseca) */
  if (mesec < (*koren)->mesec)
    dodaj_u_stablo(&(*koren)->levo, ime, prezime, dan, mesec,
                   godina);
  else if (mesec == (*koren)->mesec && dan < (*koren)->dan)
    dodaj_u_stablo(&(*koren)->levo, ime, prezime, dan, mesec,
                   godina);
  else
    dodaj_u_stablo(&(*koren)->desno, ime, prezime, dan, mesec,
                   godina);
}

/* Funkcija vrsi pretragu stabla i vraca cvor sa trazenim
   datumom (null ako takav ne postoji). U promenljivu pom ce
   biti smesten prvi datum (dan i mesec) veci od trazenog datuma 
   (null ako takav ne postoji) */
Cvor *pretrazi(Cvor * koren, int dan, int mesec)
{
  /* Stablo je prazno, obustavlja se pretraga */
  if (koren == NULL)
    return NULL;

  /* Ako je trazeni datum u korenu */
  if (koren->dan == dan && koren->mesec == mesec)
    return koren;

  /* Ako je mesec trazenog datuma manji od meseca sadrzanog u
     korenu ili ako su meseci isti ali je dan trazenog datuma
     manji od aktuelnog datuma, pretrazuje se levo podstablo -
     pre toga se svakako proverava da li leva grana postoji -
     ako ne postoji treba vratiti prvi sledeci, a to je bas
     vrednost uocenog korena */
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

int main(int argc, char **argv)
{
  FILE *in;
  Cvor *koren;
  Cvor *slavljenik;
  char ime[MAX_NISKA], prezime[MAX_NISKA];
  int dan, mesec, godina;

  /* Provera da li je zadato ime ulazne datoteke */
  if (argc < 2) {
    /* Ako nije, ispisuje se poruka i prekida se sa izvrsavanjem
       programa */
    printf("Nedostaje ime ulazne datoteke!\n");
    return 0;
  }

  /* Inace, priprema se datoteka za citanje */
  in = fopen(argv[1], "r");
  if (in == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke!\n");
    exit(EXIT_FAILURE);
  }

  /* I stablo se popunjava podacima */
  koren = NULL;
  while (fscanf
         (in, "%s %s %d.%d.%d.", ime, prezime, &dan, &mesec,
          &godina) != EOF)
    dodaj_u_stablo(&koren, ime, prezime, dan, mesec, godina);

  /* Zatvaranje datoteke */
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
    if (slavljenik == NULL) {
      printf
          ("Nema podataka o oviom ni o sledecem rodjendanu.\n");
      continue;
    }

    /* Slucaj kada su pronadjeni pravi podaci */
    if (slavljenik->dan == dan && slavljenik->mesec == mesec) {
      printf("Slavljenik: %s %s\n", slavljenik->ime,
             slavljenik->prezime);
      continue;
    }

    /* Slucaj su pronadjeni podaci o prvom sledecem rodjendanu */
    printf("Slavljenik: %s %s %d.%d.\n", slavljenik->ime,
           slavljenik->prezime, slavljenik->dan,
           slavljenik->mesec);
  }

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
