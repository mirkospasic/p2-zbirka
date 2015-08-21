#include <stdio.h>
#include <stdlib.h>

#define MAX_V 10 
#define MAX_K 10

/* Funkcija proverava da li su ispisani svi elementi iz matrice, 
   odnosno da li se narusio prirodan poredak medju granicama */
int krajIspisa(int top, int bottom, int left, int right) 
{
  return  !(top <= bottom && left <= right);
}

/* Funkcija spiralno ispisuje elemente matrice */
void ispisi_matricu_spiralno(int a[][MAX_K], int n, int m) 
{
  int i,j,top, bottom,left, right;

  top=left = 0;
  bottom=n-1;
  right = m-1; 

  while( !krajIspisa(top, bottom, left, right) ) {
    /* Ispisuje se prvi red*/
    for(j=left; j<=right; j++)
      printf("%d ",a[top][j]);
        
    /* Spustamo prvi red */
    top++;
        
    if(krajIspisa(top,bottom,left,right))
      break;
        
    for(i=top; i<=bottom; i++ )
      printf("%d ",a[i][right]);
        
    /* Pomeramo desnu kolonu za naredni krug ispisa 
       bliže levom kraju */
    right--;
        
    if(krajIspisa(top,bottom,left,right))
      break;
        
    /* Ispisujemo donju vrstu */
    for(j=right; j>=left; j-- )
      printf("%d ",a[bottom][j]);
        
    /* Podižemo donju vrstu za naredni krug ispisa */ 
    bottom--;  
        
    if(krajIspisa(top,bottom,left,right))
      break;
        
    /* Ispisujemo prvu kolonu*/
    for(i=bottom; i>=top; i-- )
      printf("%d ",a[i][left]);
        
    /* Pripremamo levu kolonu za naredni krug ispisa */
    left++; 
  }
  putchar('\n');
}

void ucitaj_matricu(int a[][MAX_K], int n, int m) 
{
  int i, j;

  for(i=0 ;i<n; i++)
    for(j=0; j<m; j++)      
      scanf("%d", &a[i][j]);    
}

int main( ) 
{
  int a[MAX_V][MAX_K];
  int m,n;
 
  /* Ucitaj broj vrsta i broj kolona matrice */ 
  scanf("%d",&n);
  scanf("%d", &m);
    
  if( n > MAX_V || n <= 0 || m > MAX_K || m <= 0) {
    fprintf(stderr, "Greska: neodgovarajuce dimenzije ");
    fprintf(stderr, "matrice.\n");
    exit(EXIT_FAILURE);	
  }
     
  ucitaj_matricu(a, n, m);
  ispisi_matricu_spiralno(a, n, m);

  return 0;
}
