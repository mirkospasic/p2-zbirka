#include <stdio.h>
    /* Repno-rekurzivna (eng. tail recursive) je ona funkcija
       Cije se telo zavrsava rekurzivnim pozivom, pri cemu taj
       rekurzivni poziv ne ucestvuje u nekom izrazu.

       Kod ovih funkcija se po zavrsetku za tekuci rekurzivni
       poziv umesto skoka na adresu povratka skace na adresu
       povratka za prethodni poziv, odnosno za poziv na manjoj
       dubini. Time se stedi i prostor i vreme.

       Ovakve funkcije se mogu lako zameniti odgovarajucom
       iterativnom funkcijom, cime se smanjuje prostorna
       slozenost algoritma. */
    /* PomoCna funkcija koja izracunava n! * result. Koristi
       repnu rekurziju. */
    /* Result je argument u kom cemo akumulirati do tada
       izracunatu vrednost faktorijela. Kada zavrsimo, tj. kada
       dodjemo do izlaza iz rekurzije potrebno je da vratimo
       result. */
int faktorijelRepna(int n, int result)
{
  if (n == 0)
    return result;

  return faktorijelRepna(n - 1, n * result);
}

/* Sada zelimo da se oslobodimo repne rekurzije koja postoji u
   funkciji faktorijelRepna, koristeci algoritam sa predavanja.

   Najpre cemo vrednost argumenta funkcije postaviti na vrednost 
   koja bi se prosledjivala rekurzivnom pozivu i pomocu goto
   naredbe vratiti se na pocetak tela funkcije. */

int faktorijelRepna_v1(int n, int result)
{
pocetak:
  if (n == 0)
    return result;

  result = n * result;
  n = n - 1;
  goto pocetak;
}

/* Pisanje bezuslovnih skokova (goto naredbi) nije dobra
   programerska praksa. Iskoristicemo prethodni medjukorak da
   bismo dobili iterativno resenje bez bezuslovnih skokova. */
int faktorijelRepna_v2(int n, int result)
{
  while (n != 0) {
    result = n * result;
    n = n - 1;
  }

  return result;
}

/* Nasim gore navedenim funkcijama pored n, mora da se salje i 1 
   za vrednost drugog argumenta u kome ce se akumulirati
   rezultat. Funkcija faktorijel(n) je ovde radi udobnosti
   korisnika, jer je sasvim prirodno da za faktorijel zahteva
   samo 1 parametar. Funkcija faktorijel izracunava n!, tako Sto 
   odgovarajucoj gore navedenoj funkciji koja zaista racuna
   faktorijel, salje ispravne argumente i vraca rezultat koju
   joj ta funkcija vrati. Za testiranje, zameniti u telu
   funkcije faktorijel poziv faktorijelRepna sa pozivom
   faktorijelRepna_v1, a zatim sa pozivom funkcije
   faktorijelRepna_v2. */
int faktorijel(int n)
{
  return faktorijelRepna(n, 1);
}

/* Test program */
int main()
{
  int n;

  printf("Unesite n (<= 12): ");
  scanf("%d", &n);
  printf("%d! = %d\n", n, faktorijel(n));

  return 0;
}
