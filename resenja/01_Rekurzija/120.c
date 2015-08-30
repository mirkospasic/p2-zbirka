#include<stdio.h>


/* Rekurzivna funkcija za odredjivanje najvece oktalne cifre u broju */
int max_oktalna_cifra(unsigned x) {
    /* Izlazak iz rekurzije */
    if(x==0) return 0;
    /* Odredjivanje poslednje oktalne cifre u broju*/
    int poslednja_cifra = x&7;
    /* Odredjivanje maksimalne oktalne cifre broja kada se iz njega izbrise poslednja oktalna cifra*/
    int max_bez_poslednje_cifre = max_oktalna_cifra(x>>3);
    return poslednja_cifra > max_bez_poslednje_cifre ? poslednja_cifra : max_bez_poslednje_cifre;
}



int main()
{
  unsigned x;
  scanf("%u", &x);
  printf("%d\n", max_oktalna_cifra(x));  
  return 0;
}
