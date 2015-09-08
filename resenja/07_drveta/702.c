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
Cvor *napravi_cvor(char *rec) {
  
  /* Alociramo memoriju za novi cvor */
  Cvor *novi_cvor = (Cvor *) malloc(sizeof(Cvor));
  if (novi_cvor == NULL) 
      return NULL;

  /* Alociramo memoriju za zadatu rec: potrebno je rezervisati
memoriju za svaki karakter reci ukljucujuci i terminirajucu nulu */
  novi_cvor->rec = (char*)malloc((strlen(rec)+1)*sizeof(char));
  if( novi_cvor->rec == NULL) {
      free(novi_cvor);
      return NULL;   
  }
  
  /* Inicijalizacija polja u novom cvoru */
  strcpy(novi_cvor->rec, rec);
  novi_cvor->brojac = 1;
  novi_cvor->levo = NULL;
  novi_cvor->desno = NULL;

  /* Vracamo adresu novog cvora */
  return novi_cvor;
}

/* Funkcija koja proverava uspesnost kreiranja novog cvora stabla*/
void proveri_alokaciju(Cvor* novi_cvor) {
  
  /* Ukoliko je cvor neuspesno kreiran */ 
  if( novi_cvor == NULL) {
    /* Ispisuje se odgovarajuca poruka i prekida
izvrsavanje
programa */ 
      fprintf(stderr, "Malloc greska za nov cvor!\n");
      exit(EXIT_FAILURE);
  }
}

/* Funkcija koja dodaje novu rec u stablo. */
void dodaj_u_stablo(Cvor** adresa_korena, char *rec) {
  
  /* Ako je stablo prazno */
  if( *adresa_korena == NULL) { 
      /* Kreiramo novi cvor */
      Cvor* novi = napravi_cvor(rec);
      proveri_alokaciju(novi);
      /* i proglasavamo ga korenom stabla */
      *adresa_korena = novi;
      return;
  }
  
  /* U suprotnom trazimo odgovarajucu poziciju za novu rec */
  
  /* Ako je rec leksikografski manju od reci u korenu ubacujemo
je u levo podstablo */
  if (strcmp(rec, (*adresa_korena)->rec) < 0)
      dodaj_u_stablo(&(*adresa_korena)->levo, rec);
  else
      /* Ako je rec leksikografski veca od reci u korenu
ubacujemo je u desno podstablo */
      if (strcmp(rec, (*adresa_korena)->rec) > 0)
          dodaj_u_stablo(&(*adresa_korena)->desno, rec);
      else
          /* Ako je rec jednaka reci u korenu, uvecavamo njen
broj pojavljivanja */
          (*adresa_korena)->brojac++;
}


/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor** adresa_korena)  {
  
  /* Ako je stablo prazno, nepotrebno je oslobadjati memoriju */
  if(*adresa_korena == NULL)
      return;
  
  /* Inace ...*/
  /* Oslobadjamo memoriju zauzetu levim podstablom */
  oslobodi_stablo(&(*adresa_korena)->levo);
  /* Oslobadjamo memoriju zauzetu desnim podstablom */
  oslobodi_stablo(&(*adresa_korena)->desno);
  
  /* Oslobadjamo memoriju zauzetu korenom */
  free((*adresa_korena)->rec);
  free(*adresa_korena);
  
  /* Proglasavamo stablo praznim */
  *adresa_korena = NULL;   
}



/* Funkcija koja pronalazi cvor koji sadrzi najfrekventniju rec (rec
sa najvecim brojem pojavljivanja)  */
Cvor *nadji_najfrekventniju_rec(Cvor * koren) {  
  
  Cvor *max, *max_levo, *max_desno;

  /* Ako je stablo prazno, prekidamo sa pretragom */
  if (koren == NULL)
      return NULL;

  /* Pronalazimo najfrekventniju reci u levom podstablu */
  max_levo = nadji_najfrekventniju_rec(koren->levo);
  
  /* Pronalazimo najfrekventniju reci u desnom podstablu */
  max_desno = nadji_najfrekventniju_rec(koren->desno);

  /* Trazimo maksimum vrednosti pojavljivanja reci iz
levog podstabla, korena i desnog podstabla */
  max = koren;
  if (max_levo != NULL && max_levo->brojac > max->brojac)
      max = max_levo;
  if (max_desno != NULL && max_desno->brojac > max->brojac)
      max = max_desno;

  /* Vracamo adresu cvora sa najvecim brojacem */
  return max;
}


