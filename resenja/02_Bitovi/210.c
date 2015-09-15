#include <stdio.h>

/* 
   Niska koju formiramo je duzine (sizeof(unsigned int)*8)/4 +1
   jer za svaku heksadekadnu cifru nam trebaju 4 binarne cifre i
   jedna dodatna pozicija nam treba za terminirajucu nulu.

   Prethodni izraz je identican sa sizeof(unsigned int)*2+1.

   Na primer, ako je duzina unsigned int 4 bajta onda je
   MAX_DUZINA 9 */

#define MAX_DUZINA sizeof(unsigned int)*2 +1


void prevod(unsigned int x, char s[])
{

  int i;
  unsigned int maska;
  int vrednost;

  /* Heksadekadni zapis broja 15 je 000...0001111 - ovo nam
     odgovara ako hocemo da citamo 4 uzastopne cifre */
  maska = 15;

  /* 
     Broj cemo citati od pozicije najmanje tezine ka poziciji
     najvece tezine; npr. za broj
     00000000001101000100001111010101 u prvom koraku cemo
     procitati bitove: 0000000000110100010000111101<0101>
     (bitove izdvojene sa <...>) u drugom koraku cemo procitati: 
     000000000011010001000011<1101>0101 u trecem koraku cemo
     procitati: 00000000001101000100<0011>11010101 i tako redom

     indeks i oznacava poziciju na koju smestamo vrednost

   */
  for (i = MAX_DUZINA - 2; i >= 0; i--) {
    /* Vrednost izdvojene cifre */
    vrednost = x & maska;

    /* Ako je vrednost iz opsega od 0 do 9 odgovarajuci karakter 
       dobijamo dodavanjem ASCII koda '0' Ako je vrednost iz
       opsega od 10 do 15 odgovarajuci karakter dobijamo tako
       sto prvo oduzmemo 10 (dobijamo vrednosti od 0 do 5) pa
       dodamo ASCII kod 'A' (time dobijamo slova 'A', 'B', ...
       'F') */
    if (vrednost < 10) {
      s[i] = vrednost + '0';
    } else {
      s[i] = vrednost - 10 + 'A';
    }

    /* Broj pomeramo za 4 bita u desnu stranu tako da mozemo da
       procitamo sledecu cifru */
    x = x >> 4;
  }

  s[MAX_DUZINA - 1] = '\0';
}

int main()
{

  unsigned int x;
  char s[MAX_DUZINA];

  /* Ucitavamo broj */
  scanf("%u", &x);

  /* Pozivamo funkciju */
  prevod(x, s);

  /* Ispsujemo dobijenu nisku */
  printf("%s\n", s);

  return 0;
}
