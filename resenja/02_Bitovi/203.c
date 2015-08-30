#include <stdio.h>

/* Funkcija vraca najveci neoznaceni broj sastavljen iz istih
   bitova kao i x  */
unsigned najveci(unsigned x) {
    unsigned velicina = sizeof(unsigned)*8;
    
    /* Formiramo masku 100000...0000000 */
    unsigned maska = 1 << (velicina-1);
    
    /* Inicijalizujemo rezultat na 0 */
    unsigned rezultat = 0;

    /* Dokle god postoje jedinice u binarnoj reprezentaciji broja x (tj. dokle god je x razlicit od nule) pomeramo ga ulevo. */
    for( ; x!=0; x<<=1 ) {
        /* Za svaku jedinicu, potiskujemo jednu 
         *	   novu jedinicu sa leva u rezultat */
        if( x & maska) {
            rezultat >>= 1;
            rezultat |= maska;
        }
    }
    
    return rezultat;
}

/* Funkcija vraca najmanji neoznacen broj 
   sa istim binarnim ciframa kao i x */
unsigned najmanji(unsigned x)  {
    /* Inicijalizujemo rezultat na 0 */
    unsigned rezultat =0;
   
    /* Dokle god imamo jedinice u broju x, pomeramo ga udesno. */
    for( ;x!=0 ; x>>=1){
        /* Za svaku jedinicu, potiskujemo jednu novu jedinicu sa desna u rezultat */
        if( x& 1) { 
            rezultat <<=1;
            rezultat |= 1;           
        }
    }
    
    return rezultat;
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

int main()  {
	int broj;
    scanf("%x", &broj);

	printf("Najveci:\n");
	print_bits( najveci(broj) );
	
	printf("Najmanji:\n");
	print_bits( najmanji(broj) );
	
    return 0;
}