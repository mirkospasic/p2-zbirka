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
   
/* Funkcija ucitava sa standardnog ulaza realan i imaginaran deo
   kompleksnog broja i smesta ih u strukturu cija adresa je argument
   funkcije */
void ucitaj_kompleksan_broj(KompleksanBroj * z);

/* Funkcija ispisuje na standardan izlaz kompleksan broj z koji joj
   se salje kao argument u obliku (x + y i) */
void ispisi_kompleksan_broj(KompleksanBroj z);

/* Funkcija vraca vrednosti realnog dela kompleksnog broja */
float realan_deo(KompleksanBroj z);

/* Funkcija vraca vrednosti imaginarnog dela kompleksnog broja */
float imaginaran_deo(KompleksanBroj z);

/* Funkcija vraca vrednost modula kompleksnog broja koji joj se salje 
   kao argument */
float moduo(KompleksanBroj z);

/* Funkcija vraca vrednost konjugovano kompleksnog broja koji
   odgovara kompleksnom broju poslatom kao argument */
KompleksanBroj konjugovan(KompleksanBroj z);

/* Funkcija vraca kompleksan broj cija vrednost je jednaka zbiru
   argumenata funkcije */
KompleksanBroj saberi(KompleksanBroj z1, KompleksanBroj z2);

/* Funkcija vraca kompleksan broj cija vrednost je jednaka razlici
   argumenata funkcije */
KompleksanBroj oduzmi(KompleksanBroj z1, KompleksanBroj z2);

/* Funkcija vraca kompleksan broj cija vrednost je jednaka proizvodu
   argumenata funkcije */
KompleksanBroj mnozi(KompleksanBroj z1, KompleksanBroj z2);

/* Funkcija vraca argument kompleksnog broja koji je funkciji poslat
   kao argument */
float argument(KompleksanBroj z);

/* Kraj zakljucanog dela */
#endif
