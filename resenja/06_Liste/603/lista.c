#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Pomocna funkcija koja kreira cvor. Funkcija vrednost novog
   cvora inicijalizuje na broj, dok pokazivac na sledeci cvor u
   novom cvoru postavlja na NULL. Funkcija vraca pokazivac na
   novokreirani cvor ili NULL ako alokacija nije uspesno
   izvrsena. */
Cvor *napravi_cvor(int broj)
{
    Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
    if (novi == NULL)
        return NULL;

    /* Inicijalizacija polja u novom cvoru. */
    novi->vrednost = broj;
    novi->sledeci = NULL;
    return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente
   liste ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave)
{
    Cvor *pomocni = NULL;

    /* Ako lista nije prazna, onda treba osloboditi memoriju. */
    while (*adresa_glave != NULL) {
        /* Potrebno je prvo zapamtiti adresu sledeceg elementa i
           onda osloboditi element koji predstavlja glavu liste*/
        pomocni = (*adresa_glave)->sledeci;
        free(*adresa_glave);
        /* Sledeci element je nova glava liste */
        *adresa_glave = pomocni;
    }
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi
   i ukoliko alokacija nije bila uspesna, oslobadja se sva
   prethodno zauzeta memorija za listu ciji pocetni cvor se
   nalazi na adresi adresa_glave. */
void proveri_alokaciju(Cvor ** adresa_glave, Cvor * novi)
{
    if (novi == NULL) {
        fprintf(stderr, "Neuspela alokacija za nov cvor\n");

        /* Oslobadjamo dinamicki alociranu memoriju i prekidamo
           program */
        oslobodi_listu(adresa_glave);
        exit(EXIT_FAILURE);
    }
}


/* Funkcija dodaje novi cvor na pocetak liste. Kreira novi cvor 
   koriscenjem funkcije napravi_cvor() i uvezuje ga na pocetak.*/
void dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
    Cvor *novi = napravi_cvor(broj);
    proveri_alokaciju(adresa_glave, novi);

    /* Sledbenik novog cvora je glava stare liste */
    novi->sledeci = *adresa_glave;
    /* Ako stara lista nije bila prazna, onda prethodni od glave
       treba da bude nov cvor. */
    if (*adresa_glave != NULL)
        (*adresa_glave)->prethodni = novi;
    /* azuriramo pokazivac na glavu u pozivajucoj funkciji jer
       je novi od sada glava liste  */
    *adresa_glave = novi;
}


/* Funkcija pronalazi i vraca pokazivac na poslednji element
   liste, ili NULL kao je lista prazna  */
Cvor *pronadji_poslednji(Cvor * glava)
{
    /*
     * ako je lista prazna, nema ni poslednjeg cvor i u tom
     * slucaju vracamo NULL.
     */
    if (glava == NULL)
        return NULL;

    /*
     * Sve dok glava ne pokazije na cvor koji nema sledeceg,
     * pomeramo pokazivac glava na taj sledeci element. Kada
     * izadjemo iz petlje, glava ce pokazivati na element liste
     * koji nema sledeceg, tj, poslednji element liste je. Zato
     * vracamo vrednost pokazivaca glava. glava je argument
     * funkcije i njegove promene nece se odraziti na vrednost
     * pokazivaca glava u pozivajucoj funkciji. 
     */
    while (glava->sledeci != NULL)
        glava = glava->sledeci;

    return glava;
}


/*
 * Funkcija nov cvor dodaje na kraj liste.  
 */
void dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
    Cvor *novi = napravi_cvor(broj);
    /*
     * Proveravamo da li je doslo do greske prilikom alokacije
     * memorije 
     */
    proveri_alokaciju(adresa_glave, novi);

    /*
     * ako je lista u koju dodajemo prazna. Nov cvor je jedini
     * cvor u novoj listi i time je i glava nove liste. 
     */
    if (*adresa_glave == NULL) {
        *adresa_glave = novi;
        return;
    }

    /*
     * Ako lista nije prazna, pronalazimo poslednji element
     * liste 
     */
    Cvor *poslednji = pronadji_poslednji(*adresa_glave);

    /*
     * tada uvezujemo nov cvor na kraj, tako sto mu azuriramo
     * pokazivac na prethodni da pokazuje na poslednjeg.
     * Sledeci od poslednjeg treba da bude nov cvor.
     */
    poslednji->sledeci = novi;
    novi->prethodni = poslednji;
}




