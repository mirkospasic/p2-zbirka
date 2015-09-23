#include <stdio.h>

/***************************************************************
   Funkcija binarnu reprezentaciju svog argumenta x rotira u 
   levo za n mesta i vraca odgovarajuci neoznacen ceo broj cija
   je binarna reprezentacija dobijena nakon rotacije.
   Na primer za n =5 i x cija je interna reprezentacija 
   1010 1011 1100 1101 1110 0001 0010 0011 
   funkcija vraca neoznacen ceo broj cija je binarna 
   reprezentacija:
   0111 1001 1011 1100 0010 0100 0111 0101 
***************************************************************/
unsigned rotate_left(int x, unsigned n)
{
  unsigned first_bit;
  /* Maska koja ima samo najvisi bit postavljen na 1 neophodna
     da bi pre siftovanja u levo za 1 najvisi bit bio sacuvan.*/
  unsigned first_bit_mask = 1 << (sizeof(unsigned) * 8 - 1);
  int i;

  /* n puta se vrsi rotaciju za jedan bit u levo. U svakoj
     iteraciji se odredi prvi bit, a potom se pomera binarna reprezentacija trenutne vrednosti promenljive
     x u levo za 1. Nakon toga, potom najnizi bit se postavlja na vrednost
     koju je imao prvi bit koji je istisnut siftovanjem */
  for (i = 0; i < n; i++) {
    first_bit = x & first_bit_mask;
    x = x << 1 | first_bit >> (sizeof(unsigned) * 8 - 1);
  }
  return x;
}

/***************************************************************
   Funkcija neoznacen broj x rotira u desno za n.
   Na primer za n=5 i x cija je binarna reprezentacija 
   1010 1011 1100 1101 1110 0001 0010 0011 
   funkcija vraca neoznacen ceo broj cija je binarna 
   reprezentacija:
   0001 1101 0101 1110 0110 1111 0000 1001 
***************************************************************/
unsigned rotate_right(unsigned x, unsigned n)
{
  unsigned last_bit;
  int i;

  /* n puta se ponavlja rotacija u desno za jedan bit. U svakoj
     iteraciji se odredjuje bit najmanje tezine broja x, zatm
     tako odredjeni bit se siftuje u levo tako da najnizi bit
     dode do pozicije najviseg bita. Zatim, nakon siftovanja binarne reprezentacije trenutne vrednosti promenljive x za 1 u
     desno, najvisi bit se postaljva na vrednost vec zapamcenog bita koji je bio na poziciji najmanje tezine. */
  for (i = 0; i < n; i++) {
    last_bit = x & 1;
    x = x >> 1 | last_bit << (sizeof(unsigned) * 8 - 1);
  }

  return x;
}

/* Verzija funkcije koja broj x rotira u desno za n mesta, gde
   je argument funkcije x oznaceni ceo broj */
int rotate_right_signed(int x, unsigned n)
{
  unsigned last_bit;
  int i;


  /* U svakoj iteraciji se odredjuje bit najmanje tezine i smesta u promenljivu
     last_bit. Kako je x oznacen ceo broj, tada se prilikom
     siftovanja u desno vrsi aritmeticki sift i cuva se znak
     broja. Dakle, razlikuju se dva slucaja u zavisnosti od
     znaka od x. Nije dovoljno da se ova provera izvrsi pre
     petlje, s obzirom da rotiranjem u desno na mesto najviseg bita moze
     doci i 0 i 1, nezavisno od pocetnog znaka broja smestenog u promenljivu x. */
  for (i = 0; i < n; i++) {
    last_bit = x & 1;

    if (x < 0)
/*************************************************************** 
         Siftovanjem u desno broja koji je negativan dobija se 1
         kao bit na najvisoj poziciji.  Na primer ako je x 
         1010 1011 1100 1101 1110 0001 0010 001b 
         (sa b je oznacen ili 1 ili 0 na najnizoj poziciji) 
         Onda je sadrzaj promenljive last_bit:
         0000 0000 0000 0000 0000 0000 0000 000b 
         Nakon siftovanja sadrzaja promenljive x za 1 u desno 
         1101 0101 1110 0110 1111 0000 1001 0001 
         Kako bi umesto 1 na najvisoj poziciji u trenutnoj 
         binarnoj reprezentaciji x bilo postavljeno b nije 
         dovoljno da se siftuje na najvisu poziciju jer bi se 
         time dobile 0, a u ovom slucaju su potrebne jedinice
         zbog bitovskog & zato se prvo vrsi komplementiranje, a
         zatim siftovanje
         ~last_bit << (sizeof(int)*8 -1) 
         B000 0000 0000 0000 0000 0000 0000 0000 
         gde B oznacava ~b.
         Potom se ponovo vrsi komplementiranje kako bi se b
         nalazilo na najvisoj poziciji i sve jedinice na ostalim
         pozicijama 
         ~(~last_bit << (sizeof(int)*8 -1)) 
         b111 1111 1111 1111 1111 1111 1111 1111 
***************************************************************/
      x = (x >> 1) & ~(~last_bit << (sizeof(int) * 8 - 1));
    else
      x = (x >> 1) | last_bit << (sizeof(int) * 8 - 1);
  }

  return x;
}


/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju 
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
  unsigned x, k;
  scanf("%x%x", &x, &k);
  printf("x %36s = ", "");
  print_bits(x);
  printf("rotate_left(%7u,%6u)%8s = ", x, k, "");
  print_bits(rotate_left(x, k));

  printf("rotate_right(%7u,%6u)%7s = ", x, k, "");
  print_bits(rotate_right(x, k));

  printf("rotate_right_signed(%7u,%6u) = ", x, k);
  print_bits(rotate_right_signed(x, k));

  return 0;
}
