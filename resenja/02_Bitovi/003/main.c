#include <stdio.h>
#include "polinom.h"

/*
Kako se za prevodjenje naSeg programa sada koriste 3
komande, da bi se ovaj proces kompilacije
automatizovao postoji make alat.
Potrebno je da u datoteci koja se zove makefile
popiSemo postupak kojim se od izvornih datoteka
dobija Zeljeni izvrSni program, a make alat Ce za nas
izvrSi naznaCene komande.
Detaljnije uputstvo o make alatu, gcc prevodiocu i joS
nekim korisnim alatima moZete nadji u skripti „GNU
alati“ Aleksandra SamardZiCa.
http://poincare.matf.bg.ac.rs/~asamardzic/gnu.pdf
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
    printf("Vrednost polimoma u tacki je %f\n", izracunaj(&p, x));

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
