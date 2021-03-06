#ifndef _STABLA_H_
#define _STABLA_H_ 1

/* a) Struktura kojom se predstavlja cvor binarnog pretrazivackog
   stabla */
typedef struct cvor {
  int broj;
  struct cvor *levo;
  struct cvor *desno;
} Cvor;

/* b) Funkcija koja alocira memoriju za novi cvor stabla,
   inicijalizuje polja strukture i vraca pokazivac na novi cvor */
Cvor *napravi_cvor(int broj);

/* c) Funkcija koja dodaje zadati broj u stablo. Povratna vrednost
   funkcije je 0 ako je dodavanje uspesno, odnosno 1 ukoliko je
   doslo do greske */
int dodaj_u_stablo(Cvor ** adresa_korena, int broj);

/* d) Funkcija koja proverava da li se zadati broj nalazi stablu */
Cvor *pretrazi_stablo(Cvor * koren, int broj);

/* e) Funkcija koja pronalazi cvor koji sadrzi najmanju vrednost u
   stablu */
Cvor *pronadji_najmanji(Cvor * koren);

/* f) Funkcija koja pronalazi cvor koji sadrzi najvecu vrednost u
   stablu */
Cvor *pronadji_najveci(Cvor * koren);

/* g) Funkcija koja brise cvor stabla koji sadrzi zadati broj */
void obrisi_element(Cvor ** adresa_korena, int broj);

/* h) Funkcija koja ispisuje stablo u infiksnoj notaciji (Levo
   postablo - Koren - Desno podstablo ) */
void ispisi_stablo_infiksno(Cvor * koren);

/* i) Funkcija koja ispisuje stablo u prefiksnoj notaciji ( Koren -
   Levo podstablo - Desno podstablo ) */
void ispisi_stablo_prefiksno(Cvor * koren);

/* j) Funkcija koja ispisuje stablo u postfiksnoj notaciji ( Levo
   podstablo - Desno postablo - Koren) */
void ispisi_stablo_postfiksno(Cvor * koren);

/* k) Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor ** adresa_korena);

#endif
