#include <stdio.h>

/***************************************************************
   Funkcija vraca vrednost cija je binarna reprezentacija slika
   u ogledalu binarne reprezentacije broja x koji se prosledjuje
   kao argument funkcije. Na primer za x
   cija binarna reprezentacija izgleda ovako
   101010111100110111100100100100011 
   funkcija treba da vrati broj cija binarna reprezentacija 
   izgleda:
   11000100100001111011001111010101 
***************************************************************/
unsigned mirror(unsigned x)
{
  unsigned najnizi_bit;
  unsigned rezultat = 0;

  int i;
  /* U svakoj iteraciji najnizi bit u binarnoj reprezentaciji tekuce vrednosti broja x se odredjuje i pamti u promenljivoj najnizi_bit, nakon cega se na promenljivu x primeni siftovanje u desno.*/
  for (i = 0; i < sizeof(x) * 8; i++) {
    najnizi_bit = x & 1;
    x >>= 1;
    /* Potiskivanjem trenutnog rezultata ka levom kraju svi
       prethodno postavljeni bitovi dobijaju vecu poziciju. Novi 
       bit se postavlja na najnizu poziciju */
    rezultat <<= 1;
    rezultat |= najnizi_bit;
  }
  return rezultat;
}


/* Funkcija prikazuje na standardni izlaz binarnu reprezentaciju 
   celog broja u memoriji */
void print_bits(int x)
{
  unsigned velicina = sizeof(int) * 8;
  unsigned maska;
  for (maska = 1 << (velicina - 1); maska != 0; maska >>= 1)
    putchar(x & maska ? '1' : '0');

  putchar('\n');
}

int main()
{
  int broj;
  scanf("%x", &broj);

  /* Ispisuje se binarna reprezentaciju unetog broja */
  print_bits(broj);

  /* Ispisuje se binarna reprezentaciju broja dobijenog pozivom
     funkcije mirror */
  print_bits(mirror(broj));

  return 0;
}
