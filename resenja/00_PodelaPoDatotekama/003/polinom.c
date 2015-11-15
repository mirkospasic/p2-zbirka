#include <stdio.h>
#include <stdlib.h>
#include "polinom.h"

void ispisi(const Polinom * p)
{
  /* Ispisivanje polinoma pocinje od najviseg stepena ka najnizem da
     bi polinom bio ispisan na prirodan nacin. Ipisisuju se samo oni
     koeficijenti koji su razliciti od nule. Ispred pozitivnih
     koeficijenata je potrebno ispisati znak + (osim u slucaju
     koeficijenta uz najvisi stepen). */
  int i;
  for (i = p->stepen; i >= 0; i--) {

    if (p->koef[i]) {
      if (p->koef[i] >= 0 && i != p->stepen)
        putchar('+');
      if (i > 1)
        printf("%.2fx^%d", p->koef[i], i);
      else if (i == 1)
        printf("%.2fx", p->koef[i]);
      else
        printf("%.2f", p->koef[i]);
    }
  }
  putchar('\n');
}

Polinom ucitaj()
{
  int i;
  Polinom p;

  /* Ucitava se stepena polinoma */
  scanf("%d", &p.stepen);

  /* Ponavlja se ucitavanje stepena sve dok se ne unese stepen iz
     dozvoljenog opsega */
  while (p.stepen > MAX_STEPEN || p.stepen < 0) {
    printf("Stepen polinoma pogresno unet, pokusajte ponovo: ");
    scanf("%d", &p.stepen);
  }

  /* Unose se koeficijenti polinoma */
  for (i = p.stepen; i >= 0; i--)
    scanf("%lf", &p.koef[i]);

  /* Vraca se procitani polinom */
  return p;
}

double izracunaj(const Polinom * p, double x)
{
  /* Rezultat se na pocetku inicijalizuje na nulu, a potom se u
     svakoj iteraciji najpre mnozi sa x, a potom i uvecava za
     vrednost odgovarajuceg koeficijenta */

  /* Primer: Hornerov algoritam za polinom x^4+2x^3+3x^2+2x+1:
     x^4+2x^3+3x^2+2x+1 = (((x+2)*x + 3)*x + 2)*x + 1 */

  double rezultat = 0;
  int i = p->stepen;
  for (; i >= 0; i--)
    rezultat = rezultat * x + p->koef[i];
  return rezultat;
}

Polinom saberi(const Polinom * p, const Polinom * q)
{
  Polinom rez;
  int i;

  /* Stepen rezultata ce odgovarati stepenu polinoma sa vecim
     stepenom */
  rez.stepen = p->stepen > q->stepen ? p->stepen : q->stepen;

  /* Racunaju se svi koeficijenti rezultujuceg polinoma tako sto se
     sabiraju koeficijenti na odgovarajucim pozicijama polinoma koje
     sabiramo. Ukoliko je pozicija za koju se racuna koeficijent veca 
     od stepena nekog od polaznih polinoma podrazumeva se da je
     koeficijent jednak koeficijentu uz odgovarajuci stepen iz drugog 
     polinoma */
  for (i = 0; i <= rez.stepen; i++)
    rez.koef[i] =
        (i > p->stepen ? 0 : p->koef[i]) +
        (i > q->stepen ? 0 : q->koef[i]);

  /* Vraca se dobijeni polinom */
  return rez;

}

Polinom pomnozi(const Polinom * p, const Polinom * q)
{
  int i, j;
  Polinom r;

  /* Stepen rezultata ce odgovarati zbiru stepena polaznih polinoma */
  r.stepen = p->stepen + q->stepen;
  if (r.stepen > MAX_STEPEN) {
    fprintf(stderr, "Stepen proizvoda polinoma izlazi iz opsega\n");
    exit(EXIT_FAILURE);
  }

  /* Svi koeficijenti rezultujuceg polinoma se inicijalizuju na nulu */
  for (i = 0; i <= r.stepen; i++)
    r.koef[i] = 0;

  /* U svakoj iteraciji odgovarajuci koeficijent rezultata se uvecava
     za proizvod odgovarajucih koeficijenata iz polaznih polinoma */
  for (i = 0; i <= p->stepen; i++)
    for (j = 0; j <= q->stepen; j++)
      r.koef[i + j] += p->koef[i] * q->koef[j];

  /* Vraca se dobijeni polinom */
  return r;
}

Polinom izvod(const Polinom * p)
{
  int i;
  Polinom r;

  /* Izvod polinoma ce imati stepen za jedan stepen manji od stepena
     polaznog polinoma. Ukoliko je stepen polinoma p vec nula, onda
     je rezultujuci polinom nula (izvod od konstante je nula). */
  if (p->stepen > 0) {
    r.stepen = p->stepen - 1;

    /* Racunanje koeficijenata rezultata na osnovu koeficijenata
       polaznog polinoma */
    for (i = 0; i <= r.stepen; i++)
      r.koef[i] = (i + 1) * p->koef[i + 1];
  } else
    r.koef[0] = r.stepen = 0;

  /* Vraca se dobijeni polinom */
  return r;
}

Polinom nIzvod(const Polinom * p, int n)
{
  int i;
  Polinom r;

  /* Provera da li je n nenegativna vrednost */
  if (n < 0) {
    fprintf(stderr, "U n-tom izvodu polinoma, n mora biti >=0 \n");
    exit(EXIT_FAILURE);
  }

  /* Nulti izvod je bas taj polinom */
  if (n == 0)
    return *p;

  /* Za n>=1, n-ti izvod se racuna tako sto se n puta pozove funkcija
     za racunanje prvog izvoda polinoma */
  r = izvod(p);
  for (i = 1; i < n; i++)
    r = izvod(&r);

  /* Vraca se dobijeni polinom */
  return r;
}
