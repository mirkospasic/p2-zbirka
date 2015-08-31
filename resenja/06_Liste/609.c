/* Sadrzaj datoteke je aritmeticki izraz koji moze sadrzati zagrade {,
   [ i (. Napisati program koji ucitava sadrzaj datoteke i koriscenjem
   steka utvrdjuje da li su zagrade u aritmetickom izrazu dobro
   uparene. Program stampa odgovarajucu poruku na standardni izlaz.

   Datoteka: {[23 + 5344] * (24 - 234)} - 23       Izlaz: ispravno
   Datoteka: {[23 + 5] * (9 * 2)} - {23} 	   Izlaz: ispravno
   Datoteka: {[2 + 54) / (24 * 87)} + (234 + 23)   Izlaz: neispravno
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct cvor{
  char z;
  struct cvor* sledeci;
} Cvor;

int main(){

  Cvor *stek = NULL;

  FILE *in = NULL;
  in = fopen("dat.txt", "r");
  if(in == NULL){
    fprintf(stderr, "Greska prilikom otvaranja datoteke dat.txt!\n");
    exit(EXIT_FAILURE);
  }

  char pom;

  while((pom=fgetc(in)) != EOF)
  {
   // ako je ucitana otvorena zagrada stavljamo je na stek
    if(pom =='(' || pom =='{' || pom =='[')
    { 
          Cvor *tmp = (Cvor*) malloc(sizeof(Cvor));
          if(tmp == NULL)
          {
            fprintf(stderr, "Greska prilikom alokacije memorije!\n");
            return 1;
          }
          tmp->z = pom;
          tmp->sledeci = stek;
          stek = tmp;   
   }   
   // ako je ucitana zatvorena zagrada...
   else if(pom == ')' || pom == '}' || pom == ']')
   { 
       // ...proveravamo da stek nije prazan i da li se na vrhu steka nalazi njegova odgovarajuca otvorena zagrada...
       if(stek != NULL && ( (stek->z == '(' && pom== ')') || (stek->z == '{' && pom == '}') || (stek->z == '[' && pom == ']')) )
       {
           	//... i u tom slucaju sa vrha steka uklanjamo otvorenu zagradu
            Cvor *tmp = stek->sledeci;
        	free(stek);
        	stek = tmp;
      }
      else
      {
           // u suprotnom, zagrade u aritmetickom izrazu nisu ispravno uparene
	       break;
      }
   }
  }//while

  // ako je na kraju stek prazan, zagrade su ispravno uparene (u suprotnom, nisu)
  if(stek == NULL)
    printf("ispravno\n");
  else{
    printf("neispravno\n");
    
  while(stek != NULL)
  { 
     //oslobadjamo memoriju koja je ostala na steku (u slucaju neispravnog uparivanja)
      Cvor *tmp = stek->sledeci;
      free(stek);
      stek = tmp;
    }
  }

  fclose(in);
  return 0;
}
