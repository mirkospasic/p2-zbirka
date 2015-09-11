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

  /* Alociramo memoriju */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizujemo polja strukture */
  strcpy(novi->ime, ime);
  strcpy(novi->prezime, prezime);
  novi->dan = dan;
  novi->mesec = mesec;
  novi->godina = godina;
  novi->levo = NULL;
  novi->desno = NULL;

  /* Vracamo adresu novog cvora */
  return novi;
}

/* Funkcija koja proverava uspesnost alokacije */
void proveri_alokaciju(Cvor * novi_cvor)
{

  /* Ako memorija nije uspesno alocirana */
  if (novi_cvor == NULL) {
    /* Ispisujemo poruku i prekidamo izvrsavanje programa */
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

  /* Oslobadjamo memoriju zauzetu levim podstablom (ako postoji) 
   */
  if ((*koren)->levo)
    oslobodi_stablo(&(*koren)->levo);

  /* Oslobadjamo memoriju zauzetu desnim podstablom (ako
     postoji) */
  if ((*koren)->desno)
    oslobodi_stablo(&(*koren)->desno);

  /* Oslobadjamo memoriju zauzetu korenom */
  free(*koren);

  /* Proglasavamo stablo praznim */
  *koren = NULL;
}

/* Funkcija koja dodaje novi cvor u stablo - stablo treba da
   bude uredjeno po datumu */
void dodaj_u_stablo(Cvor ** koren, char ime[], char prezime[],
                    int dan, int mesec, int godina)
{

  /* Ako je stablo prazno */
  if (*koren == NULL) {

    /* Kreiramo novi cvor */
    Cvor *novi_cvor =
        napravi_cvor(ime, prezime, dan, mesec, godina);
    proveri_alokaciju(novi_cvor);

    /* I proglasavamo ga korenom */
    *koren = novi_cvor;

    return;
  }

  /* Kako se ne unosi godina za pretragu, stablo uredjujemo samo
     po mesecu (i danu u okviru istog meseca) */
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
   datumom (null ako takav ne postoji). u promenljivu pom ce
   biti smesten prvi datum (dan i mesec) veci od trazenog
   datuma (null ako takav ne postoji)

 */
Cvor *pretrazi(Cvor * koren, int dan, int mesec)
{
  /* Stablo je prazno, obustavljamo pretragu */
  if (koren == NULL)
    return NULL;

  /* Nasli smo trazeni datum u stablu */
  if (koren->dan == dan && koren->mesec == mesec)
    return koren;

  /* Ako je mesec trazenog datuma manji od meseca sadrzanog u
     korenu ili ako su meseci isti ali je dan trazenog datuma
     manji od aktuelnog datuma, pretrazujemo levo podstablo -
     pre toga svakako proveravamo da li leva grana postoji - ako 
     ne postoji treba da vratimo prvi sledeci, a to je bas
     vrednost uocenog korena */
  if (mesec < koren->mesec
      || (mesec == koren->mesec && dan < koren->dan)) {
    if (koren->levo == NULL)
      return koren;
    else
      return pretrazi(koren->levo, dan, mesec);
  }

  /* inace, nastavljamo pretragu u desnom delu */
  return pretrazi(koren->desno, dan, mesec);
}


int main(int argc, char **argv)
{
  FILE *in;
  Cvor *koren;
  Cvor *slavljenik;
  char ime[MAX_NISKA], prezime[MAX_NISKA];
  int dan, mesec, godina;

  /* Proveravamo da li je zadato ime ulazne datoteke */
  if (argc < 2) {
    /* Ako nije, ispisujemo poruku i prekidamo sa izvrsavanjem
       programa */
    printf("Nedostaje ime ulazne datoteke!\n");
    return 0;
  }

  /* Inace, pripremamo datoteku za citanje */
  in = fopen(argv[1], "r");
  if (in == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke!\n");
    exit(EXIT_FAILURE);
  }

  /* I popunjavamo podacima stablo */
  koren = NULL;
  while (fscanf
         (in, "%s %s %d.%d.%d.", ime, prezime, &dan, &mesec,
          &godina) != EOF)
    dodaj_u_stablo(&koren, ime, prezime, dan, mesec, godina);

  /* I zatvaramo datoteku */
  fclose(in);

  /* Omogucavamo pretragu podataka */
  while (1) {

    /* Ucitavamo novi datum */
    printf("Unesite datum: ");
    if (scanf("%d.%d.", &dan, &mesec) == EOF)
      break;

    /* Pretrazujemo stablo */
    slavljenik = pretrazi(koren, dan, mesec);

    /* Ispisujemo pronadjene podatke */
    if (slavljenik == NULL) {
      printf("Nema podataka o ovim ni o sledecem rodjendanu.\n");
      continue;
    }

    /* Slucaj kada smo pronasli prave podatke */
    if (slavljenik->dan == dan && slavljenik->mesec == mesec) {
      printf("Slavljenik: %s %s\n", slavljenik->ime,
             slavljenik->prezime);
      continue;
    }

    /* Slucaj kada smo pronasli podatke o prvom sledecem
       rodjendanu */
    printf("Slavljenik: %s %s %d.%d.\n", slavljenik->ime,
           slavljenik->prezime, slavljenik->dan,
           slavljenik->mesec);
  }

  /* Oslobadjamo memoriju zauzetu stablom */
  oslobodi_stablo(&koren);

  /* Prekidamo sa izvrsavanjem programa */
  return 0;
}
