#include <stdio.h>

/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju celog broja u memoriji */
void print_bits( int x)  { 
    unsigned velicina = sizeof(int)*8; 		
    unsigned maska; 	

    for( maska = 1 << (velicina -1); maska!=0 ; maska >>= 1)
        putchar( x & maska ? '1' : '0' );

    putchar('\n');
}

/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x pomeranjem broja x*/
int count_bits1(int x) {
    int br=0;
    unsigned wl = sizeof(int)*8 -1;
    unsigned maska= 1 << wl; 
     
    /*  Kako je argument funkcije oznacen ceo broj x ne mozemo da siftujemo x u desno.
        naredba x>>=1 vrsila bi aritmeticki sift u desno, tj. bitove
        sa desne strane bi bili popunjavani bitom znaka.
        Npr. -3 bit znaka je 1. U tom slucaju nikad nece biti
        ispunjen uslov x!=0 i program ce biti zarobljen u
        beskonacnoj petlji.
    */
    
    /* Formiramo masku 100000...0000000,koja sluzi za
        ocitavanje bita najvece tezine. U svakoj iteraciji
        x se pomera u levo za 1 mesto, i ocitavamo sledeci
        bit. Petlja se zavrsava kada vise nema jedinica tj.
        kada x postane nula. */
    for( ;  x!=0 ; x<<=1 )
        x & maska ? br++ : 1;
    
    return br;
}


int main() { 
    
    int x;
	scanf("%x", &x);
    printf("Broj bitova u zapisu je %d.\n", count_bits(x));
	
    return 0;
}