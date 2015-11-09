#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/* Funkcija objedinjuje dve liste ciji se pokazivaci na glave nalaze
   na adresama adresa_glave_1 i adresa_glave_2 prevezivanjem
   pokazivaca postojecih cvorova tih listi. */
Cvor *objedini(Cvor ** adresa_glave_1, Cvor ** adresa_glave_2)
{
  /* Pokazivace na pocetne cvorove listi koje se prevezuju */
  Cvor *lista1 = *adresa_glave_1;
  Cvor *lista2 = *adresa_glave_2;
  /* Pokazivac na pocetni cvor rezultujuce liste */
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

  /* Preko adresa glavi polaznih listi vrednosti pokazivaca u
     pozivajucoj funkciji se postavljaju na NULL, jer se svi cvorovi
     prethodnih listi nalaze negde unutar rezultujuce liste. Do njih
     se moze doci prateci pokazivace iz glave rezultujuce liste, tako 
     da stare pokazivace treba postaviti na NULL. */
  *adresa_glave_1 = NULL;
  *adresa_glave_2 = NULL;

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

  /* Lista rezultat dobijena je prevezivanjem cvorova polaznih listi.
     Njenim oslobadjanjem bice oslobodjena sva zauzeta memorija. */
  oslobodi_listu(&rezultat);

  return 0;
}
