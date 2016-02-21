#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Funkcija objedinjuje dve liste ciji se pokazivaci na glave nalaze
   na adresama adresa_glave_1 i adresa_glave_2 prevezivanjem
   pokazivaca postojecih cvorova listi */
Cvor *objedini(Cvor ** adresa_glave_1, Cvor ** adresa_glave_2)
{
  /* Pokazivaci na pocetne cvorove listi koje se prevezuju */
  Cvor *lista1 = *adresa_glave_1;
  Cvor *lista2 = *adresa_glave_2;

  /* Pokazivac na pocetni cvor rezultujuce liste */
  Cvor *rezultujuca = NULL;
  Cvor *tekuci = NULL;

  /* Ako su obe liste prazne i rezultat je prazna lista */
  if (lista1 == NULL && lista2 == NULL)
    return NULL;

  /* Ako je prva lista prazna, rezultat je druga lista */
  if (lista1 == NULL)
    return lista2;

  /* Ako je druga lista prazna, rezultat je prva lista */
  if (lista2 == NULL)
    return lista1;

  /* Odredjuje se prvi cvor rezultujuce liste - to je ili prvi cvor
     liste lista1 ili prvi cvor liste lista2 u zavisnosti od toga
     koji sadrzi manju vrednost */
  if (lista1->vrednost < lista2->vrednost) {
    rezultujuca = lista1;
    lista1 = lista1->sledeci;
  } else {
    rezultujuca = lista2;
    lista2 = lista2->sledeci;
  }
  /* Kako promenljiva rezultujuca pokazuje na pocetak nove liste, ne
     sme joj se menjati vrednost. Zato se koristi pokazivac tekuci
     koji sadrzi adresu trenutnog cvora rezultujuce liste */
  tekuci = rezultujuca;

  /* U svakoj iteraciji petlje rezultujucoj listi se dodaje novi
     cvor tako da bude uredjena neopadajuce. Pokazivac na listu iz
     koje se uzima cvor se azurira tako da pokazuje na sledeci cvor */
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
     rezultujucu listu treba nadovezati ostatak druge liste */
  if (lista1 == NULL)
    tekuci->sledeci = lista2;
  else
    /* U suprotnom treba nadovezati ostatak prve liste */
    tekuci->sledeci = lista1;

  /* Preko adresa glava polaznih listi vrednosti pokazivaca u
     pozivajucoj funkciji se postavljaju na NULL jer se svi cvorovi
     prethodnih listi nalaze negde unutar rezultujuce liste. Do njih
     se moze doci prateci pokazivace iz glave rezultujuce liste, tako 
     da stare pokazivace treba postaviti na NULL. */
  *adresa_glave_1 = NULL;
  *adresa_glave_2 = NULL;

  return rezultujuca;
}

int main(int argc, char **argv)
{
  /* Argumenti komandne linije su neophodni */
  if (argc != 3) {
    fprintf(stderr,
            "Greska: Program se poziva sa:\n ./a.out dat1.txt dat2.txt\n");
    exit(EXIT_FAILURE);
  }

  /* Otvaraju se datoteke u kojima se nalaze elementi listi */
  FILE *in1 = NULL;
  in1 = fopen(argv[1], "r");
  if (in1 == NULL) {
    fprintf(stderr,
            "Greska: Neuspesno otvaranje datoteke %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  FILE *in2 = NULL;
  in2 = fopen(argv[2], "r");
  if (in2 == NULL) {
    fprintf(stderr,
            "Greska: Neuspesno otvaranje datoteke %s.\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  /* Liste su na pocetku prazne */
  int broj;
  Cvor *lista1 = NULL;
  Cvor *lista2 = NULL;

  /* Ucitavanje listi */
  while (fscanf(in1, "%d", &broj) != EOF)
    dodaj_na_kraj_liste(&lista1, broj);

  while (fscanf(in2, "%d", &broj) != EOF)
    dodaj_na_kraj_liste(&lista2, broj);

  /* Datoteke vise nisu potrebne i treba ih zatvoriti. */
  fclose(in1);
  fclose(in2);

  /* Pokazivac rezultat ce pokazivati na glavu liste dobijene
     objedinjavanjem listi */
  Cvor *rezultat = objedini(&lista1, &lista2);

  /* Ispis rezultujuce liste. */
  ispisi_listu(rezultat);

  /* Lista rezultat dobijena je prevezivanjem cvorova polaznih
     listi. Njenim oslobadjanjem oslobadja se sva zauzeta memorija. */
  oslobodi_listu(&rezultat);

  exit(EXIT_SUCCESS);
}
