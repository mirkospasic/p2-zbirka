/* complex.c */

/* Ukljucuje se zaglavlje neophodno za rad sa kompleksnim brojevima.
   Ovde je to neophodno jer nam je neophodno da bude poznata
   definicija tipa KompleksanBroj. Takodje, time su ukljucena
   zaglavlja standardne biblioteke koja su navedena u complex.h */
#include "complex.h"

/* Funkcija ucitava sa standardnog ulaza realan i imaginaran deo
   kompleksnog broja i smesta ih u strukturu cija adresa je argument
   funkcije */
void ucitaj_kompleksan_broj(KompleksanBroj * z)
{
  printf("Unesite realan i imaginaran deo kompleksnog broja: ");
  scanf("%f", &z->real);
  scanf("%f", &z->imag);
}

/* Funkcija ispisuje na standardan izlaz kompleksan broj z koji joj
   se salje kao argument u obliku (x + y i) */
void ispisi_kompleksan_broj(KompleksanBroj z)
{
  printf("(");
  if (z.real != 0) {
    printf("%.2f", z.real);

    if (z.imag > 0)
      printf(" + %.2f i", z.imag);
    else if (z.imag < 0)
      printf(" - %.2f i", -z.imag);
  } else
    printf("%.2f i", z.imag);

  if (z.imag == 0 && z.real == 0)
    printf("0");

  printf(")");
}

/* Funkcija vraca vrednosti realnog dela kompleksnog broja */
float realan_deo(KompleksanBroj z)
{
  return z.real;
}

/* Funkcija vraca vrednosti imaginarnog dela kompleksnog broja */
float imaginaran_deo(KompleksanBroj z)
{
  return z.imag;
}

/* Funkcija vraca vrednost modula kompleksnog broja koji joj se salje 
   kao argument */
float moduo(KompleksanBroj z)
{
  return sqrt(z.real * z.real + z.imag * z.imag);
}

/* Funkcija vraca vrednost konjugovano kompleksnog broja koji
   odgovara kompleksnom broju poslatom kao argument */
KompleksanBroj konjugovan(KompleksanBroj z)
{
  KompleksanBroj z1 = z;
  z1.imag *= -1;
  return z1;
}

/* Funkcija vraca kompleksan broj cija vrednost je jednaka zbiru
   argumenata funkcije */
KompleksanBroj saberi(KompleksanBroj z1, KompleksanBroj z2)
{
  KompleksanBroj z = z1;

  z.real += z2.real;
  z.imag += z2.imag;

  return z;
}

/* Funkcija vraca kompleksan broj cija vrednost je jednaka razlici
   argumenata funkcije */
KompleksanBroj oduzmi(KompleksanBroj z1, KompleksanBroj z2)
{
  KompleksanBroj z = z1;

  z.real -= z2.real;
  z.imag -= z2.imag;

  return z;
}

/* Funkcija vraca kompleksan broj cija vrednost je jednaka proizvodu
   argumenata funkcije */
KompleksanBroj mnozi(KompleksanBroj z1, KompleksanBroj z2)
{
  KompleksanBroj z;

  z.real = z1.real * z2.real - z1.imag * z2.imag;
  z.imag = z1.real * z2.imag + z1.imag * z2.real;

  return z;
}

/* Funkcija vraca argument kompleksnog broja koji je funkciji poslat
   kao argument */
float argument(KompleksanBroj z)
{
  return atan2(z.imag, z.real);
}
