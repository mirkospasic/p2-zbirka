#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

/* NAPOMENA: Primer demonstrira "vracanje nizova iz funkcije". 
   Ovako nesto se može improvizovati tako sto se u funkciji 
   dinamicki kreira niz potrebne velicine, popuni se potrebnim
   informacijama, a zatim se vrati njegova adresa. Imajuci u 
   vidu cinjenicu da dinamicki kreiran objekat ne nestaje 
   kada se izadje iz funkcije koja ga je kreirala, vraceni 
   pokazivac se kasnije u pozivajucoj funkciji može koristiti 
   za pristup "vracenom" nizu. Medjutim, pozivajuca funkcija 
   ima odgovornost i da se brine o dealokaciji istog prostora */

/* Funkcija dinamicki kreira niz karaktera u koji smesta 
   rezultat nadovezivanja niski. Adresa niza se vraca kao 
   povratna vrednost. */
char *nadovezi(char *s, char *t) {
  /* Dinamicki kreiramo prostor dovoljne velicine */
  char *p = (char *) malloc((strlen(s) + strlen(t) + 1) 
                                           * sizeof(char));

  /* Proveravamo uspeh alokacije */
  if (p == NULL) {
    fprintf(stderr, "malloc(): ");
    fprintf(stderr, "greska pri alokaciji memorije.\n");	
    exit(EXIT_FAILURE);
  }

  /* Kopiramo i nadovezujemo stringove */
    
  /* Resenje bez koriscenja biblioteckih funkcija */
  /* 
  int i,j;
  for(i=j=0; s[j]!='\0'; i++, j++)
    p[i]=s[j];

  for(j=0; t[j]!='\0'; i++, j++)
    p[i]=t[j];

  p[i]='\0';
  */

  /* Resenje sa koriscenjem biblioteckih funkcija iz zaglavlja 
     string.h */
  strcpy(p, s);
  strcat(p, t);
	
  /* Vracamo pokazivac p */
  return p;
}

int main() {
  char *s = NULL;
  char s1[MAX], s2[MAX];

  /* Ucitavamo dve niske koje cemo da nadovežemo */
  scanf("%s", s1);
  scanf("%s", s2);

  /* Pozivamo funkciju da nadoveže stringove */
  s = nadovezi(s1, s2);

  /* Prikazujemo rezultat */
  printf("%s\n", s);

  /* Oslobadjamo memoriju alociranu u funkciji nadovezi() */
  free(s);

  return 0;
}

