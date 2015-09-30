#include<stdio.h>
#include<stdlib.h>
#include "601/lista.h"

/* Funkcija objedinjuje dve liste ciji se pokazivaci na glave nalaze
   na adresama adresa_glave_1 i adresa_glave_2 prevezivanjem
   pokazivaca postojecih cvorova listi. */
Cvor *objedini(Cvor ** adresa_glave_1, Cvor ** adresa_glave_2)
{
  /* Pokazivac na glavu rezultujuce liste. */
  Cvor *rezultujuca = NULL;
  /* Tekuci je pokazivac na pokazivac kome sledecem treba promeniti
     vrednosti. Inicijalizuje se na adresu pokazivaca rezultujuca jer 
     prvo treba odrediti glavu rezultujuce liste. */
  Cvor **tekuci = &rezultujuca;

  /* Ako su obe liste prazne, rezultat je isto prazna lista. */
  if (*adresa_glave_1 == NULL && *adresa_glave_2 == NULL)
    return NULL;

  /* Ako je prva lista prazna, rezultat je druga lista. */
  if (*adresa_glave_1 == NULL)
    return *adresa_glave_2;

  /* Ako je druga lista prazna, rezultat je prva lista. */
  if (*adresa_glave_2 == NULL)
    return *adresa_glave_1;

  /* Sve dok u obe liste ima cvorova, azurira se vrednost pokazivaca
     na koji tekuci pokazuje. U prvoj iteraciji tekuci pokazuje na
     pokazivac rezultujuca i ovako se pokazivac rezultujuca usmerava
     da pokazuje na pocetak nove liste, tj. na cvor sa vrednoscu
     manjeg od brojeva sadrzanih u cvorovima na koje vode pokazivaci
     na adresama adresa_glave_1 i adresa_glave_2. U svim ostalim
     iteracijama to isto se dogadja samo pokazivacu na koji tekuci u
     tom trenutku pokazuje. */
  while (*adresa_glave_1 != NULL && *adresa_glave_2 != NULL) {
    if ((*adresa_glave_1)->vrednost < (*adresa_glave_2)->vrednost) {
      /* Pokazivac na koji tekuci pokazuje dobija vrednosti
         pokazivaca koji se nalazi na adresa_glave_1. Time sledbenik
         poslednjeg uvezanog cvora postaje cvor koji je aktuelna
         glava prve liste. */
      *tekuci = *adresa_glave_1;
      /* Pomera se glava prve liste na sledeci cvor prve liste.

         Ova promena bice vidljiva i van funkcije jer se direktno
         menja promenljiva koja se nalazi na adresi adresa_glave_1. */
      *adresa_glave_1 = (*adresa_glave_1)->sledeci;
    } else {
      /* Sledbenik poslednjeg uvezanog cvora bice cvor koji je
         aktuelna glava druge liste. */
      *tekuci = *adresa_glave_2;
      /* Pomera se glava druge liste na sledeci cvor druge liste */
      *adresa_glave_2 = (*adresa_glave_2)->sledeci;
    }
    /* Tekuci se pomera na pokazivac sledeci od poslednjeg uvezanog,
       jer je upravo to pokazivac koji treba da bude azuriran u
       sledecoj iteraciji petlje. */
    tekuci = &((*tekuci)->sledeci);
  }

  /* Ako se iz petlje izaslo jer se stiglo do kraja prve liste, na
     rezultujucu listu treba nadovezati ostatak druge liste. Tako
     sledbenik poslednjeg uvezanog cvora treba da bude ostatak druge
     liste. */
  if (*adresa_glave_1 == NULL)
    *tekuci = *adresa_glave_2;
  else {
    if (*adresa_glave_2 == NULL)
      *tekuci = *adresa_glave_1;
  }

  return rezultujuca;
}

