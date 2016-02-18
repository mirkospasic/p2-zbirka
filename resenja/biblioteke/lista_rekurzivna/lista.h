#ifndef _LISTA_H_
#define _LISTA_H_

/* Struktura kojom je predstavljen cvor liste sadrzi celobrojni
   podatak vrednost i pokazivac na sledeci cvor liste. */
typedef struct cvor {
  int vrednost;
  struct cvor *sledeci;
} Cvor;

/* Funkcija kreira cvor, vrednost novog cvora inicijalizuje na broj,
   dok pokazivac na sledeci cvor postavlja na NULL. Vraca pokazivac
   na novokreirani cvor ili NULL ako alokacija nije bila uspesna. */
Cvor *napravi_cvor(int broj);

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove liste
   ciji se pokazivac glava nalazi na adresi adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave);

/* Funkcija dodaje novi cvor na pocetak liste. Vraca 1 ukoliko je
   bilo greske pri alokaciji memorije, inace vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj);

/* Funkcija dodaje broj na kraj liste. Vraca 1 ukoliko je bilo
   greske pri alokaciji memorije, inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj);

/* Funkcija dodaje broj u rastuce sortiranu listu tako da nova lista
   ostane sortirana. Vraca 1 ukoliko je bilo greske pri alokaciji
   memorije, inace vraca 0. */
int dodaj_sortirano(Cvor ** adresa_glave, int broj);

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   Vraca pokazivac na cvor liste u kome je sadrzan trazeni broj ili
   NULL u slucaju da takav cvor ne postoji u listi. */
Cvor *pretrazi_listu(Cvor * glava, int broj);

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom broju.
   U pretrazi oslanja se na cinjenicu da je lista koja se pretrazuje
   neopadajuce sortirana. Vraca pokazivac na cvor liste u kome je
   sadrzan trazeni broj ili NULL u slucaju da takav cvor ne postoji. */
Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj);

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Azurira pokazivac na glavu liste, koji moze biti promenjen u
   slucaju da se obrise stara glava liste. */
void obrisi_cvor(Cvor ** adresa_glave, int broj);

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj,
   oslanjajuci se na cinjenicu da je prosledjena lista sortirana
   neopadajuce. Azurira pokazivac na glavu liste, koji moze biti
   promenjen ukoliko se obrise stara glava liste. */
void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj);

/* Funkcija ispisuje samo vrednosti cvorova liste razdvojene
   zapetama. */
void ispisi_vrednosti(Cvor * glava);

/* Funkcija prikazuje vrednosti cvorova liste pocev od glave ka
   kraju liste, razdvojene zapetama i uokvirene zagradama. */
void ispisi_listu(Cvor * glava);

#endif
