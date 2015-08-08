#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"

Cvor* napravi_cvor(int b ) {  
    Cvor* novi = (Cvor*) malloc(sizeof(Cvor));
    if( novi == NULL)
        return NULL;

    /* Inicijalizacija polja novog čvora */
    novi->broj = b;
    novi->levo = NULL;
    novi->desno = NULL;
    
    return novi;
}


void oslobodi_stablo(Cvor** adresa_korena)  {
      /* Prazno stablo i nema šta da se oslobadja */
    if( *adresa_korena == NULL)
        return;
    
    /* Rekurzivno oslobadjamo najpre levo, a onda i desno podstablo*/
    if( (*adresa_korena)->levo ) 
        oslobodi_stablo(&(*adresa_korena)->levo);
    if( (*adresa_korena)->desno) 
        oslobodi_stablo(&(*adresa_korena)->desno);
    
    free(*adresa_korena);
    *adresa_korena =NULL;
}


void proveri_alokaciju( Cvor* novi) {
    if( novi == NULL) {
        fprintf(stderr, "Malloc greska za nov cvor!\n");
        exit(EXIT_FAILURE);
    }
}

void dodaj_u_stablo(Cvor** adresa_korena, int broj) {
    /* Postojece stablo je prazno*/
    if( *adresa_korena == NULL){ 
        Cvor* novi = napravi_cvor(broj);
        proveri_alokaciju(novi);
        *adresa_korena = novi;  /*  Kreirani čvor novi će biti od sada koren stabla*/
        return;
    }
        
    /* Brojeve smeštamo u uredjeno binarno stablo, pa 
    ako je broj koji ubacujemo manji od broja koji je u korenu  */
    if( broj < (*adresa_korena)->broj)         /* dodajemo u levo podstablo */
        dodaj_u_stablo(&(*adresa_korena)->levo, broj);
    /* ako je broj manji ili jednak od broja koji je u korenu stabla, dodajemo nov čvor desno od korena */
    else 
        dodaj_u_stablo(&(*adresa_korena)->desno, broj);
}

