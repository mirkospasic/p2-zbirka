#include <stdio.h>
#define MAX_DIM 1000

/* Bitno!
 * Kad pisemo rekurzivnu funkciju moramo da obezbedimo:
 * - Izlazak iz rekurzije (obicno trivijalnim slucajem).
 * - Rekurzivni poziv kojim se reSava problem manje 
 *   dimenzije.
 * 
 *	Rekurzija nam omogucava pisanje elegantnijih resenja.
 *  Rekurzivne funkcije troSe mnogo vise memorije nego
 *      iterativne koje reSavaju isti problem.
 */


/*
 * n==0, suma(a,0) = 0
 * n >0, suma(a,n) = a[n-1]+suma(a,n-1)
 *     Suma celog niza je jednaka sumi prvih n-1 elementa 
 *      uveCenoj za poslednji element celog niza.
 */
int sumaNiza(int *a, int n)
{
    /* Ne stavljamo strogu jednakost n==0,
     * za slucaj da korisnik prilikom prvog poziva, 
     * poSalje negativan broj za velicinu niza. 
     */
    if(n<=0 )  
            return 0;   
    
    return a[n-1] + sumaNiza(a,n-1);
}

/*
 * n==0, suma(a,0) = 0
 * n >0, suma(a,n) = a[0]+suma(a+1,n-1)
 *      Suma celog niza je jednaka zbiru prvog elementa 
 *      niza i sume preostalih n-1 elementa.
 */
int sumaNiza2(int *a, int n)
{
    if(n<=0)  
            return 0;
    
    return a[0] + sumaNiza2(a+1,n-1);
}
int main()
{
	int x, a[MAX_DIM];
    int n, i=0;
    
    /* Ucitavamo broj elemenata niza */
    scanf("%d", &n);
    
    /* Ucitavamo n elemenata niza. */
	for(i=0; i<n; i++)
		scanf("%d", &a[i]);
	
	/*      int a[]={ 10, 2, 3, 45, 21};
			int n = sizeof(a)/sizeof(int);  
     * Ovako odredjivanje velicine niza je primenljivo 
     * samo na nizove koji su definisani i inicijalizovani 
     * kao u prethodnom redu, navodjenjem elemenata.
     */
    
    
    printf("Suma elemenata je %d\n",sumaNiza(a, n));
	
	/*
    printf("Suma elemenata je %d\n",sumaNiza2(a, n));
    */
    return 0;   
}
