#include <stdio.h>
#include <stdlib.h>

/* NAPOMENA: 
   Jednostruko povezana lista je struktura podataka 
   koja se sastoji od sekvence cvorova. Svaki cvor sadrzi 
   podatak (odredjenog tipa) i pokazivac na sledeci cvor u
   sekvenci. Prvi cvor u sekvenci naziva se glava liste. Ostatak
   liste (bez glave) je takodje lista, i naziva se rep liste.
   Lista koja ne sadrzi cvorove naziva se prazna lista. Prilikom
   baratanja listom mi cuvamo samo pokazivac na glavu liste.
   Kada pristupimo glavi liste, u njoj imamo zapisanu adresu 
   sledeceg elementa, pa mu samim tim mozemo pristupiti. Kada mu
   pristupimo, u njemu je sadrzana adresa sledeceg elementa, pa
   preko tog pokazivaca mozemo da mu pristupimo, itd. Poslednji 
   element u listi nema sledeci element: u tom slucaju se 
   njegov pokazivac na sledeci postavlja na NULL. Takodje, prazna
   lista se predstavlja NULL pokazivacem.
   
   Prednost koriscenja povezanih lista  u odnosu na dinamicki
   niz je u tome sto se elementi mogu efikasno umetati i brisati
   sa bilo koje pozicije u nizu, bez potrebe za realokacijom ili
   premestanjem elemenata. Nedostatak ovakvog pristupa je to sto
   ne mozemo nasumicno pristupiti proizvoljnom elementu, vec se 
   elementi moraju obradjivati redom (iteracijom kroz listu). 
   
   
   Prilikom promene liste (dodavanje novog elementa, brisanje elementa, 
   premestanje elemenata, itd.) postoji mogucnost da glava liste bude 
   promenjena, tj. da to postane neki drugi cvor (sa drugom adresom). 
   U tom slucaju se pokazivac na glavu liste mora azurirati. Kada
   promenu liste obavljamo u posebnoj funkciji onda je potrebno da se 
   pozivajucoj funkciji vrati azurirana informacija o adresi glave liste.
   
   Pozvana funkcija koja vrsi promenu na listi prihvata kao argument 
   pokazivac na pokazivacku promenljivu koja u pozivajucoj funkciji cuva 
   adresu glave i koju, eventalno, treba azurirati. 
   Sada pozvana funkcija moze interno da preko dobijenog pokazivaca 
   promeni promenljivu pozivajuce funkcije direktno. Npr:
   funkcija_za_promenu(&pok, ...); 
*/

/* Struktura koja predstavlja cvor liste */
typedef struct cvor {
    /* Podatak koji cvor sadrzi */
    int vrednost;               
    /* Pokazivac na sledeci cvor liste */
    struct cvor *sledeci;   
} Cvor;



/* Pomocna funkcija koja kreira cvor. Funkcija vrednost
   novog cvora inicijalizuje na broj, dok pokazivac na
   sledeci cvor u novom cvoru postavlja na NULL. 
   Funkcija vraca pokazivac na novokreirani cvor ili NULL
   ako alokacija nije uspesno izvrsena.  */
Cvor * napravi_cvor(int broj) {
    Cvor * novi = (Cvor *) malloc(sizeof(Cvor));
    if( novi == NULL )
        return NULL;

    /* Inicijalizacija polja u novom cvoru */
    novi->vrednost = broj;
    novi->sledeci = NULL;
    return novi;
}




/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente liste 
   ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave) {
    Cvor *pomocni = NULL;

    /* Ako lista nije prazna, onda ima memorije koju treba osloboditi */
    while (*adresa_glave != NULL) {
        /* Potrebno je najpre zapamtiti adresu sledeceg elementa, 
	   a tek onda osloboditi element koji predstavlja glavu liste */
        pomocni = (*adresa_glave)->sledeci;
        free(*adresa_glave);
        /* Sledeci element je nova glava liste */
        *adresa_glave = pomocni;
    }
}



/* Funkcija proverava uspesnost alokacije memorije za cvor novi i ukoliko 
   alokacija nije bila uspesna, oslobadja se sva prethodno zauzeta memorija 
   za listu ciji pocetni cvor se nalazi na adresi adresa_glave.  */
void proveri_alokaciju(Cvor** adresa_glave, Cvor* novi) {
    /* Ukoliko je novi NULL */
    if ( novi == NULL ) {
        fprintf(stderr, "Neuspela alokacija za nov cvor\n");
	/* Oslobadjamo svu dinamicki alociranu memoriju i prekidamo program */
 
        oslobodi_listu(adresa_glave);     
        exit(EXIT_FAILURE);
    }
}



