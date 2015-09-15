#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


int main()
{
    Cvor *glava = NULL;
    Cvor *trazeni = NULL;
    int broj;

    /*
     * Testiramo dodavanje u listu tako da ona bude neopadajuce
     * uredjena 
     */
    printf
        ("\nUnosite elemente liste (za kraj unesite CTRL+D)\n");
    printf("\n\tLista: ");
    ispisi_listu(glava);

    while (scanf("%d", &broj) > 0) {
        dodaj_sortirano(&glava, broj);
        printf("\n\tLista: ");
        ispisi_listu(glava);
    }

    printf("\nUnesite element koji se trazi u listi: ");
    scanf("%d", &broj);

    trazeni = pretrazi_sortiranu_listu(glava, broj);
    if (trazeni == NULL)
        printf("Element NIJE u listi!\n");
    else
        printf("Trazeni broj %d je u listi!\n",
               trazeni->vrednost);


    /*
     * Brisemo elemente iz liste cije polje vrednost je jednako
     * broju procitanom sa ulaza 
     */
    printf("\nUnesite element koji se brise iz liste: ");
    scanf("%d", &broj);

    obrisi_element_sortirane_liste(&glava, broj);

    printf("Lista nakon brisanja:  ");
    ispisi_listu(glava);

    printf("\nLista ispisana u nazad: ");
    ispisi_listu_u_nazad(glava);

    oslobodi_listu(&glava);

    return 0;
}
