#include <stdio.h>
#define MAX 50


int main(){
    int m[MAX][MAX];
    int v, k;
    int i, j;
    int max_broj_negativnih, max_indeks_kolone;
    int broj_negativnih;

    /* Ucitavamo dimenzije matrice */
    scanf("%d", &v);
    scanf("%d", &k);
    
    if(v<0 || v>MAX || k<0 || k>MAX){
        fprintf(stderr, "-1\n");
        return 0;        
    }
    
    /* Ucitavamo elemente matrice */
    for(i=0; i<v; i++){
        for(j=0; j<k; j++){
            scanf("%d", &m[i][j]);
        }
    }
    
    /*Pronalazimo kolonu koja sadrzi najveci broj negativnih elemenata */
    max_indeks_kolone=0;
    
    max_broj_negativnih=0;
    for(i=0; i<v; i++){
        if(m[i][0]<0){
            max_broj_negativnih++;        
        }
        
    }
    
    for(j=0; j<k; j++){
        broj_negativnih=0;
        for(i=0; i<v; i++){
            if(m[i][j]<0){
                broj_negativnih++;                
            }
            if(broj_negativnih>max_broj_negativnih){
                max_indeks_kolone=j;                
            }            
        }
        
    }
    
    /* Ispisujemo trazeni rezultat */
    printf("%d\n", max_indeks_kolone);
    
    /* Zavrsavamo program */
    return 0;
}