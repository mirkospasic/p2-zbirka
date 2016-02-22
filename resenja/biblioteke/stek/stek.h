#ifndef _STEK_H_
#define _STEK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

#define OTVORENA 1
#define ZATVORENA 2

#define VAN_ETIKETE 0
#define PROCITANO_MANJE 1
#define U_ETIKETI 2

/* Struktura kojim se predstavlja cvor liste sadrzi ime etikete i
   pokazivac na sledeci cvor */
typedef struct cvor {
  char etiketa[MAX];
  struct cvor *sledeci;
} Cvor;

/* Funkcija kreira novi cvor, upisuje u njega etiketu i vraca
   njegovu adresu ili NULL ako alokacija nije bila uspesna */
Cvor *napravi_cvor(char *etiketa);

/* Funkcija oslobadja memoriju zauzetu stekom */
void oslobodi_stek(Cvor ** adresa_vrha);

/* Funkcija postavlja na vrh steka novu etiketu. U slucaju greske
   pri alokaciji za novi cvor funkcija vraca 1, inace vraca 0 */
int potisni_na_stek(Cvor ** adresa_vrha, char *etiketa);

/* Funkcija skida sa vrha steka etiketu. Ako je drugi argument
   pokazivac razlicit od NULL, tada u niz karaktera na koji on
   pokazuje upisuje ime etikete koja je upravo skinuta sa steka dok
   u suprotnom ne radi nista. Funkcija vraca 0 ako je stek prazan
   (pa samim tim nije bilo moguce skinuti vrednost sa steka) ili 1 u
   suprotnom */
int skini_sa_steka(Cvor ** adresa_vrha, char *etiketa);

/* Funkcija vraca pokazivac na string koji sadrzi etiketu na vrhu
   steka. Ukoliko je stek prazan, vraca NULL */
char *vrh_steka(Cvor * vrh);

/* Funkcija prikazuje stek od vrha prema dnu */
void prikazi_stek(Cvor * vrh);

/* Funkcija iz datoteke kojoj odgovara pokazivac f cita sledecu
   etiketu, i upisuje je u nisku na koju pokazuje pokazivac
   etiketa. Vraca EOF u slucaju da se dodje do kraja datoteke pre
   nego sto se procita etiketa. Vraca OTVORENA, ako je procitana
   otvorena etiketa, odnosno ZATVORENA, ako je procitana zatvorena
   etiketa */
int uzmi_etiketu(FILE * f, char *etiketa);

#endif
