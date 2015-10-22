/* complex.h */
/* 
   Zaglavlje complex.h sadrzi definiciju tipa KompleksanBroj i
   deklaracije funkcija za rad sa kompleksnim brojevima. Zaglavlje
   nikada ne treba da sadrzi definicije funckija. Da bi neki program
   mogao da koristi ove brojeve i funkcije iz ove biblioteke,
   neophodno je da ukljuci ovo zaglavlje. */

/* Ovim pretprocesorskim direktivama se zakljucava zaglavlje i time
   onemogucujemo da se sadrzaj zaglavlja vise puta ukljuci. Niska
   posle kljucne reci ifndef je proizvoljna, ali treba da se ponovi u 
   narednoj pretrocesorskoj define direktivi. */
#ifndef  _COMPLEX_H
#define _COMPLEX_H

/* Zaglavlja standardne biblioteke koje sadrze deklaracije funkcija
   koje se koriste u definicijama funkcija navedenim u complex.c */
#include <stdio.h>
#include <math.h>

/* Struktura KompleksanBroj */
typedef struct {
  float real;
  float imag;
} KompleksanBroj;

/* Deklaracije funkcija za rad sa kompleksnim brojevima. Sve one su
   definisane u complex.c */
void ucitaj_kompleksan_broj(KompleksanBroj * z);

void ispisi_kompleksan_broj(KompleksanBroj z);

float realan_deo(KompleksanBroj z);

float imaginaran_deo(KompleksanBroj z);

float moduo(KompleksanBroj z);

KompleksanBroj konjugovan(KompleksanBroj z);

KompleksanBroj saberi(KompleksanBroj z1, KompleksanBroj z2);

KompleksanBroj oduzmi(KompleksanBroj z1, KompleksanBroj z2);

KompleksanBroj mnozi(KompleksanBroj z1, KompleksanBroj z2);

float argument(KompleksanBroj z);

/* Kraj zakljucanog dela */
#endif
