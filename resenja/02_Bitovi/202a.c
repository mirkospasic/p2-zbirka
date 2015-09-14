#include <stdio.h>

/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju celog broja u memoriji */
void print_bits(int x)  { 
    unsigned velicina = sizeof(int)*8; 		
    unsigned maska; 	

    for( maska = 1 << (velicina -1); maska!=0 ; maska >>= 1)
        putchar( x & maska ? '1' : '0' );

    putchar('\n');
}

/* Funkcija vraca broj jedinica u binarnoj reprezentaciji broja x pomeranjem broja x*/
int count_bits(int x) {
    int br=0;
    unsigned wl = sizeof(unsigned)*8 -1;
        
    /* Formiramo masku 100000...0000000, koja sluzi za
        ocitavanje bita najvece tezine. U svakoj iteraciji
        maska se pomera u desno za 1 mesto, i ocitavamo sledeci
        bit. Petlja se zavrsava kada vise nema jedinica tj.
        kada maska postane nula. */
    unsigned maska= 1 << wl;      
    for( ;  maska!=0 ; maska>>=1 )
        x & maska ? br++ : 1;
    
    return br;
}


int main() {     
    int x;
	scanf("%x", &x);
    printf("Broj jedinica u zapisu je %d.\n", count_bits(x));
	
    return 0;
}
