#ifndef __STABLA_H__
#define __STABLA_H__ 1

/* Struktura kojom se predstavlja čvor drveta */
typedef struct dcvor{
    int broj;
    struct dcvor* levo, *desno;
} Cvor;

/* Funkcija alocira prostor za novi čvor drveta, inicijalizuje polja
    strukture i vraća pokazivač na nov čvor */
Cvor* napravi_cvor(int b );

/* Oslobadjamo dinamički alociran prostor za stablo
 * Nakon oslobadjanja se u pozivajućoj funkciji koren 
 * postavljana NULL, jer je stablo prazno  */
void oslobodi_stablo(Cvor** adresa_korena);


/* Funkcija proverava da li je novi čvor ispravno alociran,
 * i nakon toga prekida program */
void proveri_alokaciju( Cvor* novi);


/* Funkcija dodaje nov čvor u stablo i 
 * ažurira vrednost korena stabla u pozivajućoj funkciji.
 */
void dodaj_u_stablo(Cvor** adresa_korena, int broj);

#endif

