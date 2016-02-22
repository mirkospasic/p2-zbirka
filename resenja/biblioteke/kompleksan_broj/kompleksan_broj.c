#include <stdio.h>
#include <math.h>

/* Ukljucuje se zaglavlje za rad sa kompleksnim brojevima, jer je
   neophodno da bude poznata definicija tipa KompleksanBroj. */
#include "kompleksan_broj.h"

void ucitaj_kompleksan_broj(KompleksanBroj * z)
{
  /* Ucitavanje vrednosti sa standardnog ulaza */
  printf("Unesite realan i imaginaran deo kompleksnog broja: ");
  scanf("%f", &z->real);
  scanf("%f", &z->imag);
}

void ispisi_kompleksan_broj(KompleksanBroj z)
{
  /* Zapocinje se sa ispisom */
  printf("(");

  /* Razlikuju se dva slucaja: 1) realni deo kompleksnog broja
     razlicit od nule: tada se realni deo ispisuje na standardni
     izlaz, nakon cega se ispisuje znak + ili - u zavisnosti da li
     je imaginarni deo pozitivan ili negativan, a potom i apsolutna
     vrednost imaginarnog dela kompleksnog broja 2) realni deo
     kompleksnog broja je nula: tada se samo ispisuje imaginaran
     deo, s tim sto se ukoliko su oba dela nula ispisuje samo 0, bez 
     decimalnih mesta */
  if (z.real != 0) {
    printf("%.2f", z.real);

    if (z.imag > 0)
      printf(" + %.2f i", z.imag);
    else if (z.imag < 0)
      printf(" - %.2f i", -z.imag);
  } else {
    if (z.imag == 0)
      printf("0");
    else
      printf("%.2f i", z.imag);
  }

  /* Zavrsava se sa ispisom */
  printf(")");
}

float realan_deo(KompleksanBroj z)
{
  /* Vraca se vrednost realnog dela kompleksnog broja */
  return z.real;
}

float imaginaran_deo(KompleksanBroj z)
{
  /* Vraca se vrednost imaginarnog dela kompleksnog broja */
  return z.imag;
}

float moduo(KompleksanBroj z)
{
  /* Koriscenjem funkcije sqrt racuna se moduo kompleksnog broja */
  return sqrt(z.real * z.real + z.imag * z.imag);
}

KompleksanBroj konjugovan(KompleksanBroj z)
{
  /* Konjugovano kompleksan broj se dobija od datog broja z tako
     sto se promeni znak imaginarnom delu kompleksnog broja */
  KompleksanBroj z1 = z;
  z1.imag *= -1;
  return z1;
}

KompleksanBroj saberi(KompleksanBroj z1, KompleksanBroj z2)
{
  /* Rezultat sabiranja dva kompleksna broja z1 i z2 je kompleksan
     broj ciji je realan deo zbir realnih delova kompleksnih
     brojeva z1 i z2, a imaginaran deo zbir imaginarnih delova
     kompleksnih brojeva z1 i z2 */
  KompleksanBroj z = z1;
  z.real += z2.real;
  z.imag += z2.imag;

  return z;
}

KompleksanBroj oduzmi(KompleksanBroj z1, KompleksanBroj z2)
{
  /* Rezultat oduzimanja dva kompleksna broja z1 i z2 je kompleksan
     broj ciji je realan deo razlika realnih delova kompleksnih
     brojeva z1 i z2, a imaginaran deo razlika imaginarnih delova
     kompleksnih brojeva z1 i z2 */
  KompleksanBroj z = z1;
  z.real -= z2.real;
  z.imag -= z2.imag;

  return z;
}

KompleksanBroj mnozi(KompleksanBroj z1, KompleksanBroj z2)
{
  /* Rezultat mnozenja dva kompleksna broja z1 i z2 je kompleksan
     broj ciji se realan i imaginaran deo racunaju po formuli za
     mnozenje kompleksnih brojeva z1 i z2 */
  KompleksanBroj z;
  z.real = z1.real * z2.real - z1.imag * z2.imag;
  z.imag = z1.real * z2.imag + z1.imag * z2.real;

  return z;
}

float argument(KompleksanBroj z)
{
  /* Argument kompleksnog broja z se racuna pozivanjem funkcije
     atan2 iz biblioteke math.h */
  return atan2(z.imag, z.real);
}
