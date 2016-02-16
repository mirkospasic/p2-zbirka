/* Zaglavlje kompleksan_broj.h sadrzi definiciju tipa KompleksanBroj 
   i deklaracije funkcija za rad sa kompleksnim brojevima. Zaglavlje
   nikada ne treba da sadrzi definicije funckija. Da bi neki program
   mogao da koristi ove brojeve i funkcije iz ove biblioteke,
   neophodno je da ukljuci ovo zaglavlje. */

/* Ovim pretprocesorskim direktivama se zakljucava zaglavlje i
   onemogucava se da se sadrzaj zaglavlja vise puta ukljuci. Niska
   posle kljucne reci ifndef je proizvoljna, ali treba da se ponovi u 
   narednoj pretrocesorskoj define direktivi. */
#ifndef  _KOMPLEKSAN_BROJ_H
#define _KOMPLEKSAN_BROJ_H

/* Zaglavlja standardne biblioteke koje sadrze deklaracije funkcija
   koje se koriste u definicijama funkcija navedenim u kompleksan_broj.c */
#include <stdio.h>
#include <math.h>

/* Struktura KompleksanBroj */
typedef struct {
  float real;
  float imag;
} KompleksanBroj;

/* Deklaracije funkcija za rad sa kompleksnim brojevima. Sve one su
   definisane u kompleksan_broj.c */

/* Funkcija ucitava sa standardnog ulaza realan i imaginara deo
   kompleksnog broja i smesta ih u strukturu cija je adresa argument
   funkcije */
void ucitaj_kompleksan_broj(KompleksanBroj * z);

/* Funkcija ispisuje na standardan izlaz zadati kompleksni broj u
   obliku (x + i y) */
void ispisi_kompleksan_broj(KompleksanBroj z);

/* Funkcija vraca vrednosti realnog dela kompleksnog broja */
float realan_deo(KompleksanBroj z);

/* Funkcija vraca vrednosti imaginarnog dela kompleksnog broja */
float imaginaran_deo(KompleksanBroj z);

/* Funkcija vraca vrednost modula zadatog kompleksnog broja */
float moduo(KompleksanBroj z);

/* Funkcija vraca vrednost konjugovano kompleksnog broja koji
   odgovara kompleksnom broju argumentu */
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

/* Funkcija vraca argument zadatog kompleksnog broja */
float argument(KompleksanBroj z);

/* Kraj zakljucanog dela */
#endif
