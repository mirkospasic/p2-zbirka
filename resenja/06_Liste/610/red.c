#include "red.h"

Cvor *napravi_cvor(Zahtev * zahtev)
{
  /* Alocira se memorija za novi cvor liste i proverava uspesnost
     alokacije */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja strukture */
  novi->nalog = *zahtev;
  novi->sledeci = NULL;

  /* Vraca se adresa novog cvora */
  return novi;
}

void oslobodi_red(Cvor ** pocetak, Cvor ** kraj)
{
  Cvor *pomocni = NULL;

  /* Sve dok red nije prazan brise se cvor koji je pocetka reda */
  while (*pocetak != NULL) {
    /* Potrebno je prvo zapamtiti adresu sledeceg cvora i onda
       osloboditi cvor sa pocetka reda */
    pomocni = *pocetak;
    *pocetak = (*pocetak)->sledeci;
    free(pomocni);
  }
  /* Nakon izlaska iz petlje red je prazan. Pokazivac na kraj reda
     treba postaviti na NULL. */
  *kraj = NULL;
}

int dodaj_u_red(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                Zahtev * zahtev)
{
  /* Kreira se novi cvor i proverava se uspesnost kreiranja */
  Cvor *novi = napravi_cvor(zahtev);
  if (novi == NULL)
    return 1;

  /* U red se uvek dodaje na kraj. Zbog postojanja pokazivaca na
     kraj, to je podjednako efikasno kao dodavanje na pocetak liste */
  if (*adresa_kraja != NULL) {
    (*adresa_kraja)->sledeci = novi;
    *adresa_kraja = novi;
  } else {
    /* Ako je red bio ranije prazan */
    *adresa_pocetka = novi;
    *adresa_kraja = novi;
  }

  /* Vraca se indikator uspesnog dodavanja */
  return 0;
}

int skini_sa_reda(Cvor ** adresa_pocetka, Cvor ** adresa_kraja,
                  Zahtev * zahtev)
{
  Cvor *pomocni = NULL;

  /* Ako je red prazan */
  if (*adresa_pocetka == NULL)
    return 0;

  /* Ako je prosledjen pokazivac zahtev, na tu adresu se prepisuje
     zahtev koji je na pocetku reda.  */
  if (zahtev != NULL)
    *zahtev = (*adresa_pocetka)->nalog;

  /* Oslobadja se memorija zauzeta cvorom sa pocetka reda i pokazivac 
     na adresi adresa_pocetka se azurira da pokazuje na sledeci cvor
     u redu. */
  pomocni = *adresa_pocetka;
  *adresa_pocetka = (*adresa_pocetka)->sledeci;
  free(pomocni);

  /* Ukoliko red nakon oslobadjanja pocetnog cvora ostane prazan,
     potrebno je azurirati i vrednost pokazivaca na adresi
     adresa_kraja na NULL */
  if (*adresa_pocetka == NULL)
    *adresa_kraja = NULL;


  return 1;
}

Zahtev *pocetak_reda(Cvor * pocetak)
{
  /* U praznom redu nema zahteva */
  if (pocetak == NULL)
    return NULL;

  /* Inace, vraca se pokazivac na zahtev sa pocetka reda */
  return &(pocetak->nalog);
}

void prikazi_red(Cvor * pocetak)
{
  /* Prikazuje se sadrzaj reda od pocetka prema kraju */
  for (; pocetak != NULL; pocetak = pocetak->sledeci)
    printf("%s %s\n", (pocetak->nalog).jmbg, (pocetak->nalog).opis);

  printf("\n");
}