/* Funkcija dodaje novi cvor na pocetak liste. 
   Kreira novi cvor koriscenjem funkcije napravi_cvor i uvezuje ga na pocetak */
void dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj) {
    /* Kreiramo nov cvor i proveravamo da li je bilo greske pri alokaciji */
    Cvor *novi = napravi_cvor(broj); 
    proveri_alokaciju(adresa_glave, novi);
    
    /* Uvezujemo novi cvor na pocetak */
    novi->sledeci = *adresa_glave;
    /* Nov cvor je sada nova glava liste */
    *adresa_glave = novi;    
}


/* Pomocna funkcija pronalazi cvor u listi iza koga treba umetnuti 
   nov element sa vrednoscu broj.*/
Cvor * pronadji_mesto_umetanja(Cvor* glava, int broj ) {
    /*Ako je lista prazna onda nema takvog mesta i vracamo NULL */
    if(glava == NULL)
        return NULL;
    
    /* Krecemo se kroz listu sve dok se ne dodje do elementa 
   ciji je sledeci element veci ili jednak od novog elementa, 
   ili dok se ne dodje do poslednjeg elementa.
   
   Zbog lenjog izracunavanja izraza u C-u prvi deo konjukcije 
   mora biti provera da li smo dosli do poslednjeg elementa liste
   pre nego sto proverimo vrednost njegovog sledeceg elementa,
   jer u slucaju poslednjeg, sledeci ne postoji, pa ni vrednost.*/
    while (glava->sledeci != NULL  && glava->sledeci->vrednost < broj) 
        glava = glava->sledeci;
    
    /* Iz petlje smo mogli izaci jer smo dosli do poslednjeg elementa 
       ili smo se zaustavili ranije na elementu ciji sledeci ima 
       vrednost vecu od broj */
    return glava;
}


void dodaj_iza(Cvor* tekuci, Cvor* novi) { 
    /* Novi element dodajemo iza tekuceg elementa */
    novi->sledeci = tekuci->sledeci;
    tekuci->sledeci = novi;
}

/* Funkcija dodaje novi element u sortiranu listu 
   tako da nova lista ostane sortirana.*/
void dodaj_sortirano(Cvor ** adresa_glave, int broj) {    
    /* U slucaju prazne liste glava nove liste je upravo novi cvor */
    if ( *adresa_glave == NULL ) {
        Cvor *novi = napravi_cvor(broj);
        /* Proveravamo da li je doslo do greske prilikom alokacije memorije */
        proveri_alokaciju(adresa_glave, novi);
        *adresa_glave = novi;
        return;
    }

    /* Lista nije prazna*/
    /* Ako je broj manji ili jednak vrednosti u glavi liste, 
       onda ga dodajemo na pocetak liste  */
    if ( (*adresa_glave)->vrednost >= broj ) {
        dodaj_na_pocetak_liste(adresa_glave, broj);
        return;
    }

    /* U slucaju da je glava liste element manji od novog elementa, 
       tada pronalazimo element liste iza koga treba da se umetne nov broj */
    Cvor* pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
    
    Cvor *novi = napravi_cvor(broj);
    /* Proveravamo da li je doslo do greske prilikom alokacije memorije */
    proveri_alokaciju(adresa_glave, novi);
    
    /* Uvezujemo novi cvor iza pomocnog */
    dodaj_iza(pomocni, novi);    
}



/* Funkcija trazi u listi element cija je vrednost jednaka datom broju.
   Funkcija se u pretrazi oslanja na cinjenicu da je lista 
   koja se pretrazuje rastuce sortirana.
   Vraca pokazivac na cvor liste u kome je sadrzan trazeni broj 
   ili NULL u slucaju da takav element ne postoji u listi. */
Cvor* pretrazi_listu(Cvor * glava, int broj) {
    /* U konjukciji koja cini uslov ostanka u petlji, bitan je redosled! */
    for ( ; glava != NULL && glava->vrednost <= broj ; glava = glava->sledeci)
      /* Pronasli smo*/
      if (glava->vrednost == broj) 
	return glava;

    /* Nema trazenog broja u listi i vracamo NULL*/
    return NULL;
}



