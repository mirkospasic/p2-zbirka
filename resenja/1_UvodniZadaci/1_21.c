#include <stdio.h>

/* a) Funkcija racuna n-ti element u nizu F - iterativna verzija */
int f_iterativna(int n, int a, int b)
{
  int i;
  int f_0 = 0;
  int f_1 = 1;
  int tmp;

  if (n == 0)
    return 0;

  for (i = 2; i <= n; i++) {
    tmp = a * f_1 + b * f_0;
    f_0 = f_1;
    f_1 = tmp;
  }

  return f_1;
}

/* b) Funkcija racuna n-ti element u nizu F - rekurzivna verzija */
int f_rekurzivna(int n, int a, int b)
{
  /* Izlaz iz rekurzije */
  if (n == 0 || n == 1)
    return n;

  /* Rekurzivni pozivi */
  return a * f_rekurzivna(n - 1, a, b) +
      b * f_rekurzivna(n - 2, a, b);
}

/* NAPOMENA: U slucaju da se rekurzijom problem svodi na vise manjih
   podproblema koji se mogu preklapati, postoji opasnost da se
   pojedini podproblemi manjih dimenzija resavaju veci broj puta.
   Npr. F(20) = a*F(19) + b*F(18), a F(19) = a*F(18) + b*F(17), tj.
   problem F(18) se resava dva puta! Problemi manjih
   dimenzija ce se resavati jos veci broj puta. Resenje za ovaj
   problem je kombinacija rekurzije sa dinamickim programiranjem.
   Podproblemi se resavaju samo jednom, a njihova resenja se pamte u
   memoriji (obicno u nizovima ili matricama), odakle se koriste ako
   tokom resavanja ponovo budu potrebni.

   U narednoj funkciji vec izracunati clanovi niza se cuvaju u
   statickom nizu celih brojeva, jer se staticki niz ne smesta
   na stek, kao sto je to slucaj sa lokalnim promenljivama, vec na
   segment podataka, odakle je dostupan svim pozivima
   rekurzivne funkcije. */

/* c) Funkcija racuna n-ti broj niza F - napredna rekurzivna
   verzija */
int f_napredna(int n, int a, int b)
{
  /* Niz koji cuva resenja podproblema. Kompajler inicijalizuje
     staticke promenljive na podrazumevane vrednosti. Stoga, elemente 
     celobrojnog niza inicijalizuje na 0 */
  static int f[20];

  /* Ako je podproblem vec ranije resen, koristi se resenje koje je
     vec izracunato i */
  if (f[n] != 0)
    return f[n];

  /* Izlaz iz rekurzije */
  if (n == 0 || n == 1)
    return f[n] = n;

  /* Rekurzivni pozivi */
  return f[n] =
      a * f_napredna(n - 1, a, b) + b * f_napredna(n - 2, a, b);
}

int main()
{
  int n, a, b, ind;

  /* Unosi se redni broj funkcije koja ce se primeniti */
  printf("Unesite redni broj funkcije koju zelite:\n");
  printf("1 - iterativna\n");
  printf("2 - rekurzivna\n");
  printf("3 - rekurzivna napredna\n");
  scanf("%d", &ind);

  /* Ucitavaju se koeficijenti a i b */
  printf("Unesite koeficijente:\n");
  scanf("%d%d", &a, &b);

  /* Ucitava se broj n */
  printf("Unesite koji clan niza se racuna:\n");
  scanf("%d", &n);

  /* Na osnovu vrednosti promenljive ind ispisuje se rezultat poziva
     funkcije f_iterativna, f_rekurzivna ili f_napredna */
  if (ind == 0)
    printf("F(%d) = %d\n", n, f_iterativna(n, a, b));
  else if (ind == 1)
    printf("F(%d) = %d\n", n, f_rekurzivna(n, a, b));
  else
    printf("F(%d) = %d\n", n, f_napredna(n, a, b));

  return 0;
}