/* Funkcija koja ispisuje reci iz stabla u leksikografskom poretku
pracene brojem pojavljivanja */
void prikazi_stablo(Cvor * koren) {  

  /* Ako je stablo prazno, zavrsavamo sa ispisom */
  if (koren == NULL)
      return;

  /* Zbog leksikografskog poretka, prvo ispisujemo sve reci iz
levog podstabla */
  prikazi_stablo(koren->levo);
  /* Zatim ispisujemo rec iz korena */
  printf("%s: %d\n", koren->rec, koren->brojac);
  /* I nastavljamo sa ispisom reci iz desnog podstabla */
  prikazi_stablo(koren->desno);
}

/* Funkcija ucitava sledecu rec iz zadate datoteke i upisuje je
  u niz rec. Maksimalna duzina reci je odredjena argumentom max.
  Funkcija vraca EOF ako nema vise reci ili 0 u suprotnom.
  Rec je niz malih ili velikih slova.*/
int procitaj_rec(FILE * f, char rec[], int max) {
  /* karakter koji citamo */
  int c;
  /* indeks pozicije na koju se smesta procitani karakter */
  int i = 0;

  /* Sve dok ima mesta za jos jedan karakter u nizu
      i dokle god nismo stigli do kraja datoteke... */
  while (i < max - 1 && (c = fgetc(f)) != EOF) {
      /* Proveravamo da li je procitani karakter slovo */
      if (isalpha(c))
          /* Ako jeste, smestamo ga u niz  - pritom vrsimo
konverziju u mala slova jer program treba da bude neosetljiv na
razliku izmedju malih i velikih slova */            
          rec[i++] = tolower(c);      
      else
          /* Ako nije, proveravamo da li smo procitali barem jedno
slovo nove rece  */
          /* Ako jesmo prekidamo sa citanjem */
          if (i > 0)                         
              break;                              
          
          /*  U suprotnom idemo na sledecu iteraciju */
  }

  /* Dodajemo na rec terminirajucu nulu */
  rec[i] = '\0';

  /* Vracamo 0 ako smo procitali rec, EOF u suprotnom */
  return i > 0 ? 0 : EOF;
}


int main(int argc, char **argv)  {
  Cvor *koren = NULL, *max;
  FILE *f;
  char rec[MAX];

  /* Proveravamo da li je navedeno ime datoteke prilikom
pokretanja programa */
  if (argc < 2)  {
      fprintf(stderr, "Nedostaje ime ulazne datoteke!\n");
      exit(EXIT_FAILURE);
  }

  /* Otvaramo datoteku iz koje citamo reci */
  if ((f = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "fopen() greska pri otvaranju %s\n", argv[1]);
      exit(EXIT_FAILURE);
  }

  /* Ucitavamo reci iz datoteke i smestamo u binarno stablo pretrage.
*/
  while (procitaj_rec(f, rec, MAX) != EOF) 
      dodaj_u_stablo(&koren, rec);
  
  /* Posto smo zavrsili sa citanjem reci zatvaramo datoteku */
  fclose(f);

  /* Prikazujemo sve reci iz teksta i brojeve njihovih
pojavljivanja. */
  prikazi_stablo(koren);

  /* Pronalazimo najfrekventniju rec */
  max = nadji_najfrekventniju_rec(koren);
  
  /* Ako takve reci nema... */
  if (max== NULL)
      /* Ispisujemo odgovarajuce obavestenje */
      printf("U tekstu nema reci!\n");
  else
      /* Inace, ispisujemo broj pojavljivanja reci */
      printf("Najcesca rec: %s (pojavljuje se %d puta)\n", max->rec,
max->brojac);


  /* Oslobadjamo dinamicki alociran prostor za stablo */
  oslobodi_stablo(&koren);

  /* Zavrsavamo sa programom */
  return 0;
}