/* Funkcija brise iz liste sve cvorove koji sadrze dati broj, 
   oslanjajuci se na cinjenicu da je prosledjena lista sortirana rastuce.
   Funkcija azurira pokazivac na glavu liste, koji moze biti 
   promenjen u slucaju da se obrise stara glava liste. */
void obrisi_element(Cvor ** adresa_glave, int broj) {
    Cvor *tekuci = NULL ;
    Cvor *pomocni = NULL ;

    /* Brisemo sa pocetka liste sve eventualne cvorove
       koji su jednaki datom broju, i azuriramo pokazivac na glavu */
    while (*adresa_glave != NULL && (*adresa_glave)->vrednost == broj) {
        /* Sacuvamo adresu repa liste pre oslobadjanja glave */
        pomocni = (*adresa_glave)->sledeci; 
        free(*adresa_glave);
        *adresa_glave = pomocni;
    }

    /* Ako je nakon toga lista ostala prazna ili glava liste sadrzi vrednost 
       koja je veca od broja, kako je lista sortirana rastuce nema potrebe 
       broj traziti u repu liste i zato prekidamo funkciju */
    if ( *adresa_glave == NULL || (*adresa_glave)->vrednost > broj)
        return;

    /* Od ovog trenutka se u svakom koraku nalazimo u tekucem cvoru cija 
       vrednost je manja od trazenog broja (kao i svi levo od njega). 
       Poredimo vrednost sledeceg cvora (ako postoji) sa trazenim brojem 
       i brisemo ga ako je jednak, a prelazimo na sledeci cvor ako je 
       razlicit. Ovaj postupak ponavljamo dok ne dodjemo do poslednjeg cvora 
       ili prvog cvora cija vrednost je veca od trazenog broja. */
    tekuci = *adresa_glave;
    while (tekuci->sledeci != NULL && tekuci->sledeci->vrednost <= broj)
        if (tekuci->sledeci->vrednost == broj) { 
	  /* tekuci->sledeci treba obrisati, 
	     zbog toga sacuvamo njegovu adresu u pomocni */
            pomocni = tekuci->sledeci;  
            /* Tekucem preusmerimo pokazivac sledeci 
	       tako sto preskacemo njegovog trenutnog sledeceg.
	       Njegov novi sledeci ce biti sledeci od ovog koga brisemo. */
            tekuci->sledeci = tekuci->sledeci->sledeci;
	    /* Sada mozemo
	     * slobodno i da oslobodimo cvor sa vrednoscu broj */
            free(pomocni); 
        } else { 
	  /* Ne treba brisati sledeceg, jer je manji od trazenog 
	     i prelazimo na sledeci */
            tekuci = tekuci->sledeci;
        }
    return;
}

/* Funkcija prikazuje elemente liste pocev od glave ka kraju liste.
   Ne saljemo joj adresu promenljive koja cuva glavu liste, jer 
   ova funkcija nece menjati listu, pa nema ni potrebe da azuriza pokazivac
   na glavu liste iz pozivajuce funkcije. */
void ispisi_listu(Cvor * glava)
{
    putchar('[');
    for ( ; glava != NULL; glava = glava->sledeci)
    {
        printf("%d", glava->vrednost);
	if( glava->sledeci != NULL )
	  printf(", ");
    }
    
    printf("]\n");
}





/* Glavni program u kome testiramo sve funkcije za rad sa listama */
int main() {
    Cvor *glava = NULL;  /* na pocetku imamo praznu listu */
    Cvor *trazeni = NULL;
    int broj;

    /* Testiramo dodavanje u listu tako da ona bude rastuce sortirana */
    printf("\nUnosite elemente liste! (za kraj unesite EOF tj. CTRL+D)\n");
    printf("\n\tLista: ");
    ispisi_listu(glava);
    
    while(scanf("%d",&broj)>0)
    {
        dodaj_sortirano(&glava, broj);
        printf("\n\tLista: ");
        ispisi_listu(glava);
    }

    printf("\nUnesite element koji se trazi u listi: ");
    scanf("%d", &broj);

    trazeni = pretrazi_listu(glava, broj);
    if(trazeni == NULL)
        printf("Element NIJE u listi!\n");
    else
        printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

    
    /* Brisemo elemente iz liste cije polje vrednost je jednako broju 
       procitanom sa ulaza */
    printf("\nUnesite element koji se brise iz liste: ");
    scanf("%d", &broj);

    obrisi_element(&glava, broj);

    printf("Lista nakon brisanja:  ");
    ispisi_listu(glava);

    oslobodi_listu(&glava);

    return 0;
}
