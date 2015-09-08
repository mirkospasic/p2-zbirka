#include <stdio.h>
#include <stdlib.h>
#include "stabla.h"
/* Funkcija kreira novo stablo identicno stablu koje je dato
   korenom. */  
void kopiraj_stablo(Cvor * koren, Cvor ** duplikat)
{
  
      /* Izlaz iz rekurzije: ako je stablo prazno nema sta da se 
         kopira */ 
      if (koren == NULL) {
    
    
  
  
      /* Dupliramo koren stabla i postavljamo ga da bude koren
         novog stabla
      *duplikat = napravi_cvor(koren->broj);
  
  
      /* Rekurzivno dupliramo levo podstablo i njegovu adresu
         cuvamo
         duplikata. */ 
      kopiraj_stablo(koren->levo, &(*duplikat)->levo);
  
      /* Rekurzivno dupliramo desno podstablo i njegovu
         cuvamo u pokazivacu na desno podstablo korena
         duplikata. */ 
      kopiraj_stablo(koren->desno, &(*duplikat)->desno);



    /* Funkcija izracunava uniju dva stabla - rezultujuce stablo 
       se
void kreiraj_uniju(Cvor ** adresa_korena1, Cvor * koren2)
{
  
      /* Ako drugo stablo nije prazno */ 
      if (koren2 != NULL) {
    
        /* dodajemo njegov koren u prvo stablo */ 
        dodaj_u_stablo(adresa_korena1, koren2->broj);
    
        /* rekurzivno racunamo uniju levog i desnog podstabla
           drugog
        kreiraj_uniju(adresa_korena1, koren2->levo);
    
  



    /* Funkcija izracunava presek dva stabla - rezultujuce
       stablo se
void kreiraj_presek(Cvor ** adresa_korena1, Cvor * koren2)
{
  
      /* Ako je prvo stablo prazno, tada je i rezultat prazno
         stablo */ 
      if (*adresa_korena1 == NULL)
    
  
      /* Kreiramo presek levog i desnog podstabla sa drugim
         stablom, tj. iz
         brisemo sve one elemente koji ne
         stablu */ 
      kreiraj_presek(&(*adresa_korena1)->levo, koren2);
  
  
      /* Ako se koren prvog stabla ne nalazi u drugom stablu
         tada ga
      if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) ==
          NULL)
    



    /* Funkcija izracunava razliku dva stabla - rezultujuce
       stablo se
void kreiraj_razliku(Cvor ** adresa_korena1, Cvor * koren2)
{
  
      /* Ako je prvo stablo prazno, tada je i rezultat prazno
         stablo */ 
      if (*adresa_korena1 == NULL)
    
  
      /* Kreiramo razliku levog i desnog podstabla sa drugim
         stablom, tj. iz
         brisemo sve one elemente koji
         stablu */ 
      kreiraj_razliku(&(*adresa_korena1)->levo, koren2);
  
  
      /* Ako se koren prvog stabla nalazi i u drugom stablu
         tada ga uklanjamo iz prvog stabla */ 
      if (pretrazi_stablo(koren2, (*adresa_korena1)->broj) !=
          NULL)
    



{
  
  
  
  
  
      /* Ucitavamo elemente prvog stabla: */ 
      koren1 = NULL;
  
  
    
  
  
      /* Ucitavamo elemente drugog stabla: */ 
      koren2 = NULL;
  
  
    
  
  
      /* Kreiramo uniju stabala: prvo napravimo kopiju prvog
         stabla kako bi
         operacije;
      kopiraj_stablo(koren1, &pomocni);
  
  
  
  
  
      /* Oslobadjamo stablo za rezultatom operacije da jer
         vise nije neophodan rezultat nakon ispisa
      oslobodi_stablo(&pomocni);
  
      /* Kreiramo presek stabala: prvo napravimo kopiju prvog
         stabla kako
         operacije;
      kopiraj_stablo(koren1, &pomocni);
  
  
  
  
  
      /* Oslobadjamo stablo za rezultatom operacije da jer
         vise nije neophodan rezultat nakon ispisa
      oslobodi_stablo(&pomocni);
  
      /* Kreiramo razliku stabala: prvo napravimo
         stabla kako
         operacije;
      kopiraj_stablo(koren1, &pomocni);
  
  
  
  
  
      /* Oslobadjamo stablo za rezultatom operacije da jer
         vise nije neophodan rezultat nakon ispisa
      oslobodi_stablo(&pomocni);
  
      /* Oslobadjamo i polazna stabla */ 
      oslobodi_stablo(&koren2);
  
  
      /* Zavrsavamo sa programom */ 
      return 0;


