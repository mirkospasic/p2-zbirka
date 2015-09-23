#include <stdio.h>

int broj_parova(unsigned int x)
{

  int broj_parova;
  unsigned int maska;

  /* Vrednost promenljive koja predstavlja broj parova se inicijalizuje na 0 */
  broj_parova = 0;

  /* Postavlja se maska tako da moze da procitamo da li su dva
     najmanja bita u zapisu broja x 11 */
  /* Binarna reprezentacija broja 3 je 000....00011 */
  maska = 3;

  while (x != 0) {

    /* Provera da li se na najmanjim pozicijama broj x
       nalazi 11 par */
    if ((x & maska) == maska) {
      broj_parova++;
    }

    /* Pomera se broj u desnu stranu da bi se u narednoj iteraciji proveravao sledeci par bitova. Pomeranjem u desno 
       bit najvece tezine se popunjava nulom jer je x
       neoznacen broj. */
    x = x >> 1;
  }

  return broj_parova;

}

int main()
{
  unsigned int x;

  scanf("%u", &x);

  printf("%d\n", broj_parova(x));

  return 0;
}
