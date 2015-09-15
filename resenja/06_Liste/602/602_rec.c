/* Resenje sa rekurzivnim funkcijama. */
#include <stdio.h>
#include <stdlib.h>

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
Cvor * napravi_cvor(int broj) 
{
  Cvor * novi = (Cvor *) malloc(sizeof(Cvor));
  if( novi == NULL )
    return NULL;

  /* Inicijalizacija polja u novom cvoru */
  novi->vrednost = broj;
  novi->sledeci = NULL;
  return novi;
}

/* Funkcija oslobadja dinamicku memoriju zauzetu za elemente 
   liste ciji se pocetni cvor nalazi na adresi *adresa_glave. */
void oslobodi_listu(Cvor ** adresa_glave) 
{
  /* Lista je prazna */
  if( *adresa_glave == NULL )
    return;

  /* Ako lista nije prazna, treba osloboditi memoriju. */  
  oslobodi_listu( &(*adresa_glave)->sledeci); 
  /* Nakon oslobodjenog repa, oslobadjamo i glavu liste */
  free(*adresa_glave);
  /* Azuriramo glavu u pozivajucoj funkciji tako da odgovara
     praznoj listi */
  *adresa_glave = NULL;
}

/* Funkcija pronalazi i vraca pokazivac na poslednji element 
   liste, ili NULL kao je lista prazna. */
Cvor* pronadji_poslednji (Cvor* glava) 
{
  /* Prazna lista nema ni poslednji cvor i zato vracamo NULL.*/
  if( glava == NULL)
    return NULL;
    
  /* Ako je glava liste takva da nema sledeceg, onda je ona 
     poslednji element */
  if( glava -> sledeci == NULL )
    return glava;
    
  /* Inace, trazimo poslednjeg u repu
     liste. */
  return pronadji_poslednji(glava->sledeci);
}


/* Funkcija dodaje novi cvor na kraj liste.
   Prilikom dodavanja u listu na kraj u velikoj vecini slucajeva
   nov broj se dodaje u rep liste u rekurzivnom pozivu. 
   U slucaju da je u rekurzivnom pozivu doslo do greske pri 
   alokaciji, funkcija vraca 1 visem rekurzivnom pozivu koji tu
   informaciju vraca u rekurzivni poziv iznad, sve dok se ne 
   vrati u main. Ako je funkcija vratila 0, onda nije bilo 
   greske. Tek je iz main funkcije moguce pristupiti pravom 
   pocetku liste i osloboditi je celu, ako ima potrebe. */
int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj) 
{
  if (*adresa_glave == NULL) 
    {
      /* Glava liste je upravo novi cvor i ujedno i cela lista.*/
      Cvor *novi = napravi_cvor(broj);
      if( novi == NULL)
	return 1;
        
      /* Azuriramo vrednost na koju pokazuje adresa_glave i tako 
         azuriramo i pokazivacku promenljivu u pozivajucoj 
         funkciji. */
      *adresa_glave = novi; 
      return 0;
    }

  /* Ako lista nije prazna, nov element se dodaje u rep liste. */
  return  dodaj_na_kraj_liste(&(*adresa_glave)->sledeci, broj);
}

/* Funkcija ispisuje samo elemente liste razdvojene zapetama */
void ispisi_elemente(Cvor *glava) 
{
  /* Prazna lista*/
  if(glava == NULL)  
    return;
    
  /* Ispisujemo element u glavi liste*/
  printf(" %d",glava->vrednost); 
  /* Rekurzivni poziv za ispis svega ostalo */
  ispisi_elemente(glava->sledeci);  
}

/* Funkcija prikazuje elemente liste pocev od glave ka kraju 
   liste. Ne saljemo joj adresu promenljive koja cuva glavu 
   liste, jer ova funkcija nece menjati listu. */
void ispisi_listu(Cvor * glava)
{
  putchar('[');
  ispisi_elemente(glava);
  putchar(']');

  putchar('\n');
}

/* Glavni program */
int main() 
{
  /* Lista je prazna na pocetku. */
  Cvor *glava = NULL; 
  Cvor *trazeni = NULL;
  int broj;

  /* Testiramo dodavanje na kraj liste*/
  printf("\nUnosite elemente liste! (za kraj unesite CTRL+D)\n");
  while(scanf("%d",&broj)>0)
    { 
      /* Ako je funkcija vratila 1 onda je bilo greske pri 
         alokaciji memorije za nov cvor i prethodno alociranu 
         listu moramo osloboditi pre napustanja programa. */
      if ( dodaj_na_kraj_liste(&glava, broj) == 1) 
        {
	  fprintf(stderr,"Neuspela alokacija za cvor %d\n",broj);
	  oslobodi_listu(&glava);
	  exit(EXIT_FAILURE);
        }
      printf("\n\tLista: ");
      ispisi_listu(glava);
    }

  ispisi_listu(glava);
  oslobodi_listu(&glava);

  return 0;
}
