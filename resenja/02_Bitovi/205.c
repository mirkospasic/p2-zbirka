#include <stdio.h>

/* Funkcija broj x rotira u levo za n mesta
 * Na primer za n =5 i x cija je interna reprezentacija
 * 1010 1011 1100 1101 1110 0001 0010 0011
 * 0111 1001 1011 1100 0010 0100 0111 0101
 */
unsigned rotate_left(int x, unsigned n) {
    unsigned first_bit;
    /* Maska koja ima samo najvisi bit postavljen na 1 neophodna da bismo pre siftovanja u levo za 1 sacuvali najvisi bit. */
    unsigned first_bit_mask = 1 << (sizeof(unsigned)*8 -1);
    int i;
    
    /* n puta vrsimo rotaciju za jedan bit u levo */
    for( i= 0; i<n; i++) {
        /* odredujemo prvi bit*/
        first_bit =  x & first_bit_mask;
        /* pomeramo sadrzaj broja x u levo za 1, a
         * potom najnizi bit postavljamo na vrednost koju je imao 
         * prvi bit koji smo istisnuli Siftovanjem */
        x = x<< 1 | first_bit >> (sizeof(unsigned)*8-1);
    }    
    return x;
}

/* Funkcija neoznacen broj x rotira u desno za n 
 * Na primer za n =5 i x cija je interna reprezentacija
 * 1010 1011 1100 1101 1110 0001 0010 0011
 * 0001 1101 0101 1110 0110 1111 0000 1001
 */
unsigned  rotate_right(unsigned x, unsigned n) {
    unsigned last_bit;
    int i;
    
    /* n puta ponavljamo rotaciju u desno za jedan bit */
    for(i=0; i<n; i++){
        last_bit = x & 1 ;	/* bit najmanje tezine */
        
        /* last_bit siftujemo u levo tako da najnizi bit dode do pozicije najviseg bita  i
         * nakon Siftovanja x za 1 u desno postavljamo x-ov najvisi bit na vrednost
         * najnizeg bita.
         */
        x = x >> 1 | last_bit << (sizeof(unsigned)*8-1);
    }

    return x;
}

/* Verzija funkcije koja broj x rotira u desno za n mesta, gde je x oznaceni broj */
int rotate_right_signed(int x, unsigned n) {
    unsigned last_bit;
    int i;

    for(i=0; i<n; i++) {
        last_bit = x & 1;	/* bit najmanje tezine */
        
        /* Kako je x oznacen ceo broj, tada se prilikom Siftovanja u desno 
         * vrsi aritmeticki sift i cuva se znak broja. Iza tog razloga imamo dva
         * slucaja u zavisnosti od znaka od x. 
         * Nije dovoljno da se ova provera izvrsi pre petlje, jer rotiranjem u desno
         * na mesto najviseg bita moze doci i 0 i 1, nezavisno od pocetnog znaka x.
         */
        if( x<0 )
            /* Siftovanjem u desno broja koji je negativan dobijamo 1 na najvisoj 
             * poziciji.  Na primer ako je x 
             * 1010 1011 1100 1101 1110 0001 0010 001b
             * (sa b oznacavamo u primeru 1 ili 0 na najnizoj poziciji)
             * 
             * last_bit je 
             * 0000 0000 0000 0000 0000 0000 0000 000b 
             * nakon Siftovanja za 1 u desno
             * 1101 0101 1110 0110 1111 0000 1001 0001
             * 
             * da bismo najvisu 1 u x postavili na b nije dovoljno da ga siftujemo 
             * na najvisu poziciju jer bi se time dobile 0, a nama su potrebne 1 
             * zbog bitovskog &
             * zato prvo komplementiramo, pa tek onda siftujemo 
             * ~last_bit << (sizeof(int)*8 -1)  
             * B000 0000 0000 0000 0000 0000 0000 0000
             * (B oznacava ~b )
             * i ponovo komplementiramo da bismo imali b na najvisoj poziciji 
             * i sve 1 na ostalim pozicijama
             * ~(~last_bit << (sizeof(int)*8 -1))
             * b111 1111 1111 1111 1111 1111 1111 1111
             */
            x = (x >>1) & ~(~last_bit << (sizeof(int)*8 -1));
        else 
            x = (x >>1) | last_bit<< (sizeof(int)*8 -1);
    }

    return x;
}


/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju celog broja u memoriji */
void print_bits( int x)  { 
    unsigned velicina = sizeof(int)*8; 		/* Broj bitova celog broja */
    unsigned maska; 	/* Maska koju cemo koristiti za "ocitavanje" bitova */
    
    /* Bitove u zapisu broja treba da ispisujemo sa leva na desno, tj od bita najvece tezine ka 
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
	unsigned x, k;
    scanf("%x%x", &x, &k);
    printf("x %36s = ", "");
    print_bits(x);
    printf("rotate_left(%7u,%6u)%8s = ", x, k, "");
    print_bits( rotate_left(x, k));
    
    printf("rotate_right(%7u,%6u)%7s = ", x, k, "");
    print_bits( rotate_right(x, k));
    
    printf("rotate_right_signed(%7u,%6u) = ", x, k);
    print_bits( rotate_right_signed(x, k));
    
    return 0;
}

