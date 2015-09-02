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
    unsigned velicina = sizeof(int)*8; 		
    unsigned maska; 	

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