#include<stdio.h>
#define MAX_DIM 256


int br_pojave(int x, int a[], int n)
{
    /* Izlazak iz rekurzije */
    if(n==1) return a[0]==x ? 1 : 0;
    
    int bp = br_pojave(x, a, n-1);
    return a[n-1]==x ? 1 + bp : bp;
}

int main() 
{
    int x, a[MAX_DIM];
    int n, i=0;
    
    /* UCitavamo broj koji se trazi */
    scanf("%d", &x);
    
    /* Sve dok ne dodjemo do kraja ulaza, ucitavamo brojeve u niz; i predstavlja indeks tekuceg broja */
    i=0;
    while(scanf("%d", &a[i])!=EOF){
        i++;
    }
    n=i;
    
    /* Ispisujemo broj pojave broja x u niz a */
    printf("%d\n", br_pojave(x,a,i));
    return 0;
}
