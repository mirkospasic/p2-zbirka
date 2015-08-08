#include <stdio.h>
#include "stabla.h"


int sumirajN (Cvor * koren, int n){
    if(koren==NULL){
            return 0;
    }
    
    if(n==0){
        return koren->broj;        
    }
    
    return sumirajN(koren->levo, n-1) + sumirajN(koren->desno, n-1);    
}


int main(){
    Cvor* koren=NULL;
    int n;
    int nivo;
    
    /* Čitamo vrednost nivoa */
    scanf("%d", &nivo);
    
    
    while(1){
        
        /* Čitamo broj sa standardnog ulaza */
        scanf("%d", &n);
    
        /* Ukoliko je korisnik uneo 0, prekidamo dalje čitanje. */
        if(n==0){
            break;            
        }
        
        /* A ako nije, dodajemo procitani broj u stablo. */
        dodaj_u_stablo(&koren, n);
        
    }
    
    /* Ispisujemo rezultat rada tražene funkcije */
    printf("%d\n", sumirajN(koren,nivo));
    
    /* Oslobadjamo memoriju */
    oslobodi_stablo(&koren);
    
    
    /* Prekidamo izvršavanje programa */
    return 0;
}
