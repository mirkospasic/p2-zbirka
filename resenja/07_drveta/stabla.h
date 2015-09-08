#ifndef __STABLA_H__
#define __STABLA_H__ 1

/* Struktura kojom se predstavlja cvor drveta */
typedef struct cvor{
  int broj;
  struct cvor* levo, *desno;
}Cvor;


/* Funkcija koja alocira memoriju za novi cvor stabla,
inicijalizuje polja i vraca pokazivac na novi cvor */
Cvor* napravi_cvor(int broj);

/* Funkcija koja proverava da li je novi cvor uspesno kreiran. */
void proveri_alokaciju( Cvor* novi_cvor);

/* Funkcija koja dodaje novu vrednost u stablo */
void dodaj_u_stablo(Cvor** adresa_korena, int broj);

/* Funkcija koja pretrazuje stablo */
Cvor* pretrazi_stablo(Cvor * koren, int broj);

/* Funkcija koja pronalazi najveci cvor stabla */
Cvor * pronadji_najveci(Cvor * koren);

/* Funkcija koja pronalazi najmanji cvor stabla */
Cvor * pronadji_najmanji(Cvor * koren);

/* Funkcija koja brise cvor stabla koji sadrzi zadati broj */
void obrisi_element(Cvor** adresa_korena, int broj);

/* Funkcija koja ispisuje sadrzaj stabla*/
void prikazi_stablo(Cvor * koren);

/* Funkcija koja oslobadja memoriju zauzetu stablom */
void oslobodi_stablo(Cvor** adresa_korena);

#endif

