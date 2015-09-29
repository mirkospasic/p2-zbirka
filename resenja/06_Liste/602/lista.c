#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Cvor *napravi_cvor(int broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

void oslobodi_listu(Cvor ** adresa_glave)
{
  /* Lista je vec prazna */
  if (*adresa_glave == NULL)
    return;

  /* Ako lista nije prazna, treba osloboditi memoriju. Pre
     oslobadjanja memorije za glavu liste, treba osloboditi rep
     liste. */
  oslobodi_listu(&(*adresa_glave)->sledeci);
  /* Nakon oslobodjenog repa, oslobadja se glava liste, i azurira se
     glava u pozivajucoj funkciji tako da odgovara praznoj listi */
  free(*adresa_glave);
  *adresa_glave = NULL;
}

int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreira se nov cvor i proverava se da li je bilo greske pri
     alokaciji */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Novi cvor se uvezuje na pocetak i postaje nova glave liste */
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;
  return 0;
}


int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
  if (*adresa_glave == NULL) {
    /* Glava liste je upravo novi cvor i ujedno i cela lista. */
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;

    /* Azurira se vrednost na koju pokazuje adresa_glave i ujedno se
       azurira i pokazivacka promenljiva u pozivajucoj funkciji. */
    *adresa_glave = novi;
    return 0;
  }


  /* Ako lista nije prazna, broj se dodaje u rep liste. */
  /* Prilikom dodavanja u listu na kraj u velikoj vecini slucajeva
     nov broj se dodaje u rep liste u rekurzivnom pozivu. U slucaju
     da je u rekurzivnom pozivu doslo do greske pri alokaciji,
     funkcija vraca 1 visem rekurzivnom pozivu koji tu informaciju
     vraca u rekurzivni poziv iznad, sve dok se ne vrati u main. Ako
     je funkcija vratila 0, onda nije bilo greske. Tek je iz main
     funkcije moguce pristupiti pravom pocetku liste i osloboditi je
     celu, ako ima potrebe. */
  return dodaj_na_kraj_liste(&(*adresa_glave)->sledeci, broj);
}

int dodaj_sortirano(Cvor ** adresa_glave, int broj)
{
  /* U slucaju prazne liste adresa_glave nove liste je upravo novi
     cvor. */
  if (*adresa_glave == NULL) {
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;

    *adresa_glave = novi;
    return 0;
  }

  /* Lista nije prazna. Ako je broj manji ili jednak vrednosti u
     glavi liste, onda se dodaje na pocetak liste i vraca se
     informacija o uspesnosti alokacije. */
  if ((*adresa_glave)->vrednost >= broj)
    return dodaj_na_pocetak_liste(adresa_glave, broj);

  /* Inace, broj treba dodati u rep, tako da rep i sa novim cvorom
     bude sortirana lista. */
  return dodaj_sortirano(&(*adresa_glave)->sledeci, broj);
}

Cvor *pretrazi_listu(Cvor * glava, int broj)
{
  /* U praznoj listi ga sigurno nema */
  if (glava == NULL)
    return NULL;

  /* Ako glava liste sadrzi trazeni broj */
  if (glava->vrednost == broj)
    return glava;

  /* Ako nije nijedna od prethodnih situacija, pretraga se nastavlja
     u repu liste. */
  return pretrazi_listu(glava->sledeci, broj);
}

Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
  /* Trazenog broja nema ako je lista prazna ili ako je broj manji od 
     vrednosti u glavi liste, jer je lista neopadajuce sortirana. */
  if (glava == NULL || glava->vrednost > broj)
    return NULL;

  /* Ako glava liste sadrzi trazeni broj, vraca se glava. */
  if (glava->vrednost == broj)
    return glava;

  /* Ako nije nijedna od prethodnih situacija, pretraga se nastavlja
     u repu. */
  return pretrazi_listu(glava->sledeci, broj);
}

void obrisi_cvor(Cvor ** adresa_glave, int broj)
{
  /* U praznoj listi, nema cvorova za brisanje. */
  if (*adresa_glave == NULL)
    return;

  /* Prvo se brisu cvorovi iz repa koji imaju vrednost broj. */
  obrisi_cvor(&(*adresa_glave)->sledeci, broj);

  /* Preostaje provera da li glavu liste treba obrisati. */
  if ((*adresa_glave)->vrednost == broj) {
    /* pomocni pokazuje na cvor koji treba da se obrise. */
    Cvor *pomocni = *adresa_glave;
    /* Azurira se pokazivac na glavu da pokazuje na sledeci u listi i 
       brise se cvor koji je bio glava liste. */
    *adresa_glave = (*adresa_glave)->sledeci;
    free(pomocni);
  }
}

void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj)
{
  /* Ako je lista prazna ili glava liste sadrzi vrednost koja je veca 
     od broja, kako je lista sortirana rastuce nema potrebe broj
     traziti u repu liste i zato se funkcija prekida. */
  if (*adresa_glave == NULL || (*adresa_glave)->vrednost > broj)
    return;

  /* Brisu se cvorovi iz repa koji imaju vrednost broj. */
  obrisi_cvor(&(*adresa_glave)->sledeci, broj);

  /* Preostaje provera da li glavu liste treba obrisati. */
  if ((*adresa_glave)->vrednost == broj) {
    /* pomocni pokazuje na cvor koji treba da se obrise. */
    Cvor *pomocni = *adresa_glave;
    /* Azurira se pokazivac na glavu da pokazuje na sledeci u listi i 
       brise se cvor koji je bio glava liste. */
    *adresa_glave = (*adresa_glave)->sledeci;
    free(pomocni);
  }
}

void ispisi_vrednosti(Cvor * glava)
{
  /* Prazna lista */
  if (glava == NULL)
    return;

  /* Ispisuje se vrednost u glavi liste. */
  printf("%d", glava->vrednost);

  /* Ako rep nije prazan, ispisuje se znak ',' i razmak. Rekurzivno
     se poziva ista funkcija za ispis ostalih. */
  if (glava->sledeci != NULL) {
    printf(", ");
    ispisi_vrednosti(glava->sledeci);
  }
}


void ispisi_listu(Cvor * glava)
{
  /* Funkciji se ne salje adresa promenljive koja cuva glavu liste,
     jer ova funkcija nece menjati listu, pa nema ni potrebe da
     azuriza pokazivac na glavu liste iz pozivajuce funkcije. Ova
     funkcija ispisuje samo zagrade, a rekurzivno ispisivanje
     vrednosti u listi prepusta rekurzivnoj pomocnoj funkciji
     ispisi_vrednosti, koja ce ispisati elemente razdvojene zapetom i 
     razmakom. */
  putchar('[');
  ispisi_vrednosti(glava);
  printf("]\n");
}
