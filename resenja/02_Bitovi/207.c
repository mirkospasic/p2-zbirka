#include <stdio.h>

/* Funkcija vraca 1 ukoliko je u binarnoj reprezentaciji broja n broj jedinica veci od broja nula.
 U suprotnom funkcija vraca 0 */
int Broj01(unsigned int n){

	int broj_nula, broj_jedinica;
	unsigned int maska;

	broj_nula=0;
	broj_jedinica=0;
	
	/* Postavljamo masku tako da pocinjemo sa analiziranjem bita najvece tezine */
	maska=1<<(sizeof(unsigned int)*4-1);

	/* Dok ne obidjemo sve bitove u zapisu broj n */
	while(maska!=0){

		/* Proveravamo da li se na poziciji koju odredjuje maska nalazi 0 ili 1 i uvecavamo odgovarajuci brojac */
		if(n&maska){
			broj_jedinica++;
		}
		else{
			broj_nula++;
		}

		/* Pomeramo masku u desnu stranu tako da mozemo da ocitamo vrednost narednog bita */
		maska=maska>>1;
	} 

	/* Ako je broj jedinica veci od broja nula vracamo 1, u suprotnom vracamo 0 */
	return (broj_jedinica>broj_nula)? 1: 0;

}	

int main(){
	unsigned int n;

	/* Ucitavamo broj */
	scanf("%u", &n);

	/* Ispsujemo vrednost funkcije */
	printf("%d\n", Broj01(n));

	return 0;
}
