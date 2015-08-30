#include <stdio.h>

/* Na primer za x cija binarna reprezentacija izgleda ovako
 * 10101011110011011110000100100011
 * 11000100100001111011001111010101
 */


unsigned mirror(unsigned x) {
    unsigned najnizi_bit;
    unsigned rezultat = 0;
    
    int i;
    /* Krecemo od najnizeg bita u zapisu broja x i dodajemo ga u rezultat */
    for(i =0; i < sizeof(x)*8; i++) {
        najnizi_bit = x & 1;
        x >>=1;
        /* Potiskujemo trenutni rezultat ka levom kraju tako svi prethodno postavljeni bitovi dobijaju vecu poziciju, a novi bit postavljamo na najnizu poziciju */
        rezultat <<= 1;
        rezultat |= najnizi_bit;
    }
    return rezultat;
}


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

int main() {
	int broj;
    scanf("%x", &broj);
	
	/*Ispisujemo binarnu reprezentaciju unetog broja*/
    print_bits(broj);   
    putchar('\n');
	/*Ispisujemo binarnu reprezentaciju broja dobijenog
      pozivom funkcije mirror	
	*/
    print_bits( mirror(broj));
    
    return 0;
}
