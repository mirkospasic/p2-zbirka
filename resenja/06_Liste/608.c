#include<stdio.h>
#include<stdlib.h>
#include "601/lista.h"

Cvor *objedini(Cvor ** glava1, Cvor ** glava2)
{
    Cvor *l3 = NULL;
    Cvor **tek = &l3;

    if (*glava1 == NULL && *glava2 == NULL)
        return NULL;

    /* Ako je prva lista prazna, onda je rezultat druga lista. */
    if (*glava1 == NULL)
        return *glava2;

    /* Ako je druga lista prazna, onda je rezultat prva lista. */
    if (*glava2 == NULL)
        return *glava1;

    /* l3 pokazuje na pocetak nove liste, tj. na manji od brojeva
       sadrzanih u cvorovima na koje pokazuju glava1 i glava2. */
    l3 = ((*glava1)->vrednost < (*glava2)->vrednost) ? *glava1 : 
*glava2;


    while (*glava1 != NULL && *glava2 != NULL) {
        if ((*glava1)->vrednost < (*glava2)->vrednost) {
            *tek = *glava1;
            *glava1 = (*glava1)->sledeci;
        } else {
            *tek = *glava2;
            *glava2 = (*glava2)->sledeci;
        }
        tek = &((*tek)->sledeci);
    }

    /* Ukoliko smo izasli iz petlje zato sto smo stigli do kraja 
       prve liste onda na rezultujucu listu nadovezujemo ostatak 
       druge liste. */
    if (*glava1 == NULL)
        *tek = *glava2;

    else if (*glava2 == NULL)
        *tek = *glava1;

    return l3;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr,
                "Greska! Program se poziva sa: ./a.out dat1.txt dat2.txt!\n");
        exit(EXIT_FAILURE);
    }

    FILE *in1 = NULL;
    in1 = fopen(argv[1], "r");
    if (in1 == NULL) {
        fprintf(stderr,
                "Greska prilikom otvaranja datoteke %s.\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *in2 = NULL;
    in2 = fopen(argv[2], "r");
    if (in2 == NULL) {
        fprintf(stderr,
                "Greska prilikom otvaranja datoteke %s.\n",
                argv[2]);
        exit(EXIT_FAILURE);
    }

    int broj;
    Cvor *glava1 = NULL;
    Cvor *glava2 = NULL;
    Cvor *l3 = NULL;

    /* Ucitavamo liste. */
    while (fscanf(in1, "%d", &broj) != EOF)
        dodaj_na_kraj_liste(&glava1, broj);
    while (fscanf(in2, "%d", &broj) != EOF)
        dodaj_na_kraj_liste(&glava2, broj);

    /* Objedinjujemo ih u jednu listu. */    
    l3 = objedini(&glava1, &glava2);

    /* Ispisujemo rezultujucu listu. */
    ispisi_listu(l3);
    oslobodi_listu(&l3);

    fclose(in1);
    fclose(in2);
    return 0;
}
