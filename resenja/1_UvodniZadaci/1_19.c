#include <stdio.h>
#include <stdlib.h>

/* Pomocna funkcija koja izracunava n! * rezultat. Koristi repnu
   rekurziju. rezultat je argument u kome se akumulira do tada
   izracunatu vrednost faktorijela. Kada dodje do izlaza iz
   rekurzije iz rekurzije potrebno je da vratimo rezultat. */
int faktorijel_repna(int n, int rezultat)
{
  if (n == 0)
    return rezultat;

  return faktorijel_repna(n - 1, n * rezultat);
}

/* U sledecim funkcijama je prikazan postupak oslobadjanja od repne
   rekurzije koja postoji u funkciji faktorijel_repna. */

/* Funkcija se transformise tako sto se rekurzivni poziv zemeni sa
   naredbama kojima se vrednost argumenta funkcije postavlja na
   vrednost koja bi se prosledjivala rekurzivnom pozivu i
   navodjenjem goto naredbe za vracanje na pocetak tela funkcije. */
int faktorijel_repna_v1(int n, int rezultat)
{
pocetak:
  if (n == 0)
    return rezultat;

  rezultat = n * rezultat;
  n = n - 1;
  goto pocetak;
}

/* Pisanje bezuslovnih skokova (goto naredbi) nije dobra
   programerska praksa i prethodna funkcija se koristi samo kao
   medjukorak. Sledi iterativno resenje bez bezuslovnih skokova */
int faktorijel_repna_v2(int n, int rezultat)
{
  while (n != 0) {
    rezultat = n * rezultat;
    n = n - 1;
  }

  return rezultat;
}

/* Prilikom poziva prethodnih funkcija pored prvog argumenta celog
   broja n, mora da se salje i 1 za vrednost drugog argumenta u
   kome ce se akumulirati rezultat. Funkcija faktorijel(n) je ovde
   radi udobnosti korisnika, jer je sasvim prirodno da za
   faktorijel zahteva samo 1 parametar. Funkcija faktorijel
   izracunava n!, tako sto odgovarajucoj gore navedenoj funkciji
   koja zaista racuna faktorijel, salje ispravne argumente i vraca
   rezultat koju joj ta funkcija vrati. Za testiranje, zameniti u
   telu funkcije faktorijel poziv faktorijel_repna sa pozivom
   faktorijel_repna_v1, a zatim sa pozivom funkcije
   faktorijel_repna_v2. */
int faktorijel(int n)
{
  return faktorijel_repna(n, 1);
}

int main()
{
  int n;

  /* Ucitava se ceo broj */
  printf("Unesite n (<= 12): ");
  scanf("%d", &n);
  if (n > 12) {
    fprintf(stderr, "Greska: Nedozvoljena vrednost za n.\n");
    exit(EXIT_FAILURE);
  }

  /* Ispisuje se rezultat poziva funkcije faktorijel */
  printf("%d! = %d\n", n, faktorijel(n));

  exit(EXIT_SUCCESS);
}
