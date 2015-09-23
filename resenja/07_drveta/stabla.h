#ifndef __STABLA_H__
#define __STABLA_H__ 1

/* Struktura kojom se predstavlja cvor binarnog pretrazivackog
   stabla */
typedef struct cvor {
  int broj;
  struct cvor *levo, *desno;
} Cvor;

/* Funkcija koja alocira memoriju za novi cvor stabla,
   inicijalizuje polja strukture i vraca pokazivac na novi cvor */
Cvor *napravi_cvor(int broj);

/* Funkcija koja proverava uspesnost kreiranja novog cvora
   stabla. */
void proveri_alokaciju(Cvor * novi_cvor);

/* Funkcija koja dodaje zadati broj u stablo */
void dodaj_u_stablo(Cvor ** adresa_korena, int broj);

/* Funkcija koja proverava da li se zadati broj nalazi u stablu */
Cvor *pretrazi_stablo(Cvor * koren, int broj);

/* Funkcija koja pronalazi cvor koji sadrzi najmanju vrednost u
   stablu */
Cvor *pronadji_najmanji(Cvor * koren);

/* Funkcija koja pronalazi cvor koji sadrzi najveci vrednost u
   stablu */
Cvor *pronadji_najveci(Cvor * koren);

/* Funkcija brise element iz stabla ciji je broj upravo jednak
   broju n. Funkcija azurira koren stabla u pozivajucoj
   funkciji, jer u ovoj funkciji koren moze biti promenjen u
   funkciji. */
void obrisi_element(Cvor ** adresa_korena, int broj);

/* Funkcija koja ispisuje sadrzaj stabla u infiksnoj notaciji
   (levo podstablo - koren - desno podstablo) */
void prikazi_stablo(Cvor * koren);

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** adresa_korena);

#endif
