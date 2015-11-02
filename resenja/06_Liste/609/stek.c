#include "stek.h"

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

void oslobodi_stek(Cvor ** adresa_vrha)
{
  Cvor *pomocni;
  while (*adresa_vrha != NULL) {
    pomocni = *adresa_vrha;
    *adresa_vrha = (*adresa_vrha)->sledeci;
    free(pomocni);
  }
}

int potisni_na_stek(Cvor ** adresa_vrha, char *etiketa)
{
  Cvor *novi = napravi_cvor(etiketa);
  if (novi == NULL)
    return 1;

  novi->sledeci = *adresa_vrha;
  *adresa_vrha = novi;
  return 0;
}

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

char *vrh_steka(Cvor * vrh)
{
  if (vrh == NULL)
    return NULL;
  return vrh->etiketa;
}

void prikazi_stek(Cvor * vrh)
{
  for (; vrh != NULL; vrh = vrh->sledeci)
    printf("<%s>\n", vrh->etiketa);
}

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
