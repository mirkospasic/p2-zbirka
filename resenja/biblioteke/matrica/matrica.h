#ifndef _MATRICA_H_
#define _MATRICA_H_ 1

/* Funkcija dinamicki alocira memoriju za matricu dimenzije n x m */
int **alociraj_matricu(int n, int m);

/* Funkcija dinamicki alocira memoriju za kvadratnu matricu dimenzije 
   n x n */
int **alociraj_kvadratnu_matricu(int n);

/* Funkcija oslobadja memoriju za matricu sa n vrsta */
int **dealociraj_matricu(int **matrica, int n);

/* Funkcija ucitava vec alociranu matricu dimenzije n x m sa
   standardnog ulaza */
void ucitaj_matricu(int **matrica, int n, int m);

/* Funkcija ucitava vec alociranu kvadratnu matricu dimenzije n sa
   standardnog ulaza */
void ucitaj_kvadratnu_matricu(int **matrica, int n);

/* Funkcija ispisuje matricu dimenzije n x m na standardnom izlazu */
void ispisi_matricu(int **matrica, int n, int m);

/* Funkcija ispisuje kvadratnu matricu dimenzije n na standardnom
   izlazu */
void ispisi_kvadratnu_matricu(int **matrica, int n);

/* Funkcija ucitava vec alociranu matricu dimenzije n x m iz datoteke
   f */
int ucitaj_matricu_iz_datoteke(int **matrica, int n, int m, FILE * f);

/* Funkcija ucitava vec alociranu kvadratnu matricu dimenzije n x n 
   iz datoteke f */
int ucitaj_kvadratnu_matricu_iz_datoteke(int **matrica, int n,
                                         FILE * f);

/* Funkcija upisuje matricu dimenzije n x m u datoteku f */
int upisi_matricu_u_datoteku(int **matrica, int n, int m, FILE * f);

/* Funkcija upisuje kvadratnu matricu dimenzije n x n u datoteku f */
int upisi_kvadratnu_matricu_u_datoteku(int **matrica, int n,
                                       FILE * f);

#endif
