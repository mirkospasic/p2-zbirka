#include <stdio.h>

/* Argumenti funkcije main mogu da budu broj argumenta komandne
   linije (int argc) i niz arugmenata komandne linije 
   (niz niski) (char *argv[]  <=>  char** argv) */
int main(int argc, char *argv[]) 
{
  int i;

  /* Ispisujemo broj argumenata komandne linije */
  printf("%d\n", argc);
    
  /* Ispisujemo argumente komandne linije */
  
  /* koristeci indeksnu sintaksu */
  /*
  for(i=0; i<argc; i++) {
    printf("%d %s\n", i, argv[i]);
  }
  */
      
  /* koristeci pokazivacku sintaksu */  
  i=argc;
  for (; argc>0; argc--)
    printf("%d %s\n", i-argc, *argv++);
  
  
  /* Nakon ove petlje "argc" ce biti jednako nuli a "argv" ce 
     pokazivati na polje u memoriji koje se nalazi iza 
	 poslednjeg argumenta komandne linije. Kako smo u 
	 promenljivoj "i" sacuvali vrednost broja argumenta 
	 komandne linije to sada možemo ponovo da postavimo 
	 "argv" da pokazuje na nulti argument komandne linije */
  argv = argv - i;
  argc = i; 
  
  /* Ispisujemo 0-ti karakter svakog od argumenata komandne linije */
  
  /* koristeci indeksnu sintaksu */
  /*
  for(i=0; i<argc; i++)
    printf("%c ", argv[i][0]);
  printf("\n"); 
  */
    
  /* koristeci pokazivacku sintaksu */
   
  for (i=0 ; i<argc; i++ )
    printf("%c ", **argv++);
    
  return 0;
}

