#ifndef  _POLINOM_H
#define _POLINOM_H

#include <stdio.h>
#include <stdlib.h>

/* Maksimalni stepen polinoma */
#define MAX_STEPEN 20


/* Polinome predstavljamo strukturom koja cuva koeficijente (koef[i] 
   je koeficijent uz clan x^i) i stepen polinoma */
typedef struct {
  double koef[MAX_STEPEN + 1];
  int stepen;
} Polinom;

/* Funkcija koja ispisuje polinom na stdout u citljivom obliku
   Polinom prenosimo po adresi, da bi ustedeli kopiranje cele
   strukture, vec samo prenosimo adresu na kojoj se nalazi polinom
   kog ispisujemo */
void ispisi(const Polinom * p);

/* Funkcija koja ucitava polinom sa tastature */
Polinom ucitaj();

/* Funkcija racuna vrednost polinoma p u tacki x Hornerovim
   algoritmom */
double izracunaj(const Polinom * p, double x);

/* Funkcija koja sabira dva polinoma */
Polinom saberi(const Polinom * p, const Polinom * q);

/* Funkcija mnozi dva polinoma p i q */
Polinom pomnozi(const Polinom * p, const Polinom * q);

/* Funkcija racuna izvod polinoma p */
Polinom izvod(const Polinom * p);

/* Funkcija racuna n-ti izvod polinoma p */
Polinom nIzvod(const Polinom * p, int n);
#endif
