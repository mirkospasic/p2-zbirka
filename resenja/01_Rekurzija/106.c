#include <stdio.h>
#include <stdlib.h>

/* Funkcija izracunava n-ti element u nizu F */
int F_rekurzivna(int n, int a, int b)
{
  /* Izlaz iz rekurzije */
  if(n ==0 || n==1)
    return n;

  /* Rekurzivni pozivi */
  return a* F_rekurzivna(n - 1, a, b) + b* F_rekurzivna(n - 2, a, b);
}

/*  NAPOMENA: U slucaju da se rekurzijom problem svodi na vise manjih 
 *  podproblema koji se mogu preklapati, postoji opasnost da se 
 *  pojedini podproblemi manjih dimenzija resavaju veci broj puta. 
 *  Npr. F(20) = a*F(19) + b*F(18), a F(19) = a*F(18) + b*F(17), 
 *  tj. problem fibonacci(18) se resava dva puta!! 
 *  Problemi manjih dimenzija ce se resavati jos veci broj puta. 
 *  Resenje za ovaj problem je kombinacija rekurzije sa dinamickim 
 *  programiranjem. Podproblemi se resavaju samo jednom, a njihova 
 *  reSenja se pamte u memoriji (obicno u nizovima ili matricama),
 *  odakle se koriste ako tokom resavanja ponovo budu potrebni. 
 * 
 *  Vec izracunate clanove niza cuvamo u statickom nizu celih 
 *  brojeva, jer taj niz onda nece biti smesten na stek, kao sto je 
 *  slucaj sa lokalnim promenljivama, vec u statickoj memoriji 
 *  odakle ce biti dostupan svim pozivima rekurzivne funkcije.
 */
   
/* Funkcija izracunava n-ti fibonaCijev broj */
int F_napredna(int n, int a, int b)
{
  /* Niz koji cuva resenja podproblema. 
   * Kompajler inicijalizuje staticke promenljive na podrazumevane 
   * vrednosti. Stoga, elemente celobrojnog niza inicijalizuje na 0 */
  static int f[20];

  /* Ako je podproblem vec ranije resen, uzimamo gotovo resenje! */
  if(f[n] != 0)
    return f[n];

  /* Izlaz iz rekurzije */
  if(n ==0 || n==1)
    return f[n] = n;

  
  /* Rekurzivni pozivi */
  return f[n] = a*F_napredna(n - 1, a, b) + b*F_napredna(n - 2, a, b);
}

  /* Iterativna verzija */
int F_iterativna(int n, int a, int b)
{
    int i;
    int F_0 = 0;
    int F_1 = 1;
    int tmp;

    if( n == 0 )
        return 0;

    for(i =2 ; i<=n; i++ ) {
        tmp = a* F_1 + b* F_0;
        F_0 = F_1;
        F_1 = tmp;
    }
    
    return F_1;
}


/* Test program */
int main() {
    int n;
    int a;
    int b;

    printf("Unesi koeficijente\n");
    scanf("%d%d", &a, &b);
    printf("Unesi koji clan niza racunamo\n");
    scanf("%d", &n);
	
 /* Testirati program za razliCite vrednosti promenljive
       n. Na primer za n=20, 30, 40, 50, 55, 60 ...*/
    printf("F( %d ) = %d\n", n, F_iterativna(n,a,b));
    printf("F( %d ) = %d\n", n, F_napredna(n,a,b));
    printf("F( %d ) = %d\n", n, F_rekurzivna(n,a,b));
  
    return 0;
}