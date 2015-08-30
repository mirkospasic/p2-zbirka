#include <stdio.h>

int broj_parova(unsigned int x){

	int broj_parova;
	unsigned int maska;

	/* Postavljamo broj parova na 0 */
	broj_parova=0;
	
	/* Postavljamo masku tako da mozemo da procitamo da li su dva najmanja bita u zapisu broja x 11 */
	/* broj 3 je binarno 000....00011 */
	maska=3; 



	/* Dok ne obidjemo sve parove bitova u zapisu broja x */
	while(x!=0){

		/* Proveravamo da li se na najmanjim pozicijama broj x nalazi 11 par */
		if((x & maska) == maska){
			broj_parova++;
		}
		
		/* Pomeramo broj u desnu stranu tako da mozemo da ocitamo vrednost sledeceg para bitova */
		x=x>>1;
	} 

	
	return broj_parova;

}	

int main(){
	unsigned int x;

	/* Ucitavamo broj */
	scanf("%u", &x);

	/* Ispsujemo vrednost funkcije */
	printf("%d\n", broj_parova(x));

	return 0;
}


