#include <stdio.h>
#include "polinom.h"

/*
Prevodjenje:
gcc -o test-polinom polinom.c test-polinom.c

ili:
gcc -c polinom.c 
gcc -c test-polinom.c
gcc -o test-polinom polinom.o test-polinom.o
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

    /* Unos tacke u kojoj se racuna vrednost polinoma */
    printf("\nUnesite tacku u kojoj racunate vrednost polinoma\n");
    scanf("%lf", &x);

    /* Ispisujemo vrednost polinoma u toj tacki */
    printf("Vrednost polimoma u tacki je %.2f\n", izracunaj(&p, x));

    /* Unesimo drugi polinom */
    printf
	("\nUnesite drugi polinom (prvo stepen, pa zatim koeficijente od najveceg stepena do nultog):\n");
    q = ucitaj();

    /* Sabiramno polinome i ispisujemo zbir ta dva polinoma */
    r = saberi(&p, &q);
    printf("Zbir polinoma ");
    ispisi(&p);
    printf("i polinoma ");
    ispisi(&q);
    printf("je : ");
    ispisi(&r);

    /* Mnozimo polinome i ispisujemo prozivod ta dva polinoma */
    r = pomnozi(&p, &q);
    printf("\nProzvod polinoma ");
    ispisi(&p);
    printf("i polinoma ");
    ispisi(&q);
    printf("je : ");
    ispisi(&r);

    /* Izvod polinoma */
    printf("\nUnosite izvod polinoma koji zelite: ");
    scanf("%d", &n);
    r = nIzvod(&p, n);
    printf("%d. izvod polinoma ", n);
    ispisi(&p);
    printf("je : ");
    ispisi(&r);

    /* Uspesno zavrsavamo program */
    return 0;
}
