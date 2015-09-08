#include <stdio.h>
#define MAX_DIM 256

int skalarno(int a[], int b[], int n)
{
    /* Izlazak iz rekurzije */
    if(n==0) return 0;

    /* Na osnovu reSenja problema dimenzije n-1, resavamo problem dimenzije n */
    else return a[n-1] * b[n-1] + skalarno(a,b,n-1);
}

int main()
{
    int i, a[MAX_DIM], b[MAX_DIM], n;

    /* Unosimo dimenziju nizova, */
    scanf("%d",&n);

    /* a zatim i same nizove. */
    for(i=0; i<n; i++)
    	scanf("%d",&a[i]);

    for(i=0;i<n;i++)
    	scanf("%d",&b[i]);

    /* Ispisujemo rezultat skalarnog proizvoda dva ucitana niza. */
    printf("%d\n", skalarno(a,b,n));

    return 0;
}