/*
 * Pomocna funkcija pronalazi cvor u listi iza koga treba
 * umetnuti nov element sa vrednoscu broj.
 */
Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj)
{
    /*
     * Ako je lista prazna onda nema takvog mesta i vracamo NULL 
     */
    if (glava == NULL)
        return NULL;

    /*
     * Krecemo se kroz listu sve dok se ne dodje do elementa
     * ciji je sledeci element veci ili jednak od novog
     * elementa, ili dok se ne dodje do poslednjeg elementa.
     * 
     * Zbog lenjog izracunavanja izraza u C-u prvi deo
     * konjukcije mora biti provera da li smo dosli do
     * poslednjeg elementa liste pre nego sto proverimo vrednost 
     * njegovog sledeceg elementa, jer u slucaju poslednjeg,
     * sledeci ne postoji, pa ni vrednost.
     */
    while (glava->sledeci != NULL
           && glava->sledeci->vrednost < broj)
        glava = glava->sledeci;

    /*
     * Iz petlje smo mogli izaci jer smo dosli do poslednjeg
     * elementa ili smo se zaustavili ranije na elementu ciji
     * sledeci ima vrednost vecu od broj 
     */
    return glava;
}



void dodaj_iza(Cvor * tekuci, Cvor * novi)
{
    /*
     * Novi element dodajemo iza tekuceg elementa 
     */
    novi->sledeci = tekuci->sledeci;
    novi->prethodni = tekuci;

    /*
     * Ako tekuci ima sledeceg, onda upravo dodajemo njemu
     * prethodnika i potrebno je i njemu da postavimo pokazivace 
     * na ispravne adrese 
     */
    if (tekuci->sledeci != NULL)
        tekuci->sledeci->prethodni = novi;
    tekuci->sledeci = novi;
}



/*
 * Fukcija dodaje u listu nov cvor na odgovarajuce mesto, tako
 * sto pronalazi cvor u listi iza kod treba uvezati nov cvor. 
 */
void dodaj_sortirano(Cvor ** adresa_glave, int broj)
{
    /*
     * Ako je lista prazna, glava nove liste je novi cvor 
     */
    if (*adresa_glave == NULL) {
        Cvor *novi = napravi_cvor(broj);
        proveri_alokaciju(adresa_glave, novi);
        *adresa_glave = novi;
        return;
    }

    /*
     * Lista nije prazna
     */
    /*
     * Ukoliko je vrednost glave liste veca od nove vrednosti
     * onda nov cvor treba staviti na pocetak liste. 
     */
    if ((*adresa_glave)->vrednost >= broj) {
        dodaj_na_pocetak_liste(adresa_glave, broj);
        return;
    }

    Cvor *novi = napravi_cvor(broj);
    proveri_alokaciju(adresa_glave, novi);

    Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
    /*
     * Uvezujemo novi cvor iza pomocnog 
     */
    dodaj_iza(pomocni, novi);
}

/*
 * Funkcija trazi u listi element cija je vrednost jednaka datom 
 * broju. Vraca pokazivac na cvor liste u kome je sadrzan
 * trazeni broj ili NULL u slucaju da takav element ne postoji u 
 * listi. 
 */
Cvor *pretrazi_listu(Cvor * glava, int broj)
{
    for (; glava != NULL; glava = glava->sledeci)
        if (glava->vrednost == broj)
            return glava;

    /*
     * Nema trazenog broja u listi i vracamo NULL
     */
    return NULL;
}

/*
 * Funkcija trazi u listi element cija je vrednost jednaka datom
 * broju. Funkcija se u pretrazi oslanja na cinjenicu da je lista
 * koja se pretrazuje neopadajuce sortirana. Vraca pokazivac na
 * cvor liste u kome je sadrzan trazeni broj ili NULL u slucaju da 
 * takav element ne postoji u listi. 
 */
Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
    /*
     * U konjukciji koja cini uslov ostanka u petlji, bitan je
     * redosled! 
     */
    for (; glava != NULL && glava->vrednost <= broj;
         glava = glava->sledeci)
        if (glava->vrednost == broj)
            return glava;

    /*
     * Nema trazenog broja u listi i vracamo NULL
     */
    return NULL;
}


