#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 51

/* Struktura koja definise cvorove stabla: sadrzi ime i prezime
   studenta, ukupan uspeh, uspeh iz matematike, uspeh iz maternjeg
   jezika i redom pokazivace na levo i desno podstablo */
typedef struct cvor_stabla {
  char ime[MAX];
  char prezime[MAX];
  double uspeh;
  double matematika;
  double jezik;
  struct cvor_stabla *levo;
  struct cvor_stabla *desno;
} Cvor;

/* Funkcija kojom se kreira cvor stabla */
Cvor *napravi_cvor(char ime[], char prezime[], double uspeh,
                   double matematika, double jezik)
{
  /* Alocira se memorija za novi cvor i proverava se uspesnost
     alokacije. */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizuju se polja strukture */
  strcpy(novi->ime, ime);
  strcpy(novi->prezime, prezime);
  novi->uspeh = uspeh;
  novi->matematika = matematika;
  novi->jezik = jezik;
  novi->levo = NULL;
  novi->desno = NULL;

  /* Vraca se adresa kreiranog cvora */
  return novi;
}

/* Funkcija kojom se proverava uspesnost alociranja memorije */
void proveri_alokaciju(Cvor * novi_cvor)
{
  /* Ukoliko je cvor neuspesno kreiran */
  if (novi_cvor == NULL) {
    /* Ispisuje se odgovarajuca poruka i prekida se izvrsavanje
       programa */
    fprintf(stderr, "Malloc greska za novi cvor!\n");
    exit(EXIT_FAILURE);
  }
}

/* Funkcija kojom se oslobadja memorija zauzeta stablom */
void oslobodi_stablo(Cvor ** koren)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*koren == NULL)
    return;

  /* Inace ... */
  /* Oslobadja se memorija zauzeta levim podstablom */
  oslobodi_stablo(&(*koren)->levo);

  /* Oslobadja se memorija zauzeta desnim podstablom */
  oslobodi_stablo(&(*koren)->desno);

  /* Oslobadja se memorija zauzeta korenom */
  free(*koren);

  /* Stablo se proglasava praznim */
  *koren = NULL;
}

/* Funkcija koja dodaje cvor sa zadatim vrednostima u stablo */
void dodaj_u_stablo(Cvor ** koren, char ime[], char prezime[],
                    double uspeh, double matematika, double jezik)
{
  /* Ako je stablo prazno */
  if (*koren == NULL) {
    /* Kreira se novi cvor */
    Cvor *novi = napravi_cvor(ime, prezime, uspeh, matematika, jezik);
    proveri_alokaciju(novi);

    /* I proglasava se korenom stabla */
    *koren = novi;

    return;
  }

  /* Inace, dodaje se cvor u stablo tako da bude sortirano po ukupnom 
     broju poena */
  if (uspeh + matematika + jezik >
      (*koren)->uspeh + (*koren)->matematika + (*koren)->jezik)
    dodaj_u_stablo(&(*koren)->levo, ime, prezime, uspeh,
                   matematika, jezik);
  else
    dodaj_u_stablo(&(*koren)->desno, ime, prezime, uspeh,
                   matematika, jezik);
}

/* Funkcija ispisuje sadrzaj stabla. Ukoliko je vrednost argumenta
   polozili jednaka 0 ispisuju se informacije o ucenicima koji nisu
   polozili prijemni, a ako je vrednost argumenta razlicita od nule,
   ispisuju se informacije o ucenicima koji su polozili prijemni */
void stampaj(Cvor * koren, int polozili)
{
  /* Stablo je prazno - prekida se sa ispisom */
  if (koren == NULL)
    return;

  /* Stampaju se informacije iz levog podstabla */
  stampaj(koren->levo, polozili);

  /* Stampaju se informacije iz korenog cvora */
  if (polozili && koren->matematika + koren->jezik >= 10)
    printf("%s %s %.1lf %.1lf %.1lf %.1lf\n", koren->ime,
           koren->prezime, koren->uspeh, koren->matematika,
           koren->jezik,
           koren->uspeh + koren->matematika + koren->jezik);
  else if (!polozili && koren->matematika + koren->jezik < 10)
    printf("%s %s %.1lf %.1lf %.1lf %.1lf\n", koren->ime,
           koren->prezime, koren->uspeh, koren->matematika,
           koren->jezik,
           koren->uspeh + koren->matematika + koren->jezik);

  /* Stampaju se informacije iz desnog podstabla */
  stampaj(koren->desno, polozili);
}

/* Funkcija koja odredjuje koliko studenata nije polozilo prijemni
   ispit */
int nisu_polozili(Cvor * koren)
{
  /* Ako je stablo prazno, broj onih koji nisu polozili je 0 */
  if (koren == NULL)
    return 0;

  /* Pretraga se vrsi i u levom i u desnom podstablu - ako uslov za
     polaganje nije ispunjen za koreni cvor, broj studenata se
     uvecava za 1 */
  if (koren->matematika + koren->jezik < 10)
    return 1 + nisu_polozili(koren->levo) +
        nisu_polozili(koren->desno);

  return nisu_polozili(koren->levo) + nisu_polozili(koren->desno);
}

int main(int argc, char **argv)
{
  FILE *in;
  Cvor *koren;
  char ime[MAX], prezime[MAX];
  double uspeh, matematika, jezik;

  /* Otvara se datoteke sa rezultatima sa prijemnog za citanje */
  in = fopen("prijemni.txt", "r");
  if (in == NULL) {
    fprintf(stderr, "Greska prilikom otvaranja datoteke!\n");
    exit(EXIT_FAILURE);
  }

  /* Citanje podataka i dodavanje u stablo */
  koren = NULL;
  while (fscanf(in, "%s %s %lf %lf %lf", ime, prezime, &uspeh,
                &matematika, &jezik) != EOF) {
    dodaj_u_stablo(&koren, ime, prezime, uspeh, matematika, jezik);
  }

  /* Zatvaranje datoteke */
  fclose(in);

  /* Stampaju se prvo podaci o ucenicima koji su polozili prijemni */
  stampaj(koren, 1);

  /* Linij se iscrtava samo ako postoje ucenici koji nisu polozili
     prijemni */
  if (nisu_polozili(koren) != 0)
    printf("-------------------------------------\n");

  /* Stampaju se podaci o ucenicima koji nisu polozili prijemni */
  stampaj(koren, 0);

  /* Oslobadja se memorija zauzeta stablom */
  oslobodi_stablo(&koren);

  return 0;
}
