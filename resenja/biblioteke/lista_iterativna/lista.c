#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Cvor *napravi_cvor(int broj)
{
  /* Alokacija memorije za novi cvor uz proveru uspesnosti */
  Cvor *novi = (Cvor *) malloc(sizeof(Cvor));
  if (novi == NULL)
    return NULL;

  /* Inicijalizacija polja strukture */
  novi->vrednost = broj;
  novi->sledeci = NULL;

  /* Vracanje adrese novog cvora */
  return novi;
}

void oslobodi_listu(Cvor ** adresa_glave)
{
  Cvor *pomocni = NULL;

  /* Ako lista nije prazna, onda treba osloboditi memoriju */
  while (*adresa_glave != NULL) {
    /* Potrebno je prvo zapamtiti adresu sledeceg cvora i onda
       osloboditi cvor koji predstavlja glavu liste */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);

    /* Sledeci cvor je nova glava liste */
    *adresa_glave = pomocni;
  }
}

int dodaj_na_pocetak_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Novi cvor se uvezuje na pocetak i postaje nova glave liste */
  novi->sledeci = *adresa_glave;
  *adresa_glave = novi;

  /* Vracanje indikatora uspesnog dodavanja */
  return 0;
}

Cvor *pronadji_poslednji(Cvor * glava)
{
  /* U praznoj listi nema cvorova pa se vraca NULL */
  if (glava == NULL)
    return NULL;

  /* Sve dok glava pokazuje na cvor koji ima sledbenika, pokazivac
     glava se pomera na sledeci cvor. Nakon izlaska iz petlje, glava
     ce pokazivati na cvor liste koji nema sledbenika, tj. na
     poslednji cvor liste pa se vraca vrednost pokazivaca glava.
     Pokazivac glava je argument funkcije i njegove promene nece se
     odraziti na vrednost pokazivaca glava u pozivajucoj funkciji. */
  while (glava->sledeci != NULL)
    glava = glava->sledeci;

  return glava;
}

int dodaj_na_kraj_liste(Cvor ** adresa_glave, int broj)
{
  /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Ako je lista prazna */
  if (*adresa_glave == NULL) {
    /* Glava nove liste je upravo novi cvor */
    *adresa_glave = novi;
  } else {
    /* Ako lista nije prazna, pronalazi se poslednji cvor i novi
       cvor se dodaje na kraj liste kao sledbenik poslednjeg */
    Cvor *poslednji = pronadji_poslednji(*adresa_glave);
    poslednji->sledeci = novi;
  }

  /* Vracanje indikatora uspesnog dodavanja */
  return 0;
}

