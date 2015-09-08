#include <stdio.h>
#include <stdlib.h>
#define  MAX_DUZINA_NIZA 50

void ispisiNiz(int a[], int n){
    int i;

    for(i=1;i<=n;i++)
        printf("%d ", a[i]);
    printf("\n");
}

/* Funkcija proverava da li se x vec 
nalazi u permutaciji na prethodnih 1...n mesta*/
int koriscen(int a[], int n, int x){
    int i;
    for(i=1; i<=n; i++)
        if(a[i] == x) return 1;

    return 0;
}

/* F-ja koja ispisuje sve permutacije od skupa {1,2,...,n} 
 * a[] je niz u koji smesta permutacije
 * m - oznacava da se na m-tu poziciju u permutaciji 
 *        smesta jedan od preostalih celih brojeva
 * n- je velicina skupa koji se permutuje
 * Funkciju pozivamo sa argumentom m=1 jer krecemo da 
 * formiramo permutaciju od 1. pozicije i nikada 
 * ne koristimo a[0].
 */ 
void permutacija(int a[], int m, int n){
    int i;

  /* Izlaz iz rekurzije:
 * Ako je pozicija na koju treba smestiti broj premasila
 * velicinu skupa, onda se svi brojevi vec nalaze u 
 * permutaciji i ispisujemo permutaciju. */
    if(m>n) {
        ispisiNiz(a,n); 
        return; 
    }
    
    /*Ideja: pronalazimo prvi broj koji mozemo da 
    postavimo na m-to mesto u nizu (broj koji se do 
    sada nije pojavio u permutaciji). Zatim, rekurzivno 
    pronalazimo one permutacije koje odgovaraju 
    ovako postavljenom pocetku permutacije. 
    Kada to zavrsimo, proveravamo da li postoji jos neki
	broj koji moze da se stavi na m-to mesto u nizu 
    (to se radi u petlji). Ako 
    ne postoji, funkcija je zavrSila sa radom. 
	Ukoliko takav broj postoji, onda ponovo pozivamo 
	rekurzivno pronalazenje odgovarajucih permutacija, 
	ali sada sa drugacije postavljenim prefiksom. */
    
        
    for(i=1;i<=n;i++){
        /* Ako se broj i nije do sada pojavio u permutaciji 
         * od 1 do m-1 pozicije, onda ga stavljamo na poziciju m 
         * i pozivamo funkciju da napravi permutaciju za jedan 
         * vece duzine, tj. m+1. Inace, nastavljamo dalje, trazeci
         * broj koji se nije pojavio do sada u permutaciji.
         */
        if(! koriscen(a,m-1,i)) {
            a[m]=i;
            /* Pozivamo ponovo funkciju da dopuni ostatak 
             * permutacije posle upisivanja i na poziciju m.
             */
            permutacija(a,m+1,n);
        }
    }
}

int main(void) {
    int n;
    int a[MAX_DUZINA_NIZA];

    printf("Unesite duzinu permutacije: ");
    scanf("%d", &n);
    if ( n < 0 ||  n >= MAX_DUZINA_NIZA) {
        fprintf(stderr, "Duzina permutacije mora biti broj veci od 0 i manji od %d!\n", MAX_DUZINA_NIZA);
        exit(EXIT_FAILURE);      
    }

    permutacija(a,1,n);

    exit(EXIT_SUCCESS);
}