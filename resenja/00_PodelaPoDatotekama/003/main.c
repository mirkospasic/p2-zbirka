#include <stdio.h>
#include "polinom.h"

/*
Prevodjenje:
gcc -o test-polinom polinom.c main.c

ili:
gcc -c polinom.c 
gcc -c main.c
gcc -o test-polinom polinom.o main.o
*/

int main(int argc, char **argv)
{
    Polinom p, q, r;
    double x;
    int n;

    /* Unos polinoma */
    printf
    ("Unesite polinom (prvo stepen, pa zatim koeficijente od najveceg stepena do nultog):\n");
    p = ucitaj();

    /* Ispis polinoma */
    ispisi(&p);

    printf("Unesite tacku u kojoj racunate vrednost polinoma\n");
    scanf("%lf", &x);

    /* Ispisujemo vrednost polinoma u toj tacki */
    printf("Vrednost polinoma u tacki je %.2f\n", izracunaj(&p, x));

    /* Unesimo drugi polinom */
    printf
	("Unesite drugi polinom (prvo stepen, pa zatim koeficijente od najveceg stepena do nultog):\n");
    q = ucitaj();

    /* Sabiramno polinome i ispisujemo zbir ta dva polinoma */
    r = saberi(&p, &q);
    printf("Zbir polinoma je: ");
    ispisi(&r);

    /* Mnozimo polinome i ispisujemo prozivod ta dva polinoma */
    r = pomnozi(&p, &q);
    printf("Prozvod polinoma je: ");
    ispisi(&r);

    /* Izvod polinoma */
    printf("Unesite izvod polinoma koji zelite:\n");
    scanf("%d", &n);
    r = nIzvod(&p, n);
    printf("%d. izvod prvog polinoma je: ", n);
    ispisi(&r);

    /* Uspesno zavrsavamo program */
    return 0;
}
