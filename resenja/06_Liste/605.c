#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

#define OTVORENA 1
#define ZATVORENA 2

#define VAN_ETIKETE 0
#define PROCITANO_MANJE 1
#define U_ETIKETI 2


/* Struktura kojim se predstavlja cvor liste sadrzi ime etikete 
   i pokazivac na sledeci cvor. */
typedef struct cvor {
    char etiketa[MAX];
    struct cvor * sledeci;
} Cvor;
    /* Funkcija kreira novi cvor, upisuje u njega etiketu i
       vraca njegovu adresu ili NULL ako alokacija nije bila
       uspesna. */
Cvor * napravi_cvor(char *etiketa)
{
    Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
    if (novi == NULL)
        return NULL;
    
    /* Inicijalizacija polja u novom cvoru */
    if (strlen(etiketa) >= MAX) {
        fprintf(stderr, 
                "Etiketa koju pokusavamo staviti na stek preduga, 
bice skracena .\n");
        etiketa[MAX - 1] = '\0';
    }
    strcpy(novi->etiketa, etiketa);
    novi->sledeci = NULL;
    return novi;
}

/* Funkcija prazni stek */
void oslobodi_stek(Cvor ** adresa_vrha)
{
    Cvor *pomocni;
    while (*adresa_vrha != NULL) {
        pomocni = *adresa_vrha;
        *adresa_vrha = (*adresa_vrha)->sledeci;
        free(pomocni);
    }
}

/* Funkcija proverava uspesnost alokacije memorije za cvor novi i
   ukoliko alokacija nije bila uspesna, oslobadja se sva
   prethodno zauzeta memorija za listu cija pocetni cvor se 
   nalazi na adresi adresa_vrha.*/
void proveri_alokaciju(Cvor ** adresa_vrha, Cvor * novi)
{
    if (novi == NULL) {
        fprintf(stderr, "Neuspela alokacija za nov cvor\n");
        oslobodi_stek(adresa_vrha);    
        exit(EXIT_FAILURE);
    }
}

/* Funkcija postavlja na vrh steka novu etiketu. */
void potisni_na_stek(Cvor ** adresa_vrha, char *etiketa)
{
    Cvor *novi = napravi_cvor(etiketa);
    proveri_alokaciju(adresa_vrha, novi);
    novi->sledeci = *adresa_vrha;
    *adresa_vrha = novi;
}

/* Funkcija skida sa vrha steka etiketu. Ako je drugi argument
   pokazivac razlicit od NULL, tada u niz karaktera na koji on
   pokazuje upisuje ime etikete koja je upravo skinuta sa steka
   dok u suprotnom ne radi nista.
   Funkcija vraca 0 ako je stek prazan (pa samim tim nije bilo
   moguce skinuti vrednost sa steka) ili 1 u suprotnom. */
int skini_sa_steka(Cvor ** adresa_vrha, char * etiketa)
{
    Cvor * pomocni;
    
    /* Pokusavamo da skinemo vrednost sa vrha praznog steka i
       imamo gresku. */
    if (*adresa_vrha == NULL)
        return 0;
    
    /* Ako adresa na koju zelimo da smestamo etiketu nije NULL
       kopiramo tamo etiketu sa vrha steka. */
    if (etiketa != NULL)
        strcpy(etiketa, (*adresa_vrha)->etiketa);
    
    /* Skidamo element sa vrha steka. */
    pomocni = *adresa_vrha;
    *adresa_vrha = (*adresa_vrha)->sledeci;
    free(pomocni);
    
    return 1;
}

/* Funkcija vraca pokazivac na string koji sadrzi etiketu na vrhu
   steka. Ukoliko je stek prazan, vraca NULL. */
char *vrh_steka(Cvor * vrh)
{
    if (vrh == NULL)
        return NULL;
    return vrh->etiketa;
}

/* Funkcija prikazuje stek pocev od vrha prema dnu. */
void prikazi_stek(Cvor * vrh)
{
    for (; vrh != NULL; vrh = vrh->sledeci)
        printf("<%s>\n", vrh->etiketa);
}

/* Funkcija iz fajla na koji pokazuje f cita sledecu etiketu, i 
   njeno ime upisuje u niz na koji pokazuje pokazivac etiketa.
   Funkcija vraca EOF u slucaju da se dodje do kraja fajla pre
   nego sto se procita etiketa, vraca OTVORENA ako je procitana
   otvorena etiketa, odnosno ZATVORENA ako je procitana zatvorena
   etiketa. */
int uzmi_etiketu(FILE * f, char *etiketa)
{
    int c;    
    int i = 0;
   
     
    /* Stanje predstavlja informaciju dokle smo stali sa citanjem
       etikete inicijalno smo ga postavili na vrednost 
       VAN_ETIKETE jer jos uvek nismo poceli da citamo.
       Tip predstavlja informaciju o tipu etikete uzima vrednosti
       OTVORENA ili ZATVORENA. */
    int stanje = VAN_ETIKETE;
    int tip;
    
    /* HTML je neosetljiv na razliku izmedju malih i velikih 
       slova. U HTML-u etikete BODY i body imaju isto znacenje, 
       dok to u C-u ne vazi. Zato cemo sve etikete prevoditi 
       u zapis samo malim slovima. */
    while ((c = fgetc(f)) != EOF) {
        switch (stanje) {
        case VAN_ETIKETE:
            if (c == '<')
                stanje = PROCITANO_MANJE;
            break;
        case PROCITANO_MANJE:
            if (c == '/') {
                /* Citamo zatvarac */
                tip = ZATVORENA;
            } else {
                if (isalpha(c)) {
                    /* Citamo otvarac */
                    tip = OTVORENA;
                    etiketa[i++] = tolower(c);
                }
            }
            /* Sada citamo etiketu i zato menjamo stanje. */
            stanje = U_ETIKETI;
            break;
        case U_ETIKETI:
            if (isalpha(c) && i < MAX - 1) {
                /* Ako je procitani karakter slovo i nismo 
                   premasili maksimalnu dozvoljenu duzinu za
                   etiketu, smestamo procitani karakter u
                   etiketu. */
                etiketa[i++] = tolower(c);
            } else {
                stanje = VAN_ETIKETE;
                /* U suprotnom, prestajemo sa citanjem etikete i
                   menjamo stanje. */
                etiketa[i] = '\0';
                /* Zavrsili smo sa citanjem etikete i vracamo tip
                   etikete koju smo procitali, a ona nam je 
                   sacuvana u nisci etiketa. */
                return tip;
            }
            break;
        }
    }
    
    /* Dosli smo do kraja datoteke pre nego sto smo zavrsili sa 
       citanjem etikete, stoga imamo gresku i vracamo EOF. */
    return EOF;
}

int main(int argc, char **argv)
{
    /* Stek nam je prazan na pocetku. */
    Cvor *vrh = NULL;
    char etiketa[MAX];
    int tip;
    /* Na pocetku su nam etikete upare, jer nismo nijednu jos 
       procitali. */
    int uparene = 1;
    FILE *f = NULL;
    /* Ime datoteke dobijamo iz komandne linije. */
    if (argc < 2) {
        fprintf(stderr, "Koriscenje: %s ime_html_datoteke\n",
                argv[0]);
        exit(0);
    }
    
    /* Otvaramo datoteku. */
    if ((f = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "fopen() greska!\n");
        exit(1);
    }
    /* Dokle god ima etiketa, uzimamo ih jednu po jednu sa
       ulaza.*/
    while ((tip = uzmi_etiketu(f, etiketa)) != EOF) {
        /* Ako je otvorena etiketa, dodajemo je na stek.
           Izuzetak su etikete <br>, <hr> i <meta> koje nemaju 
           sadrzaj, tako da ih nije potrebno zatvoriti. 
           NAPOMENA: 
           U html-u postoje jos neke etikete koje koje nemaju 
           sadrzaj (npr link). Pretpostavimo da njih nema u 
           dokumentu, zbog jednostavnosti. */
        if (tip == OTVORENA) {
            if (strcmp(etiketa, "br") != 0
                && strcmp(etiketa, "hr") != 0
                && strcmp(etiketa, "meta") != 0)
                potisni_na_stek(&vrh, etiketa);
        }
        /* Ako je zatvorena etiketa, tada je uslov dobre
           uparenosti da je u pitanju zatvaranje etikete koja je
           poslednja otvorena, a jos uvek nije zatvorena. Ova
           etiketa se mora nalaziti na vrhu steka. Ako je taj 
           uslov ispunjen, tada je skidamo sa steka, jer je 
           zatvorena. U suprotnom, obavestavamo  korisnika da 
           etikete nisu pravilno uparene. */
        else if (tip == ZATVORENA) {
            if (vrh_steka(vrh) != NULL
                && strcmp(vrh_steka(vrh), etiketa) == 0)
                skini_sa_steka(&vrh, NULL);
            else {
                printf(vrh_steka(vrh) !=
                       NULL ?
                       "Etikete nisu pravilno uparene\n(nadjena\
etiketa </%s> a poslednja otvorena etiketa je <%s>)\n" : \
"Etikete nisu pravilno uparene\n(nadjena etiketa </%s> koja nije\
otvorena)\n", etiketa, vrh_steka(vrh));
                uparene = 0;
                break;
            }
        }
    }
    /* Zatvaramo datoteku. */
    fclose(f);
    /* Ako nismo pronasli pogresno uparivanje do sada, stek 
       treba da bude prazan. Ako nije, tada znaci da postoje jos 
       neke etikete koje su otvorene ali nisu bile zatvorene. */
    if (uparene) {
        if (vrh_steka(vrh) == NULL)
            printf("Etikete su pravilno uparene!\n");
        else
            printf("Etikete nisu pravilno uparene\n(etiketa <%s> 
nije zatvorena)\n", vrh_steka(vrh));
    }
    
    /* Oslobadjamo memoriju alociranu za stek, ukoliko vec nije.
     */
    oslobodi_stek(&vrh);
    return 0;
}
