#include <stdio.h>

int zbir_cifara(unsigned int x)
{
    /* Izlazak iz rekurzije: ako je broj jednocifren */
    if(x<10) return x;
    
    /* Zbir cifara broja jednak je zbiru svih njegovih cifara osim poslednje cifre + poslednja cifra tog broja */
    return zbir_cifara(x/10) + x%10;
}


int main() 
{
    unsigned int x;
    
    /* Ucitava se ceo broj sa ulaza */
    scanf("%u",&x);
    
    /* Ispisuje se zbir cifara broja ucitanog broja */
    printf("%d\n", zbir_cifara(x));
    
    return 0;
}