Cvor *pronadji_mesto_umetanja(Cvor * glava, int broj)
{
  /* U praznoj listi nema takvog mesta i vraca se NULL */
  if (glava == NULL)
    return NULL;

  /* Pokazivac glava se pomera na sledeci cvor sve dok ne bude
     pokazivao na cvor ciji sledeci ili ne postoji ili ima vrednost
     vecu ili jednaku vrednosti novog cvora. Zbog izracunavanja
     izraza u C-u prvi deo konjunkcije mora biti provera da li se
     doslo do poslednjeg cvora liste pre nego sto se proveri
     vrednost u sledecem cvoru, jer u slucaju poslednjeg, sledeci ne
     postoji, pa ni njegova vrednost. */
  while (glava->sledeci != NULL && glava->sledeci->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje se moglo izaci pomeranjem pokazivaca glava do
     poslednjeg cvora ili, ranije, nailaskom na cvor ciji sledeci
     ima vrednost vecu od broj. */
  return glava;
}

int dodaj_iza(Cvor * tekuci, int broj)
{
  /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
  Cvor *novi = napravi_cvor(broj);
  if (novi == NULL)
    return 1;

  /* Dodavanje novog cvora iza tekuceg cvora. */
  novi->sledeci = tekuci->sledeci;
  tekuci->sledeci = novi;

  /* Vracanje indikatora uspesnog dodavanja */
  return 0;
}

int dodaj_sortirano(Cvor ** adresa_glave, int broj)
{
  /* Ako je lista prazna */
  if (*adresa_glave == NULL) {
    /* Glava nove liste je novi cvor */
    /* Kreiranje novog cvora uz proveru uspesnost kreiranja */
    Cvor *novi = napravi_cvor(broj);
    if (novi == NULL)
      return 1;

    *adresa_glave = novi;

    /* Vracanje indikatora uspesnog dodavanja */
    return 0;
  }

  /* Inace, ako je broj manji ili jednak vrednosti u glavi liste,
     onda ga treba dodati na pocetak liste. */
  if ((*adresa_glave)->vrednost >= broj) {
    return dodaj_na_pocetak_liste(adresa_glave, broj);
  }

  /* U slucaju da je glava liste cvor sa vrednoscu manjom od broj,
     tada se pronalazi cvor liste iza koga treba uvezati nov cvor */
  Cvor *pomocni = pronadji_mesto_umetanja(*adresa_glave, broj);
  return dodaj_iza(pomocni, broj);
}

Cvor *pretrazi_listu(Cvor * glava, int broj)
{
  /* Obilazenje cvorova liste */
  for (; glava != NULL; glava = glava->sledeci)
    /* Ako je vrednost tekuceg cvora jednaka zadatom broju, pretraga
       se obustavlja */
    if (glava->vrednost == broj)
      return glava;

  /* Nema trazenog broja u listi i vraca se NULL */
  return NULL;
}

Cvor *pretrazi_sortiranu_listu(Cvor * glava, int broj)
{
  /* Obilazenje cvorovi liste */
  /* U uslovu ostanka u petlji, bitan je redosled provera u
     konjunkciji. */
  while (glava != NULL && glava->vrednost < broj)
    glava = glava->sledeci;

  /* Iz petlje se moglo izaci na vise nacina. Prvi, tako sto je
     glava->vrednost veca od trazenog broja i tada treba vratiti
     NULL, jer trazen broj nije nadjen medju manjim brojevima pri
     pocetku sortirane liste, pa se moze zakljuciti da ga nema u
     listi. Drugi nacini, tako sto se doslo do kraja liste i glava
     je NULL ili tako sto je glava->vrednost == broj. U oba
     poslednja nacina treba vratiti pokazivac glava bilo da je NULL
     ili pokazivac na konkretan cvor. */
  if (glava->vrednost > broj)
    return NULL;
  else
    return glava;
}

void obrisi_cvor(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = NULL;
  Cvor *pomocni = NULL;

  /* Sa pocetka liste se brisu svi cvorovi koji su jednaki datom
     broju i azurira se pokazivac na glavu liste */
  while (*adresa_glave != NULL && (*adresa_glave)->vrednost == broj) {
    /* Adresu repa liste treba sacuvati pre oslobadjanja cvora na
       adresi adresa_glave */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }

  /* Ako je nakon ovog brisanja lista ostala prazna, izlazi se iz
     funkcije */
  if (*adresa_glave == NULL)
    return;

  /* Od ovog trenutka, u svakoj iteraciji petlje promenljiva tekuci
     pokazuje na cvor cija je vrednost razlicita od trazenog broja.
     Isto vazi i za sve cvorove levo od tekuceg. Poredi se vrednost
     sledeceg cvora (ako postoji) sa trazenim brojem. Cvor se brise
     ako je jednak, a ako je razlicit, prelazi se na sledeci cvor.
     Ovaj postupak se ponavlja dok se ne dodje do poslednjeg cvora. */
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL)
    if (tekuci->sledeci->vrednost == broj) {
      /* tekuci->sledeci treba obrisati, zbog toga se njegova adresa
         prvo cuva u promenljivoj pomocni. */
      pomocni = tekuci->sledeci;
      /* Tekucem se preusmerava pokazivac sledeci, preskakanjem
         njegovog trenutnog sledeceg. Njegov novi sledeci ce biti
         sledeci od cvora koji se brise. */
      tekuci->sledeci = pomocni->sledeci;
      /* Sada treba osloboditi cvor sa vrednoscu broj. */
      free(pomocni);
    } else {
      /* Inace, ne treba brisati sledeceg od tekuceg i pokazivac se
         pomera na sledeci. */
      tekuci = tekuci->sledeci;
    }
  return;
}

void obrisi_cvor_sortirane_liste(Cvor ** adresa_glave, int broj)
{
  Cvor *tekuci = NULL;
  Cvor *pomocni = NULL;

  /* Sa pocetka liste se brisu svi cvorovi koji su jednaki datom
     broju i azurira se pokazivac na glavu liste. */
  while (*adresa_glave != NULL && (*adresa_glave)->vrednost == broj) {
    /* Adresu repa liste treba sacuvati pre oslobadjanja cvora na
       adresi adresa_glave. */
    pomocni = (*adresa_glave)->sledeci;
    free(*adresa_glave);
    *adresa_glave = pomocni;
  }

  /* Ako je nakon ovog brisanja lista ostala prazna, funkcija se
     prekida. Isto se radi i ukoliko glava liste sadrzi vrednost
     koja je veca od broja, jer kako je lista sortirana rastuce nema 
     potrebe broj traziti u repu liste. */
  if (*adresa_glave == NULL || (*adresa_glave)->vrednost > broj)
    return;

  /* Od ovog trenutka se u svakoj iteraciji pokazivac tekuci
     pokazuje na cvor cija vrednost je manja od trazenog broja, kao
     i svim cvorovima levo od njega. Cvor se brise ako je jednak,
     ili, ako je razlicit, prelazi se na sledeci cvor. Ovaj postupak
     se ponavlja dok se ne dodje do poslednjeg cvora ili prvog cvora
     cija vrednost je veca od trazenog broja. */
  tekuci = *adresa_glave;
  while (tekuci->sledeci != NULL
         && tekuci->sledeci->vrednost <= broj)
    if (tekuci->sledeci->vrednost == broj) {
      pomocni = tekuci->sledeci;
      tekuci->sledeci = tekuci->sledeci->sledeci;
      free(pomocni);
    } else {
      /* Ne treba brisati sledeceg od tekuceg jer je manji od
         trazenog i tekuci se pomera na sledeci cvor. */
      tekuci = tekuci->sledeci;
    }
  return;
}

void ispisi_listu(Cvor * glava)
{
  /* Funkciji se ne salje adresa promenljive koja cuva glavu liste
     jer se lista nece menjati */
  putchar('[');
  /* Unutar zagrada ispisuju se vrednosti u cvorovima liste od
     pocetka prema kraju liste. */
  for (; glava != NULL; glava = glava->sledeci) {
    printf("%d", glava->vrednost);
    if (glava->sledeci != NULL)
      printf(", ");
  }
  printf("]\n");
}