/* Druga verzija prethodne funkcije koja ne pristupa pokazivacima
   preko adresa vec direktno. Ne salju joj se adrese, vec vrednosti
   pokazivaca na glave listi. */
Cvor *objedini_v2(Cvor * lista1, Cvor * lista2)
{
  Cvor *rezultujuca = NULL;
  Cvor *tekuci = NULL;

  /* Ako su obe liste prazne i rezultat je prazna lista. */
  if (lista1 == NULL && lista2 == NULL)
    return NULL;

  /* Ako je prva lista prazna, rezultat je druga lista. */
  if (lista1 == NULL)
    return lista2;

  /* Ako je druga lista prazna, rezultat je prva lista. */
  if (lista2 == NULL)
    return lista1;

  /* Rezultujuca pokazuje na pocetak nove liste, tj. na cvor sa
     vrednoscu manjeg od brojeva sadrzanih u cvorovima na koje
     pokazuju lista1 i lista2. */
  if (lista1->vrednost < lista2->vrednost) {
    rezultujuca = lista1;
    lista1 = lista1->sledeci;
  } else {
    rezultujuca = lista2;
    lista2 = lista2->sledeci;
  }
  tekuci = rezultujuca;

  /* Kako rezultujuca pokazuje na pocetak nove liste i ne sme joj se
     menjati vrednost, koristi se pokazivac tekuci koji trenutno
     sadrzi adresu promenljive rezultujuca. U svakoj iteraciji
     petlje, dobijace adekvatnog sledbenika tako da i nova lista bude
     uredjena neopadajuce i pomerace se na adresu sledeceg. */
  while (lista1 != NULL && lista2 != NULL) {
    if (lista1->vrednost < lista2->vrednost) {
      tekuci->sledeci = lista1;
      lista1 = lista1->sledeci;
    } else {
      tekuci->sledeci = lista2;
      lista2 = lista2->sledeci;
    }
    tekuci = tekuci->sledeci;
  }

  /* Ako se iz petlje izaslo jer se stiglo do kraja prve liste, na
     rezultujucu listu treba nadovezati ostatak druge liste. */
  if (lista1 == NULL)
    tekuci->sledeci = lista2;
  else
    tekuci->sledeci = lista1;

  return rezultujuca;
}

/* Glavni program */
int main(int argc, char **argv)
{
  /* Argumenti komandne linije su neophodni. */
  if (argc != 3) {
    fprintf(stderr,
            "Program se poziva sa: ./a.out dat1.txt dat2.txt\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaramo datoteke sa elementima obe liste. */
  FILE *in1 = NULL;
  in1 = fopen(argv[1], "r");
  if (in1 == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  FILE *in2 = NULL;
  in2 = fopen(argv[2], "r");
  if (in2 == NULL) {
    fprintf(stderr,
            "Greska prilikom otvaranja datoteke %s.\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  int broj;
  Cvor *lista1 = NULL;
  Cvor *lista2 = NULL;
  Cvor *rezultat = NULL;

  /* Ucitavanje listi */
  while (fscanf(in1, "%d", &broj) != EOF)
    dodaj_na_kraj_liste(&lista1, broj);
  while (fscanf(in2, "%d", &broj) != EOF)
    dodaj_na_kraj_liste(&lista2, broj);

  /* Pokazivac rezultat ce pokazivati na glavu liste koja se dobila
     objedinjavanjem listi */
  rezultat = objedini(&lista1, &lista2);

 /***************************************************************** 
  Poziv druge verzije prethodne funkcije
  
  rezultat = objedini_v2(lista1, lista2);
  *****************************************************************/

  /* Ispis rezultujuce liste. */
  ispisi_listu(rezultat);

  /* Kako je lista rezultat dobijena prevezivanjem cvorova polaznih
     listi, njenim oslobadjanjem bice oslobodjena sva zauzeta
     memorija. */
  oslobodi_listu(&rezultat);

  fclose(in1);
  fclose(in2);
  return 0;
}
