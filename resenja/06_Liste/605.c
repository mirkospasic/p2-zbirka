/* Simuliramo rad jednog saltera na kom se prvo zakazuju termini, tako sto se korisnik prijavljuje sa jmbg-om i zahtevom,
 * a potom sluzbenik usluzuje redom korisnike kako su se prijavljivali.
 * Sluzbenik ima mogucnost da svakog korisnika vrati natrag na kraj reda, ukoliko na postavljeno pitanje odgovori sa Da,
 * Posle svakog 10 opsluzenog korisnika nudi mu se mogucnost da prekine sa radom, ne vezano od broja korisnika koji i
 * dalje cekaju u redu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* NAPOMENA: Red (eng. queue) je struktura podataka nad kojom su 
   definisane sledece operacije:
   1) Dodavanje elementa -- kazemo da je element dodat na kraj reda
      (eng. enqueue() operacija)
   2) Uklanjanje elementa koji je prvi dodat -- kazemo da je 
      element skinut sa pocetka reda (eng. dequeue() operacija)
   3) Ocitavanje vrednosti elementa koji je na pocetku reda (eng.
      front() operacija)

   Red spada u FIFO strukture (eng. First In First Out). Moze se 
   implementirati na vise nacina. Najjednostavniji nacin je da se
   definise kao niz. Medjutim, tada je ogranicen max. broj elemenata
   u redu dimenzijom niza. Zbog toga se obicno pribegava koriscenju
   lista za implementaciju reda, gde se enqueue() operacija svodi
   na dodavanje na kraj liste, a dequeue() operacija se svodi na uklanjanje
   glave liste. Obe operacije se izvode u konstantnom vremenu, pod uslovom
   da se osim pokazivaca na glavu liste cuva i pokazivac na poslednji element
   u listi.

   U ovom zadatku ce red biti koriscen da se u njega smestaju korisnicki zahtevi i da ih 
   sluzbenik usluzuje i sklanja iz reda.
*/

#define MAX 1000
#define JMBG_DUZINA 14

/* Struktura sa podacima o zahtevima korisnika */
typedef struct {
    char jmbg[JMBG_DUZINA];  /* Jmbg korisnika */
    char opis[MAX];    /* opis zahteva korisnika */
} Zahtev;



/* Struktura koja predstavlja cvor liste */
typedef struct cvor {
    Zahtev nalog;          /* zahtev korisnika */
    struct cvor *sledeci;   /* pokazivac na sledeci cvor */
} Cvor;


/* Funkcija kreira novi cvor, upisuje u njega ime fajla
   i vraca adresu novog cvora ili NULL ako je doslo do greske 
   pri alokaciji. Ako je doslodo greske, trebalo bi osloboditi
   ceo red. Ostavljamo da to uradi funkcija koja je pozvala
   funkciju napravi_cvor, a gresku joj signaliziramo saljuci 
   joj NULL.*/
Cvor *napravi_cvor( Zahtev* zahtev) {
    Cvor *novi = (Cvor *) malloc(sizeof(Cvor)); 
    if ( novi  == NULL) 
      return NULL;

    novi->nalog = *zahtev;
    novi->sledeci = NULL;
    return novi;
}

