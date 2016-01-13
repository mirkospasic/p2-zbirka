#ifndef  _POLINOM_H
#define _POLINOM_H

#include <stdio.h>
#include <stdlib.h>

/* Maksimalni stepen polinoma */
#define MAKS_STEPEN 20


/* Polinomi se predstavljaju strukturom koja cuva koeficijente
   (koef[i] je koeficijent uz clan x^i) i stepen polinoma */
typedef struct {
  double koef[MAKS_STEPEN + 1];
  int stepen;
} Polinom;

/* Funkcija koja ispisuje polinom na standardni izlaz u citljivom
   obliku. Polinom se prenosi po adresi da bi se ustedela memorija:
   ne kopira se cela struktura, vec se samo prenosi adresa na kojoj
   se nalazi polinom koji ispisujemo */
void ispisi(const Polinom * p);

/* Funkcija koja ucitava polinom sa tastature */
Polinom ucitaj();

/* Funkcija racuna i vraca vrednost polinoma p u tacki x Hornerovim
   algoritmom */
double izracunaj(const Polinom * p, double x);

/* Funkcija koja sabira dva polinoma */
Polinom saberi(const Polinom * p, const Polinom * q);

/* Funkcija koja mnozi dva polinoma p i q */
Polinom pomnozi(const Polinom * p, const Polinom * q);

/* Funkcija koja racuna izvod polinoma p */
Polinom izvod(const Polinom * p);

/* Funkcija koja racuna n-ti izvod polinoma p */
Polinom n_izvod(const Polinom * p, int n);
#endif
