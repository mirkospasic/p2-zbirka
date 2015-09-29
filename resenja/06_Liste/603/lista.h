#ifndef _LISTA_H
#define _LISTA_H

/* Struktura kojom je predstavljen cvor liste sadrzi celobrojni
   podatak vrednost i pokazivace na sledeci i prethodni cvor liste. */
typedef struct cvor {
  int vrednost;
  struct cvor *sledeci;
  struct cvor *prethodni;
} Cvor;

/* Funkcija kreira cvor, vrednost novog cvora inicijalizuje na broj,
   dok pokazivac na sledeci cvor u novom cvoru postavlja na NULL.
   Funkcija vraca pokazivac na novokreirani cvor ili NULL ako
   alokacija nije uspesno izvrsena. */
Cvor *napravi_cvor(int broj);

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove liste
   ciji se pocetni cvor nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave);

/* Funkcija dodaje novi cvor na pocetak liste. Kreira novi cvor
   koriscenjem funkcije napravi_cvor() i uvezuje ga na pocetak. Vraca 
   1 ukoliko je bilo greske pri alokaciji memorije, inace vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj);

/* Funkcija pronalazi i vraca pokazivac na poslednji cvor liste, ili 
   NULL ukoliko je lista prazna. */
Cvor *pronadji_poslednji(Cvor * glava);

/* Funkcija dodaje broj na kraj liste. Ukoliko dodje do greske pri
   alokaciji memorije vratice 1, inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj);

/* Pomocna funkcija pronalazi cvor u listi iza koga treba umetnuti
   nov cvor sa vrednoscu broj. */
Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj);

/* Funkcija uvezuje cvor novi iza postojeceg cvora tekuci. */
void dodaj_iza(Cvor * tekuci, Cvor * novi);

/* Fukcija dodaje u listu nov cvor na odgovarajuce mesto, tako sto
   pronalazi cvor u listi iza kod treba uvezati nov cvor. Ukoliko
   dodje do greske pri alokaciji memorije vratice 1, inace vraca 0. */
int dodaj_sortirano(Cvor ** adresa_glave, int broj);

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Vraca pokazivac na cvor liste u kome je sadrzan trazeni broj ili
   NULL u slucaju da takav cvor ne postoji u listi. */
Cvor *pretrazi_listu(Cvor * glava, int broj);

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Funkcija se u pretrazi oslanja na cinjenicu da je lista koja se
   pretrazuje neopadajuce sortirana. Vraca pokazivac na cvor liste u
   kome je sadrzan trazeni broj ili NULL u slucaju da takav cvor ne
   postoji u listi.  */
Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj);

/* Funkcija brise u listi na koju pokazuje pokazivac glava onaj cvor
   na koji pokazuje pokazivac tekuci. */
void obrisi_tekuci(Cvor ** adresa_glave, Cvor * tekuci);

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Funkcija azurira pokazivac na glavu liste, koji moze biti
   promenjen u slucaju da se obrise stara glava. */
void obrisi_cvor(Cvor ** adresa_glave, int broj);

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj,
   oslanjajuci se na cinjenicu da je prosledjena lista neopadajuce
   sortirana. Funkcija azurira pokazivac na glavu liste, koji moze
   biti promenjen ukoliko se obrise stara glava liste. */
void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj);

/* Funkcija prikazuje vrednosti cvorova liste pocev od glave ka kraju 
   liste, razdvojene zapetama i uokvirene zagradama. */
void ispisi_listu(Cvor * glava);

/* Funkcija prikazuje cvorove liste pocev od kraja ka glavi liste. */
void ispisi_listu_unazad(Cvor * glava);

#endif
