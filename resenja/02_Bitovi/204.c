#include <stdio.h>

/* Funckija postavlja na nulu n bitova pocev od pozicije p. 
 * Pozicije se broje pocev od pozicije najnizeg bita, 
 * pri cemu se broji od nule .
 * Npr, za n=5,  p=10
 *     1010 1011 1100 1101 1110 1010 1110 0111
 *     1010 1011 1100 1101 1110 1000 0010 0111
 */
unsigned reset(unsigned x, unsigned n, unsigned p ) {
    /* Cilj nam je da samo zeljene bitove anuliramo, a da ostali ostanu nepromenjeni.
     * Formiramo masku koja ima n bitova postavljenih na 0 pocev od pozicije p, 
     * dok su svi ostali postavljeni na 1.
     * 
     * Na primer, za n=5 i p=10 
     * formiramo masku oblika 
     * 1111 1111 1111 1111 1111 1000 0011 1111
     * To postizemo na sledeci nacin:
     * ~0                       1111 1111 1111 1111 1111 1111 1111 1111 
     * (~0 << n)           1111 1111 1111 1111 1111 1111 1110 0000
     * ~(~0 << n)         0000 0000 0000 0000 0000 0000 0001 1111
     * (~(~0 << n) << ( p-n+1))             0000 0000 0000 0000 0000 0111 1100 0000
     * ~(~(~0 << n) << ( p-n+1))          1111 1111 1111 1111 1111 1000 0011 1111
     */
    unsigned maska =  ~(~(~0 << n) << ( p-n+1));

    return x & maska;
} 

/* Funckija postavlja na 1 n bitova pocev od pozicije p. 
 * Pozicije se broje pocev od pozicije najnizeg bita, 
 * pri cemu se broji od nule .
 * Npr, za n=5,  p=10
 *     1010 1011 1100 1101 1110 1010 1110 0111
 *     1010 1011 1100 1101 1110 1111 1110 0111
 */
unsigned set(unsigned x, unsigned n, unsigned p ) {
    /* Kako zelimo da samo odredjenih n bitova postavimo na 1, dok ostali treba da ostanu netaknuti.
     * Na primer, za n=5 i p=10
     * formiramo masku oblika  0000 0000 0000 0000 0000 0111 1100 0000
     * prateci vrlo slican postupak kao za prethodnu funkciju
     */
    unsigned maska = ~(~0 << n) << (p-n+1);

    return x|maska;
}

/* Funkcija vraca celobrojno polje bitova, desno poravnato, koje predstavlja n bitova 
 * pocev od pozicije p u binarnoj reprezentaciji broja x, pri cemu se pozicija broji 
 * sa desna ulevo, gde je pocetna pozicija 0.
 * Na primer za n = 5 i p = 10 i broj
 *    1010 1011 1100 1101 1110 1010 1110 0111
 *    0000 0000 0000 0000 0000 0000 0000 1011
 */
unsigned get_bits(unsigned x, unsigned n, unsigned p ) {
    /* Kreiramo masku kod kod koje su poslednjih n bitova 1, a ostali su 0.
     * Na primer za n=5
     * 0000 0000 0000 0000 0000 0000 0001 1111
     */
    unsigned maska = ~(~0 << n);
    
    /* Pomeramo sadrzaj u desno tako da trazeno polje bude uz desni kraj.
     * Zatim maskiramo ostale bitove, sem zeljenih n i vracamo vrednost */
    return maska & ( x >> (p-n+1));
}


/* Funkcija vraca broj x kome su n bitova pocev od pozicije p postavljeni na
   vrednosti n bitova najnize tezine binarne reprezentacije broja y */
