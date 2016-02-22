#ifndef _DVOSTRUKO_POVEZANA_LISTA_H_
#define _DVOSTRUKO_POVEZANA_LISTA_H_

/* Struktura kojom je predstavljen cvor liste sadrzi celobrojnu
   vrednost i pokazivace na sledeci i prethodni cvor liste. */
typedef struct cvor {
  int vrednost;
  struct cvor *sledeci;
  struct cvor *prethodni;
} Cvor;

/* Funkcija kreira cvor, vrednost novog cvora inicijalizuje na
   broj, dok pokazivac na sledeci cvor postavlja na NULL. Vraca
   pokazivac na novokreirani cvor ili NULL ako alokacija nije bila
   uspesna. */
Cvor *napravi_cvor(int broj);

/* Funkcija oslobadja dinamicku memoriju zauzetu za cvorove liste
   ciji se pocetni cvor nalazi na adresi adresa_glave, a poslednji
   na adresi adresa_kraja. */
void oslobodi_listu(Cvor ** adresa_glave, Cvor ** adresa_kraja);

/* Funkcija dodaje novi cvor na pocetak liste. Vraca 1 ukoliko je
   bilo greske pri alokaciji memorije, inace vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, Cvor **
                           adresa_kraja, int broj);

/* Funkcija dodaje broj na kraj liste. Vraca 1 ukoliko je bilo
   greske pri alokaciji memorije, inace vraca 0. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, Cvor ** adresa_kraja,
                        int broj);

/* Pomocna funkcija pronalazi cvor u listi iza koga treba umetnuti
   novi cvor sa vrednoscu broj. */
Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj);

/* Funkcija dodaje broj iza zadatog cvora. Vraca 1 ukoliko je
   dodavanje uspesno, odnosno 0 ukoliko je doslo do greske. */
int dodaj_iza(Cvor * tekuci, int broj);

/* Funkcija dodaje broj u sortiranu listu tako da lista ostane
   sortirana. Vraca 1 ukoliko je bilo greske pri alokaciji
   memorije, inace vraca 0. */
int dodaj_sortirano(Cvor ** adresa_glave, Cvor ** adresa_kraja, int
                    broj);

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom
   broju. Vraca pokazivac na cvor liste u kome je sadrzan trazeni
   broj ili NULL u slucaju da takav cvor ne postoji u listi. */
Cvor *pretrazi_listu(Cvor * glava, int broj);

/* Funkcija trazi u listi cvor cija je vrednost jednaka datom
   broju. U pretrazi oslanja se na cinjenicu da je lista koja se
   pretrazuje neopadajuce sortirana. Vraca pokazivac na cvor liste
   koji sadrzi trazeni broj ili NULL u slucaju da takav cvor ne
   postoji. */
Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj);

/* Funkcija brise cvor na koji pokazuje pokazivac tekuci u listi
   ciji pokazivac glava se nalazi na adresi adresa_glave. */
void obrisi_tekuci(Cvor ** adresa_glave, Cvor ** adresa_kraja,
                   Cvor * tekuci);

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Azurira pokazivac na glavu liste, koji moze biti promenjen u
   slucaju da se obrise stara glava. */
void obrisi_cvor(Cvor ** adresa_glave, Cvor ** adresa_kraja, int
                 broj);

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj,
   oslanjajuci se na cinjenicu da je prosledjena lista neopadajuce
   sortirana. Azurira pokazivac na glavu liste, koji moze biti
   promenjen ukoliko se obrise stara glava liste. */
void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, Cvor **
                                 adresa_kraja, int broj);

/* Funkcija prikazuje vrednosti cvorova liste pocev od glave ka
   kraju liste, razdvojene zapetama i uokvirene zagradama. */
void ispisi_listu(Cvor * glava);

/* Funkcija prikazuje vrednosti cvorova liste pocevsi od kraja ka
   glavi liste, razdvojene zapetama i uokvirene zagradama. */
void ispisi_listu_unazad(Cvor * kraj);

#endif