/* Funkcija prazni red */
void oslobodi_red(Cvor ** pocetak, Cvor ** kraj)
{
    Cvor *pomocni;

    while (*pocetak != NULL) {
        pomocni = *pocetak;
        *pocetak = (*pocetak)->sledeci;
        free(pomocni);
    }
    *kraj = NULL;
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi i ukoliko 
 * alokacija nije bila uspesna, oslobadja se sva prethodno zauzeta memorija 
 * za listu cija pocetni cvor se nalazi na adresi adresa_pocetka.  */
void proveri_alokaciju(Cvor** adresa_pocetka, Cvor** adresa_kraja, Cvor* novi) {
    /* Ukoliko je novi NULL */
    if ( novi == NULL ) {
        fprintf(stderr, "Neuspela alokacija za nov cvor\n");
        oslobodi_red(adresa_pocetka, adresa_kraja);     /* oslobadjamo sve dinamicki alocirano */    
        exit(EXIT_FAILURE);
    }
}


/* Funkcija dodaje na kraj reda novi fajl */
void dodaj_u_red(Cvor ** adresa_pocetka, Cvor ** adresa_kraja, Zahtev* zahtev) {
    Cvor *novi = napravi_cvor(zahtev);
    proveri_alokaciju(adresa_pocetka, adresa_kraja, novi);
    
    /* U red se uvek dodaje na kraj, ali zbog postojanja pokazivaca na kraj, 
     * dodavanje na kraj je podjednako efikasno kao dodavanje na pocetak  */
    if (*adresa_kraja != NULL) {
        (*adresa_kraja)->sledeci = novi;
        *adresa_kraja = novi;
    } else {
        /* ako je red bio ranije prazan */
        *adresa_pocetka = novi;
        *adresa_kraja = novi;
    }
}

/* Funkcija skida sa pocetka reda zahtev. Ako je poslednji argument
   pokazivac razlicit od NULL, tada se u strukturu na koju on
   pokazuje upisuje  zahtev koji je upravo skinut sa reda
   dok u suprotnom ne upisuje nista. Funkcija vraca 0 ako je red
   prazan (pa samim tim nije bilo moguce skinuti vrednost sa 
   reda) ili 1 u suprotnom. */
int skini_sa_reda(Cvor ** adresa_pocetka, Cvor ** adresa_kraja, Zahtev *zahtev) {
    Cvor *pomocni;

    if (*adresa_pocetka == NULL)
        return 0;

    if (zahtev != NULL)
        *zahtev = (*adresa_pocetka)->nalog;

    pomocni = *adresa_pocetka;
    *adresa_pocetka = (*adresa_pocetka)->sledeci;
    free(pomocni);

    if (*adresa_pocetka == NULL)
        *adresa_kraja = NULL;

    return 1;
}

 
/* Funkcija vraca pokazivac na strukturu koji sadrzi zahtev korisnika
   na pocetku reda. Ukoliko je red prazan, vraca NULL */
Zahtev* pocetak_reda(Cvor * pocetak) {
    if (pocetak == NULL)
        return NULL;
    
    return &(pocetak->nalog);
}

/* Funkcija prikazuje red  */
void prikazi_red(Cvor * pocetak) {
    for (; pocetak != NULL; pocetak = pocetak->sledeci){
        printf("%s %s\n", (pocetak->nalog).jmbg, (pocetak->nalog).opis);
        }
    
    printf("\n");
}

/* Glavni program */
int main(int argc, char **argv)
{
    Cvor *pocetak = NULL, *kraj = NULL; // red je prazan 
    Zahtev nov_zahtev;  
    Zahtev* sledeci = NULL;
    char odgovor[3];
    int broj_usluzenih =0;
    
    /* Korisnici rezervisu termin, unosenjem JMBG broja i opisa usluge koja im je potrebna */
    printf("Korisnici se prijavljuju unosenjem svog JMBG broja i opisa potrebne usluge:\n[CTRL+D za kraj]\n");
    while(  scanf( "%s\n" ,nov_zahtev.jmbg) != EOF) {   /* neophodno je \n u scanf da bi se i nov red procitao da bi fgets nakon toga procitao ispravan red sa opisom zahteva*/
        fgets(nov_zahtev.opis,MAX-1, stdin);
        dodaj_u_red(&pocetak, &kraj, &nov_zahtev);
    }

    /* Dokle god ima korisnika u redu, usluzujemo ih   */    
    while ( 1 ) {
        sledeci = pocetak_reda(pocetak);
        if(sledeci == NULL)
            break; // nema nikog vise u redu
            
        printf("\nSledeci na redu je korisnik sa JMBG brojem: %s\n\n", sledeci->jmbg);
        
        skini_sa_reda(&pocetak, &kraj, &nov_zahtev);
        /* usluzujemo korisnika*/
        printf("Usluzuje se korisnik sa \n\tjmbg brojem: %s \n\ti zahtevom: %s\n\n", nov_zahtev.jmbg, nov_zahtev.opis);
        
        broj_usluzenih++;
        
        printf ("Da li korisnika  vracate na kraj reda? [Da/Ne] " );
        scanf("%s",odgovor);
        
        /* Sada se korisnik dodaje na kraj reda */
        if(strcmp(odgovor, "Da") == 0)
            dodaj_u_red(&pocetak, &kraj, &nov_zahtev);
        
        if( broj_usluzenih %10 == 0) {
            printf("Da li je kraj smene? [Da/Ne]? ");
            scanf("%s",odgovor);
        
            if(strcmp(odgovor, "Da") == 0)
               break;
        }
    }
    
    /* Alternativno bez koriscenja funkcije za pocetak reda 
     * 
     * while ( skini_sa_reda(&pocetak, &kraj, &nov_zahtev); ) {            
        printf("Sledeci na redu je korisnik sa JMBG brojem: %s\n", nov_zahtev.jmbg);
        
        printf("Usluzuje se korisnik sa \n\tjmbg brojem: %s \n\ti zahtevom: %s\n", nov_zahtev.jmbg, nov_zahtev.opis);
        
        printf ("Da li se vracate na kraj reda? [Da/ne] " );
        scanf("%s",odgovor);
        
        if(strcmp(odgovor, "Da") == 0)
            dodaj_u_red(&pocetak, &kraj, nov_zahtev);
    }
    */
    
    
    /* Oslobadjamo red ukoliko je sluzbenik prekinuo sa radom mozda je bilo jos neusluzenih korisnika */
    oslobodi_red(&pocetak, &kraj);

    return 0;
}