unsigned set_n_bits(unsigned x, unsigned n, unsigned p , unsigned y) {
     /* Kreiramo masku kod kod koje su poslednjih n bitova 1, a ostali su 0.
     * Na primer za n=5
     * 0000 0000 0000 0000 0000 0000 0001 1111
     */
    unsigned last_n_1 = ~(~0 << n);
    
    /* Kao ranije u funkciji reset, kreiramo masku koja ima n bitova postavljenih 
     * na 0 pocevsi od pozicije p, dok su ostali bitovi 1.
     * Na primer za n=5 i p =10 
     * 1111 1111 1111 1111 1111 1000 0011 1111
     */
    unsigned middle_n_0 = ~(~(~0 << n ) << (p-n+1));
    
    /* x sa resetovanih n bita na pozicijama pocev od p */
    unsigned x_reset = x & middle_n_0;
    
    /* y cijih je n bitova najnize tezine pomereno tako da stoje 
     * pocev od pozicije p. Ostali bitovi su nule.
     *  (y & last_n_1)  resetuje sve bitove osim najnizih n
     */
    unsigned y_shift_middle= (y & last_n_1) << (p-n+1);
    
    return x_reset ^ y_shift_middle;
}


/* Funkcija invertuje bitove u zapisu broja x pocevsi od pozicije p njih n*/
unsigned invert(unsigned x, unsigned n, unsigned p )
{	
	/* Formiramo masku sa n jedinica pocev od pozicije p
     * Na primer za n=5 i p=10
     * 0000 0000 0000 0000 0000 0111 1100 0000
     */
	unsigned maska = ~(~0 << n) << (p-n+1);

	/* Operator ekskluzivno ili invertuje sve bitove gde je odgovarajuci 
       bit maske 1. Ostali bitovi ostaju nepromenjeni. */
	return maska ^ x;
}


/* Funkcija prikazuje na standardni ekran binarnu reprezentaciju celog broja u memoriji */
void print_bits( int x)  { 
    unsigned velicina = sizeof(int)*8; 		/* Broj bitova celog broja */
    unsigned maska; 	/* Maska koju cemo koristiti za "ocitavanje" bitova */
    
    /* Bitove u zapisu broja treba da ispisujemo sa leva na desno, tj. od bita najvece tezine ka 
     * bitu najmanje tezine. Iz tog razloga, za pocetnu vrednost maske uzimamo vrednost 
     * ciji binarni zapis je takav da je bit najvece tezine 1, a svi ostali nule. 
     * Nakon toga, u svakoj iteraciji cemo tu jedinicu pomerati u desno, kako bismo ocitali 
     * naredni bit, gledano s leva na desno. Odgovarajuci karakter, ('0' ili '1'), ispisuje se na ekranu. 
     *
     * Zbog siftovanja maske u desno koja na pocetku ima najvisi bit postavljen na 1, 
     * neophodno je da maska bude neoznacen ceo broj i da se Siftovanjem u desno ova 1 
     * ne bi smatrala znakom i prepisivala, vec da bi nam se svakim Siftovanjem  sa levog kraja
     * binarnog zapisa pojavljivale 0. */

    for( maska = 1 << (velicina -1); maska!=0 ; maska >>= 1)
        putchar( x & maska ? '1' : '0' );

    putchar('\n');
}



int main() {
    unsigned broj, p, n, y;
    scanf("%u%u%u%u", &broj, &n, &p, &y);
    printf("Broj %5u %25s= ", broj, "");
    print_bits(broj);
       
  
    printf("reset(%5u,%5u,%5u)%11s = ", broj, n, p, "");
    print_bits( reset(broj, n, p));
   
	printf("set(%5u,%5u,%5u)%13s = ", broj, n, p, "");
    print_bits( set(broj, n, p));
   
    printf("get_bits(%5u,%5u,%5u)%8s = ", broj, n, p, "");
    print_bits( get_bits(broj, n, p));
   
    printf("y = %31u = ", y);
    print_bits(y);
    printf("set_n_bits(%5u,%5u,%5u,%5u) = ", broj, n, p, y);
    print_bits( set_n_bits(broj, n, p, y));
  
    printf("invert(%5u,%5u,%5u)%10s = ", broj, n, p, "");
    print_bits( invert(broj, n, p));
  
	return 0;
}
