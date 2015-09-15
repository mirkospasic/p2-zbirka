#include <stdio.h>
#include <stdlib.h>

/* Struktura koja predstavlja cvor liste */
typedef struct cvor {
  /* Podatak koji cvor sadrzi */
  int vrednost;               
  /* Pokazivac na sledeci cvor liste */
  struct cvor *sledeci;   
} Cvor;

/* Pomocna funkcija koja kreira cvor. Funkcija vrednost novog
   cvora inicijalizuje na broj, dok pokazivac na sledeci cvor u 
   novom cvoru postavlja na NULL. 
   Funkcija vraca pokazivac na novokreirani cvor ili NULL ako 
   alokacija nije uspesno izvrsena.  */
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
  if( *adresa_glave == NULL )
    return;

  /* Ako lista nije prazna, memoriju treba osloboditi. Pre nego
     sto oslobodimo memoriju za glavu liste, moramo osloboditi 
     rep liste. */    
  oslobodi_listu( &(*adresa_glave)->sledeci); 
  /* Nakon oslobodjenog repa, oslobadjamo i glavu liste */
  free(*adresa_glave);
  /* Azuriramo glavu u pozivajucoj funkciji tako da odgovara 
     praznoj listi */
  *adresa_glave = NULL;
}

/* Funkcija dodaje novi cvor na pocetak liste. 
   Kreira novi cvor koriscenjem funkcije napravi_cvor i uvezuje 
   ga na pocetak. Funkcija vraca 1 ukoliko je doslo do greske 
   pri alokaciji, inace vraca 0. */
int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreiramo nov cvor i proverimo da li je bilo greske pri 
     alokaciji */
  Cvor *novi = napravi_cvor(broj); 
  if( novi == NULL)
    return 1;   
    
  /* Uvezujemo novi cvor na pocetak */
  novi->sledeci = *adresa_glave;
  /* Nov cvor je sada nova glava liste */
  *adresa_glave = novi;    
  return 0; 
}

/* Funkcija dodaje novi element u rastuce sortiranu listu tako da
   nova lista ostane sortirana. Vraca 0, ako je alokacija novog 
   cvora prosla bez greske, inace vraca 1 da bi ta vrednost bila 
   propagirala nazad do prvog poziva. */
int  dodaj_sortirano(Cvor ** adresa_glave, int broj) 
{
  /* u slucaju prazne liste adresa_glave nove liste je upravo 
     novi cvor */
  if (*adresa_glave == NULL) 
    {
      Cvor *novi = napravi_cvor(broj);
      if( novi == NULL)
	return 1;   

      *adresa_glave = novi;
      return 0 ;
    }

  /* Lista nije prazna*/
  /* Ako je broj manji ili jednak vrednosti u glavi liste, 
     onda u sustini dodajemo na pocetak liste.  */
  if ((*adresa_glave)->vrednost >= broj ) 
    {
      /* Vracamo informaciju o uspesnosti alokacije */
      return dodaj_na_pocetak_liste(adresa_glave, broj); 
    }
    
  /* Inace, element treba dodati u rep, tako da rep i sa novim 
     elementom bude sortirana lista */
  return dodaj_sortirano(&(*adresa_glave)->sledeci, broj);
}


/* Funkcija trazi u listi element cija je vrednost jednaka datom 
   broju. Vraca pokazivac na cvor liste u kome je sadrzan trazeni
   broj ili NULL u slucaju da takav element ne postoji u listi */
Cvor *pretrazi_listu(Cvor * glava, int broj) 
{
  if(glava == NULL || glava->vrednost > broj )
    return NULL;
  
  /* Ako glava liste sadrzi trazeni broj */
  if(glava->vrednost == broj )
    return glava; 

  /* Inace, pretragu nastavljamo u repu */
  return pretrazi_listu(glava->sledeci, broj);
}

/* Funkcija brise iz liste sve cvorove koji sadrze dati broj.
   Funkcija azurira pokazivac na glavu liste (koji moze biti 
   promenjen u slucaju da se obrise stara glava) */
void obrisi_element(Cvor ** adresa_glave, int broj) 
{
  if( *adresa_glave == NULL)
    return ;

  /* Pre nego proverimo situaciju sa glavom liste, obrisacemo sve
     cvorove iz repa koji imaju vrednost bas broj */
  obrisi_element(&(*adresa_glave)->sledeci, broj);
    
  /* Preostaje da proverimo da li glavu treba obrisati. */
  if ( (*adresa_glave)->vrednost == broj ) 
    {
      /* Cvor koji treba da se obrise */
      Cvor* pomocni = *adresa_glave; 
      /* Azuriramo pokazivac na glavu da pokazuje na sledeci u 
         listi i brisemo element koji je do malocas bio glava 
         liste. */
      *adresa_glave = (*adresa_glave)->sledeci; 
      free(pomocni);
    }
}

/* Funkcija ispisuje samo elemente liste razdvojene zapetama */
void ispisi_elemente(Cvor *glava) 
{
  if(glava == NULL)  
    return;
    
  /* Ispisujemo element u glavi liste*/
  printf(" %d",glava->vrednost); 
  /* Rekurzivni poziv za ispis svega ostalo */
  ispisi_elemente(glava->sledeci);  
}

/* Funkcija prikazuje elemente liste pocev od glave ka kraju 
   liste. Ne saljemo joj adresu promenljive koja cuva glavu 
   liste, jer ova funkcija nece menjati listu, pa nema ni potrebe
   da azuriza pokazivac iz pozivajuce funkcije. */
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

  /* Testiramo dodavanje novog broja da lista bude sortirana */
  printf("\nUnosite elemente liste! (za kraj unesite CTRL+D)\n");
  while(scanf("%d",&broj)>0)
    { 
      /* Ako je funkcija vratila 1, bilo je greske pri alokaciji 
         memorije za nov cvor i prethodno alociranu listu moramo
         osloboditi pre napustanja programa. */
      if ( dodaj_sortirano(&glava, broj) == 1) 
        {
	  fprintf(stderr,"Neuspela alokacija za cvor %d\n",broj);
	  oslobodi_listu(&glava);
	  exit(EXIT_FAILURE);
        }
      printf("\n\tLista: ");
      ispisi_listu(glava);
    }

  ispisi_listu(glava);

  printf("\nUnesite element koji se trazi u listi: ");
  scanf("%d", &broj);

  trazeni=pretrazi_listu(glava, broj);
  if( trazeni == NULL)
    printf("Element NIJE u listi!\n");
  else
    printf("Trazeni broj %d je u listi!\n", trazeni->vrednost);

  printf("\nUnesite element koji se brise u listi: ");
  scanf("%d", &broj);

  obrisi_element(&glava, broj);

  printf("Lista nakon brisanja:  ");
  ispisi_listu(glava);

  oslobodi_listu(&glava);

  return 0;
}
