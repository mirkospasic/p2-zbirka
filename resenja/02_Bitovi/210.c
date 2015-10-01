#include <stdio.h>

/* 
   Niska koja se formiramo je duzine (sizeof(unsigned int)*8)/4 +1
   jer su za svaku heksadekadnu cifru potrebne 4 binarne cifre i
   jedna dodatna pozicija za terminirajucu nulu.

   Prethodni izraz je identican sa sizeof(unsigned int)*2+1. */

#define MAX_DUZINA sizeof(unsigned int)*2 +1


void prevod(unsigned int x, char s[])
{

  int i;
  unsigned int maska;
  int vrednost;

  /* Heksadekadni zapis broja 15 je 000...0001111 - odgovarajuca
     maska za citanje 4 uzastopne cifre */
  maska = 15;

  /************************************************************* 
     Broj se posmatra od pozicije najmanje tezine ka poziciji
     najvece tezine. Na primer za broj
     00000000001101000100001111010101 
     u prvom koraku se citaju bitovi izdvojeni sa <...>: 
     0000000000110100010000111101<0101>
     u drugom koraku: 
     000000000011010001000011<1101>0101 
     u trecem koraku:
     00000000001101000100<0011>11010101 i tako redom

     Indeks i oznacava poziciju na koju se smesta vrednost.

   */
  for (i = MAX_DUZINA - 2; i >= 0; i--) {
    /* Vrednost izdvojene cifre */
    vrednost = x & maska;

    /* Ako je vrednost iz opsega od 0 do 9 odgovarajuci karakter se
       dobija dodavanjem ASCII koda '0'. Ako je vrednost iz opsega od 
       10 do 15 odgovarajuci karakter se dobija tako sto se prvo
       oduzme 10 (time se dobiju vrednosti od 0 do 5) pa se na tako
       dobijenu vrednost doda ASCII kod 'A' (time se dobija
       odgovarajuce slovo 'A', 'B', ... 'F') */
    if (vrednost < 10) {
      s[i] = vrednost + '0';
    } else {
      s[i] = vrednost - 10 + 'A';
    }

    /* Primenljiva x se pomera za 4 bita u desnu stranu i time ce u
       narednoj iteraciji biti posmatrane sledece 4 cifre */
    x = x >> 4;
  }

  s[MAX_DUZINA - 1] = '\0';
}

int main()
{

  unsigned int x;
  char s[MAX_DUZINA];

  scanf("%u", &x);

  prevod(x, s);

  printf("%s\n", s);

  return 0;
}
