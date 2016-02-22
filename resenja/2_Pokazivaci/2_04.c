#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;
  char tip_ispisa;

  printf("Broj argumenata komandne linije je %d.\n", argc);
  printf("Kako zelite da ispisete argumente? Koriscenjem"
         " indeksne ili pokazivacke sintakse (I ili P)? ");
  scanf("%c", &tip_ispisa);

  printf("Argumenti komandne linije su:\n");
  if (tip_ispisa == 'I') {
    /* Ispisuju se argumenti komandne linije koriscenjem indeksne
       sintakse */
    for (i = 0; i < argc; i++)
      printf("%d %s\n", i, argv[i]);
  } else if (tip_ispisa == 'P') {
    /* Ispisuju se argumenti komandne linije koriscenjem
       pokazivacke sintakse */
    i = argc;
    for (; argc > 0; argc--)
      printf("%d %s\n", i - argc, *argv++);

    /* Nakon ove petlje argc je jednako nuli, a argv pokazuje na
       polje u memoriji koje se nalazi iza poslednjeg argumenta
       komandne linije. Kako je u promenljivoj i sacuvana vrednost
       broja argumenta komandne linije to sada moze ponovo da se
       postavi argv da pokazuje na nulti argument komandne linije */
    argv = argv - i;
    argc = i;
  }

  printf("Pocetna slova argumenata komandne linije:\n");
  if (tip_ispisa == 'I') {
    /* koristeci indeksnu sintaksu */
    for (i = 0; i < argc; i++)
      printf("%c ", argv[i][0]);
    printf("\n");
  } else if (tip_ispisa == 'P') {
    /* koristeci pokazivacku sintaksu */
    for (i = 0; i < argc; i++)
      printf("%c ", **argv++);
    printf("\n");
  }

  return 0;
}
