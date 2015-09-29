#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Pomocna funkcija koja kreira cvor. Funkcija vrednost novog cvora
   inicijalizuje na broj, dok pokazivac na sledeci cvor u novom cvoru 
   postavlja na NULL. Funkcija vraca pokazivac na novokreirani cvor
   ili NULL ako alokacija nije uspesno izvrsena.  */
Cvor *napravi_cvor(int broj)
{
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove liste
   ciji se pocetni cvor nalazi na adresi adresa_glave. */
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

/* Funkcija dodaje novi cvor na pocetak liste. Kreira novi cvor
   koriscenjem funkcije napravi_cvor() i uvezuje ga na pocetak.
   Funkcija vraca 1 ukoliko je doslo do greske pri alokaciji, inace
   vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreira se nov cvor i proverava se da li je bilo greske pri
     alokaciji */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Novi cvor se uvezuje na pocetak, i tako postaje nova glave liste 
   */
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;
  return 0;
}

/* Funkcija dodaje novi cvor na kraj liste. Prilikom dodavanja u
   listu na kraj u velikoj vecini slucajeva nov broj se dodaje u rep 
   liste u rekurzivnom pozivu. U slucaju da je u rekurzivnom pozivu
   doslo do greske pri alokaciji, funkcija vraca 1 visem rekurzivnom
   pozivu koji tu informaciju vraca u rekurzivni poziv iznad, sve dok 
   se ne vrati u main. Ako je funkcija vratila 0, onda nije bilo
   greske. Tek je iz main funkcije moguce pristupiti pravom pocetku
   liste i osloboditi je celu, ako ima potrebe. */
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
  return dodaj_na_kraj_liste(&(*adresa_glave)->sledeci, broj);
}

/* Funkcija dodaje broj u rastuce sortiranu listu tako da nova lista
   ostane sortirana. Vraca 0, ako je alokacija novog cvora prosla
   bez greske, inace vraca 1 da bi ta vrednost bila propagirala nazad 
   do prvog poziva. */
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

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Vraca pokazivac na cvor liste u kome je sadrzan trazeni broj ili
   NULL u slucaju da takav cvor ne postoji u listi. */
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

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Funkcija se u pretrazi oslanja na cinjenicu da je lista koja se
   pretrazuje neopadajuce sortirana. Vraca pokazivac na cvor liste u
   kome je sadrzan trazeni broj ili NULL u slucaju da takav cvor ne
   postoji u listi. */
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

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Funkcija azurira pokazivac na glavu liste, koji moze biti
   promenjen u slucaju da se obrise stara glava liste. */
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

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj,
   oslanjajuci se na cinjenicu da je prosledjena lista sortirana
   neopadajuce. Funkcija azurira pokazivac na glavu liste, koji moze
   biti promenjen ukoliko se obrise stara glava liste. */
void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj)
{
  /* Ako je lista prazna ili glava liste sadrzi vrednost koja je
     veca od broja, kako je lista sortirana rastuce nema potrebe
     broj traziti u repu liste i zato se funkcija prekida. */
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

/* Funkcija ispisuje samo vrednosti cvorova liste razdvojene
   zapetama. */
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

/* Funkcija prikazuje vrednosti cvorova liste pocev od glave ka kraju 
   liste. Ne salje joj se adresa promenljive koja cuva glavu liste,
   jer ova funkcija nece menjati listu, pa nema ni potrebe da azuriza 
   pokazivac na glavu liste iz pozivajuce funkcije. Ova funkcija
   ispisuje samo zagrade, a rekurzivno ispisivanje vrednosti u listi
   prepusta rekurzivnoj pomocnoj funkciji ispisi_vrednosti, koja ce
   ispisati elemente razdvojene zapetom i razmakom. */
void ispisi_listu(Cvor * glava)
{
  putchar('[');
  ispisi_vrednosti(glava);
  printf("]\n");
}
