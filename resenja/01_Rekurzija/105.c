#include <stdio.h>
#include <stdlib.h>

/* Pomocna funkcija koja izracunava n! * result. Koristi repnu
   rekurziju. Result je argument u kome se akumulira do tada
   izracunatu vrednost faktorijela. Kada dodje do izlaza iz rekurzije 
   iz rekurzije potrebno je da vratimo result. */
int faktorijelRepna(int n, int result)
{
  if (n == 0)
    return result;

  return faktorijelRepna(n - 1, n * result);
}

/* U sledecim dvema funkcijama je prikazan postupak oslobadjanja od
   repne rekurzije koja postoji u funkciji faktorijelRepna.

   Funkcija se transformise tako sto rekurzivni poziv zemeni sa
   naredbama kojima se vrednost argumenta funkcije postavlja na
   vrednost koja bi se prosledjivala rekurzivnom pozivu i navodjenjem
   goto naredbe za vracanje na pocetak tela funkcije. */

int faktorijelRepna_v1(int n, int result)
{
pocetak:
  if (n == 0)
    return result;

  result = n * result;
  n = n - 1;
  goto pocetak;
}

/* Pisanje bezuslovnih skokova (goto naredbi) nije dobra programerska 
   praksa i prethodna funkcija se koristi samo kao medjukorak. Sledi
   iterativno resenje bez bezuslovnih skokova */
int faktorijelRepna_v2(int n, int result)
{
  while (n != 0) {
    result = n * result;
    n = n - 1;
  }

  return result;
}

/* Prilikom poziva prethodnih funkcija pored prvog argumenta celog
   broja n, mora da se salje i 1 za vrednost drugog argumenta u kome
   ce se akumulirati rezultat. Funkcija faktorijel(n) je ovde radi
   udobnosti korisnika, jer je sasvim prirodno da za faktorijel
   zahteva samo 1 parametar. Funkcija faktorijel izracunava n!, tako
   sto odgovarajucoj gore navedenoj funkciji koja zaista racuna
   faktorijel, salje ispravne argumente i vraca rezultat koju joj ta
   funkcija vrati. Za testiranje, zameniti u telu funkcije faktorijel
   poziv faktorijelRepna sa pozivom faktorijelRepna_v1, a zatim sa
   pozivom funkcije faktorijelRepna_v2. */
int faktorijel(int n)
{
  return faktorijelRepna(n, 1);
}

int main()
{
  int n;

  /* Ucitava se ceo broj */
  printf("Unesite n (<= 12): ");
  scanf("%d", &n);
  if (n > 12) {
    printf("Greska: nedozvoljena vrednost za n!\n");
    exit(EXIT_FAILURE);
  }

  /* Ispisuje se rezultat */
  printf("%d! = %d\n", n, faktorijel(n));

  exit(EXIT_SUCCESS);
}
