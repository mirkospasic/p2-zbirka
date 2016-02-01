#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Struktura kojom je predstavljan kompleksan broj sadrzi realan i
   imaginaran deo kompleksnog broja */
typedef struct {
  float real;
  float imag;
} KompleksanBroj;

/* Funkcija ucitava sa standardnog ulaza realan i imaginara deo
   kompleksnog broja i smesta ih u strukturu cija je adresa argument
   funkcije */
void ucitaj_kompleksan_broj(KompleksanBroj * z)
{
  /* Ucitavanje vrednosti sa standardnog ulaza */
  printf("Unesite realni i imaginarni deo kompleksnog broja: ");
  scanf("%f", &z->real);
  scanf("%f", &z->imag);
}

/* Funkcija ispisuje na standardan izlaz zadati kompleksni broj u
   obliku (x + i y). Ovoj funkciji se argument prenosi po vrednosti
   jer se u samoj funkciji ne menja njegova vrednost */
void ispisi_kompleksan_broj(KompleksanBroj z)
{
  /* Zapocinje se sa ispisom */
  printf("(");

  /* Razlikuju se dva slucaja: 1) realni deo kompleksnog broja
     razlicit od nule: tada se realni deo ispisuje na standardni
     izlaz, nakon cega se ispisuje znak + ili - u zavisnosti da li je 
     imaginarni deo pozitivan ili negativan, a potom i apsolutna
     vrednost imaginarnog dela kompleksnog broja 2) realni deo
     kompleksnog broja je nula: tada se samo ispisuje imaginaran deo, 
     s tim sto se ukoliko su oba dela nula ispisuje samo 0, bez
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

/* Funkcija vraca vrednost modula zadatog kompleksnog broja */
float moduo(KompleksanBroj z)
{
  return sqrt(z.real * z.real + z.imag * z.imag);
}

/* Funkcija vraca vrednost konjugovano kompleksnog broja koji
   odgovara kompleksnom broju argumentu */
KompleksanBroj konjugovan(KompleksanBroj z)
{
  /* Konjugovano kompleksan broj z se dobija tako sto se promeni znak 
     imaginarnom delu kompleksnog broja */

  KompleksanBroj z1 = z;

  z1.imag *= -1;

  return z1;
}

/* Funkcija vraca kompleksan broj cija vrednost je jednaka zbiru
   argumenata funkcije */
KompleksanBroj saberi(KompleksanBroj z1, KompleksanBroj z2)
{
  /* Rezultat sabiranja dva kompleksna broja z1 i z2 je kompleksan
     broj ciji je realan deo zbir realnih delova kompleksnih brojeva
     z1 i z2, a imaginaran deo zbir imaginarnih delova kompleksnih
     brojeva z1 i z2 */

  KompleksanBroj z = z1;

  z.real += z2.real;
  z.imag += z2.imag;

  return z;
}

/* Funkcija vraca kompleksan broj cija vrednost je jednaka razlici
   argumenata funkcije */
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

/* Funkcija vraca kompleksan broj cija vrednost je jednaka proizvodu
   argumenata funkcije */
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

/* Funkcija vraca argument zadatog kompleksnog broja */
float argument(KompleksanBroj z)
{
  /* Argument kompleksnog broja z se racuna pozivanjem funkcije atan2 
     iz biblioteke math.h */

  return atan2(z.imag, z.real);
}

int main()
{
  char c;

  /* Deklaracija 3 promenljive tipa KompleksanBroj */
  KompleksanBroj z1, z2, z;

  /* Ucitavanje prvog kompleksnog broja, a potom i njegovo
     ispisivanje na standardni izlaz */
  ucitaj_kompleksan_broj(&z1);
  ispisi_kompleksan_broj(z1);
  printf("\n");

  /* Ucitavanje drugog kompleksnog broja, a potom njegovo ispisivanje 
     na standardni izlaz */
  ucitaj_kompleksan_broj(&z2);
  ispisi_kompleksan_broj(z2);
  printf("\n");

  /* Ucitavanje i provera znaka na osnovu koga korisnik bira
     aritmeticku operaciju koja ce se izvrsiti nad kompleksnim
     brojevima */
  getchar();
  printf("Unesite znak (+,-,*): ");
  scanf("%c", &c);
  if (c != '+' && c != '-' && c != '*') {
    printf("Greska: nedozvoljena vrednost operatora!\n");
    exit(EXIT_FAILURE);
  }

  /* Analizira se uneti operator */
  if (c == '+') {
    /* Racuna se zbir */
    z = saberi(z1, z2);
  } else if (c == '-') {
    /* Racuna se razlika */
    z = oduzmi(z1, z2);
  } else {
    /* Racuna se proizvod */
    z = mnozi(z1, z2);
  }

  /* Ispisuje se rezultat */  
  ispisi_kompleksan_broj(z1);
  printf(" %c ", c);
  ispisi_kompleksan_broj(z2);
  printf("  =  ");
  ispisi_kompleksan_broj(z);  

  /* Ispisuje se realan, imaginaran deo i moduo prvog kompleksnog
     broja */
  printf("\nRealni_deo: %.f\nImaginarni_deo: %f\nModuo: %f\n",
         realan_deo(z), imaginaran_deo(z), moduo(z));

  /* Izracunava se i ispisuje konjugovano kompleksan broj drugog
     kompleksnog broja */
  printf("Konjugovano kompleksan broj: ");
  ispisi_kompleksan_broj(konjugovan(z));
  printf("\n");

  /* Testira se funkcija koja racuna argument kompleksnog broja */
  printf("Argument kompleksnog broja: %f\n", argument(z));

  exit(EXIT_SUCCESS);
}
