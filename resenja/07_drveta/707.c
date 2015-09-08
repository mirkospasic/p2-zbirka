#include<stdio.h>
#include<stdlib.h>

/* Struktura koja opisuje cvor stabla */
typedef struct cvor_stabla {
  int podatak;
  struct cvor_stabla *levo;
  struct cvor_stabla *desno;
} Cvor;

/* Funkcija kojom se kreira novi cvor stabla koji sadrzi zadatu
   vrednost */
Cvor *napravi_cvor(int broj)
{
  /* Alociramo memoriju za novi cvor */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizujemo polja cvora */
  novi->podatak = broj;
  novi->levo = NULL;
  novi->desno = NULL;

  /* Vracamo adresu novog cvora */
  return novi;
}

/* Funkcija koja proverava uspesnost kreiranja novog cvora
   stabla */
void proveri_alokaciju(Cvor * koren)
{
  /* Ukoliko je cvor neuspesno kreiran */
  if (koren == NULL) {
    /* Ispisuje se odgovarajuca poruka i prekida izvrsavanje
       programa */
    fprintf(stderr, "Malloc greska za nov cvor!\n");
    exit(EXIT_FAILURE);
  }
}

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** koren)
{
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if (*koren == NULL)
    return;

  /* Inace ... */
  /* Oslobadjamo memoriju zauzetu levim podstablom */
  if ((*koren)->levo)
    oslobodi_stablo(&(*koren)->levo);

  /* Oslobadjamo memoriju zauzetu desnim podstablom */
  if ((*koren)->desno)
    oslobodi_stablo(&(*koren)->desno);

  /* Oslobadjamo memoriju zauzetu korenom */
  free(*koren);

  /* Proglasavamo stablo praznim */
  *koren = NULL;
}

/* Funkcija koja dodaje novi broj u stablo. */
void dodaj_u_stablo(Cvor ** koren, int broj)
{
  /* Ako je stablo prazno */
  if (*koren == NULL) {
    /* Kreiramo novi cvor */
    Cvor *novi = napravi_cvor(broj);
    proveri_alokaciju(novi);
    /* i proglasavamo ga korenom stabla */
    *koren = novi;
    return;
  }
  /* U suprotnom trazimo odgovarajucu poziciju za novi broj */
  /* Ako je broj manji od vrednosti sadrzane u korenu, ubacujemo 
     ga u levo podstablo */
  if (broj < (*koren)->podatak)
    dodaj_u_stablo(&(*koren)->levo, broj);
  else
    /* Inace, ubacujemo broj u desno podstablo */
    dodaj_u_stablo(&(*koren)->desno, broj);
}


/* Funkcija koja proverava da li su dva stabla koja sadrze cele
   brojeve identicna. Povratna vrednost funkcije je 1 ako jesu,
   odnosno 0 ako nisu */
int identitet(Cvor * koren1, Cvor * koren2)
{
  /* Ako su oba stabla prazna, jednaka su */
  if (koren1 == NULL && koren2 == NULL)
    return 1;

  /* Ako je jedno stablo prazno, a drugo nije, stabla nisu
     jednaka */
  if (koren1 == NULL || koren2 == NULL)
    return 0;

  /* Ako su oba stabla neprazna i u korenu se nalaze razlicite
     vrednosti, mozemo da zakljucimo da se razlikuju */
  if (koren1->podatak != koren2->podatak)
    return 0;

  /* inace, proveravamo da li vazi i jednakost u levih
     podstabala i desnih podstabala */
  return (identitet(koren1->levo, koren2->levo)
          && identitet(koren1->desno, koren2->desno));
}

int main()
{

  int broj;
  Cvor *koren1, *koren2;

  koren1 = NULL;
  /* ucitavamo elemente prvog stabla */
  printf("Prvo stablo: ");
  scanf("%d", &broj);
  while (broj != 0) {
    dodaj_u_stablo(&koren1, broj);
    scanf("%d", &broj);
  }

  koren2 = NULL;
  /* ucitavamo elemente drugog stabla */
  printf("Drugo stablo: ");
  scanf("%d", &broj);
  while (broj != 0) {
    dodaj_u_stablo(&koren2, broj);
    scanf("%d", &broj);
  }

  /* pozivamo funkciju koja ispituje identitet stabala */
  if (identitet(koren1, koren2))
    printf("Stabla jesu identicna.\n");
  else
    printf("Stabla nisu identicna.\n");

  /* oslobadjamo memoriju zauzetu stablima */
  oslobodi_stablo(&koren1);
  oslobodi_stablo(&koren2);

  /* zavrsavamo sa radom programa */
  return 0;
}