/*
 * Funkcija brise u listi na koju pokazuje pokazivac glava onaj
 * cvor na koji pokazuje pokazivac tekuci. Obratiti paznju da je
 * kod dvostruke liste ovo mnogo lakse uraditi jer cvor tekuci
 * sadrzi pokazivace na svog sledbenika i prethodnika u listi.
 * Pre nego sto fizicki obrisemo tekuci obavezno moramo azurirati
 * sve pokazivace sledbenika i prethodnika. 
 */
void obrisi_tekuci(Cvor ** adresa_glave, Cvor * tekuci)
{
    /*
     * Ako je tekuci NULL pokazivac nema sta da se brise. 
     */
    if (tekuci == NULL)
        return;

    /*
     * Ako postoji prethodnik od tekuceg onda se postavlja da
     * njegov sledeci bude sledeci od tekuceg. 
     */
    if (tekuci->prethodni != NULL)
        tekuci->prethodni->sledeci = tekuci->sledeci;

    /*
     * Ako postoji sledbenik tekuceg (cvora koji bismo obrisali) 
     * onda njegov prethodnik treba da bude prethodnik tekuceg.
     */
    if (tekuci->sledeci != NULL)
        tekuci->sledeci->prethodni = tekuci->prethodni;

    /*
     * Ako je glava element koji se brise, glava nove liste ce
     * biti sledbenik od stare glave. 
     */
    if (tekuci == *adresa_glave)
        *adresa_glave = tekuci->sledeci;

    /*
     * Oslobadjamo dinamicki alociran prostor za cvor tekuci. 
     */
    free(tekuci);
}



/*
 * Funkcija brise iz liste sve cvorove koji sadrze dati broj.
 * Funkcija azurira pokazivac na glavu liste, koji moze biti
 * promenjen u slucaju da se obrise stara glava. 
 */
void obrisi_element(Cvor ** adresa_glave, int broj)
{
    Cvor *tekuci = *adresa_glave;

    while ((tekuci =
            pretrazi_listu(*adresa_glave, broj)) != NULL)
        obrisi_tekuci(adresa_glave, tekuci);
}


/*
 * Funkcija brise iz liste sve cvorove koji sadrze dati broj,
 * oslanjajuci se na cinjenicu da je prosledjena lista sortirana
 * neopadajuce. Funkcija azurira pokazivac na glavu liste, koji
 * moze biti promenjen ukoliko se obrise stara glava liste. 
 */
void obrisi_element_sortirane_liste(Cvor ** adresa_glave, int
                                    broj)
{
    Cvor *tekuci = *adresa_glave;

    while ((tekuci =
            pretrazi_sortiranu_listu(*adresa_glave,
                                     broj)) != NULL)
        obrisi_tekuci(adresa_glave, tekuci);
}


/*
 * Funkcija prikazuje elemente liste pocev od glave ka kraju
 * liste. Ne saljemo joj adresu promenljive koja cuva glavu
 * liste, jer ova funkcija nece menjati listu, pa nema ni
 * potrebe da azuriza pokazivac na glavu liste iz pozivajuce
 * funkcije. 
 */
void ispisi_listu(Cvor * glava)
{
    putchar('[');
    for (; glava != NULL; glava = glava->sledeci) {
        printf("%d", glava->vrednost);
        if (glava->sledeci != NULL)
            printf(", ");
    }

    printf("]\n");
}

/*
 * Funkcija prikazuje elemente liste pocev od kraja ka glavi
 * liste. Kod dvostruko povezane to je jako jednostavno jer
 * svaki cvor ima pokazivac na prethodni element u listi. 
 */
void ispisi_listu_u_nazad(Cvor * glava)
{
    putchar('[');
    if (glava == NULL) {
        printf("]\n");
        return;
    }

    glava = pronadji_poslednji(glava);

    for (; glava != NULL; glava = glava->prethodni) {
        printf("%d", glava->vrednost);
        if (glava->prethodni != NULL)
            printf(", ");
    }
    printf("]\n");
}
