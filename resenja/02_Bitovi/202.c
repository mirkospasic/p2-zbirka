#include <stdio.h>

/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju celog broja u memoriji */
void print_bits( int x)  { 
    unsigned velicina = sizeof(int)*8; 		/* broj bitova celog broja */
    unsigned maska; 	/* maska koju cemo koristiti za "ocitavanje" bitova */
    
    /* Bitove u zapisu broja treba da ispisujemo sa leva na desno, tj. od bita najvece tezine ka 
     * bitu najmanje tezine. Iz tog razloga, za pocetnu vrednost maske uzimamo vrednost 
     * ciji binarni zapis je takav da je bit najvece tezine 1, a svi ostali nule. 
     * Nakon toga, u svakoj iteraciji cemo tu jedinicu pomerati u desno, kako bismo ocitali 
     * naredni bit, gledano s leva na desno. Odgovarajuci karakter, ('0' ili '1'), ispisuje se na ekranu. 
     *
     * Zbog siftovanja maske u desno koja na pocetku ima najvisi bit postavljen na 1, 
     * neophodno je da maska bude neoznacen ceo broj i da se siftovanjem u desno ova 1 
     * ne bi smatrala znakom i prepisivala, vec da bi nam se svakim siftovanjem  sa levog kraja
     * binarnog zapisa pojavljivale 0. */

    for( maska = 1 << (velicina -1); maska!=0 ; maska >>= 1)
        putchar( x & maska ? '1' : '0' );

    putchar('\n');
}

/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x pomeranjem broja maske */
int count_bits(int x) {
    int br=0;
    unsigned maska = 1;

    for( ; maska!=0; maska <<=1 )
        if(x&maska) 
            br++;

    return br;
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
    print_bits(0xABCDE123);
    printf("Broj bitova u zapisu je %d.\n", count_bits(0xABCDE123));
	/*
    printf("Broj bitova u zapisu je %d.\n", count_bits1(0xABCDE123));
	*/
	
    return 0;
}