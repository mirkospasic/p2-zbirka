/* Datoteka sort.c */

#include "sort.h"

/* Funkcija sortira niz celih brojeva metodom sortiranja
   izborom. Ideja algoritma je sledeca: U svakoj iteraciji
   pronalazimo najmanji element i postavljamo ga na pocetak
   niza. Dakle, u prvoj iteraciji, pronalazimo najmanji element, 
   i dovodomo ga na nulto mesto u nizu. U i-toj iteraciji
   najmanjih i elemenata su vec na svojim pozicijama, pa od i+1
   do n-1 elementa trazimo najmanji, koji dovodimo na i+1
   poziciju. */
void selectionsort(int a[], int n)
{
  int i, j;
  int min;
  int pom;

  /* U svakoj iteraciji ove petlje se pronalazi najmanji element 
     medju elementima a[i], a[i+1],...,a[n-1], i postavlja se na 
     poziciju i, dok se element na pozciji i premesta na
     poziciju min, na kojoj se nalazio najmanji od gore
     navedenih elemenata. */
  for (i = 0; i < n - 1; i++) {
    /* Unutrasnja petlja pronalazi poziciju min, na kojoj se
       nalazi najmanji od elemenata a[i],...,a[n-1]. */
    min = i;
    for (j = i + 1; j < n; j++)
      if (a[j] < a[min])
        min = j;

    /* Zamena elemenata na pozicijama (i) i min. Ovo se radi
       samo ako su (i) i min razliciti, inace je nepotrebno. */
    if (min != i) {
      pom = a[i];
      a[i] = a[min];
      a[min] = pom;
    }
  }

}


/* Funkcija sortira niz celih brojeva metodom sortiranja
   umetanjem. Ideja algoritma je sledeca: neka je na pocetku
   i-te iteracije niz prvih i elemenata (a[0],a[1],...,a[i-1])
   sortirano. U i-toj iteraciji zelimo da element a[i] umetnemo
   na pravu poziciju medju prvih i elemenata tako da dobijemo
   niz duzine i+1 koji je sortiran. Ovo radimo tako sto i-ti
   element najpre uporedimo sa njegovim prvim levim susedom
   (a[i-1]). Ako je a[i] vece, tada je on vec na pravom mestu, i 
   niz a[0],a[1],...,a[i] je sortiran, pa mozemo preci na
   sledecu iteraciju. Ako je a[i-1] vece, tada zamenjujemo a[i]
   i a[i-1], a zatim proveravamo da li je potrebno dalje
   potiskivanje elementa u levo, poredeci ga sa njegovim novim
   levim susedom. Ovim uzastopnim premestanjem se a[i] umece na
   pravo mesto u nizu. */
void insertionsort(int a[], int n)
{
  int i, j;

  /* Na pocetku iteracije pretpostavljamo da je niz
     a[0],...,a[i-1] sortiran */
  for (i = 1; i < n; i++) {

    /* U ovoj petlji redom potiskujemo element a[i] u levo
       koliko je potrebno, dok ne zauzme pravo mesto, tako da
       niz a[0],...a[i] bude sortiran. Indeks j je trenutna
       pozicija na kojoj se element koji umecemo nalazi. Petlja
       se zavrsava ili kada element dodje do levog kraja (j==0)
       ili dok ne naidjemo na element a[j-1] koji je manji od
       a[j]. */
    for (j = i; j > 0 && a[j] < a[j - 1]; j--) {
      int temp = a[j];
      a[j] = a[j - 1];
      a[j - 1] = temp;
    }
  }
}


/* Funkcija sortira niz celih brojeva metodom mehurica. Ideja
   algoritma je sledeca: prolazimo kroz niz redom poredeci
   susedne elemente, i pri tom ih zamenjujuci ako su u pogresnom 
   poretku. Ovim se najveci element poput mehurica istiskuje na
   "povrsinu", tj. na krajnju desnu poziciju. Nakon toga je
   potrebno ovaj postupak ponoviti nad nizom a[0],...,a[n-2],
   tj. nad prvih n-1 elemenata niza bez poslednjeg koji je
   postavljen na pravu poziciju. Nakon toga se istu postupak
   ponavlja nad sve kracim i kracim prefiksima niza, cime se
   jedan po jedan istiskuju elemenenti na svoje prave pozicije. */
void bubblesort(int a[], int n)
{
  int i, j;
  int ind;

  for (i = n, ind = 1; i > 1 && ind; i--)

    /* Poput "mehurica" potiskujemo najveci element medju
       elementima od a[0] do a[i-1] na poziciju i-1 uporedjujuci 
       susedne elemente niza i potiskujuci veci u desno */
    for (j = 0, ind = 0; j < i - 1; j++)
      if (a[j] > a[j + 1]) {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;

        /* Promenljiva ind registruje da je bilo premestanja.
           Samo u tom slucaju ima smisla ici na sledecu
           iteraciju, jer ako nije bilo premestanja, znaci da su 
           svi elementi vec u dobrom poretku, pa nema potrebe
           prelaziti na kraci prefiks niza. Moglo je naravno i
           bez ovoga, algoritam bi radio ispravno, ali bi bio
           manje efikasan, jer bi cesto nepotrebno vrsio mnoga
           uporedjivanja, kada je vec jasno da je sortiranje
           zavrseno. */
        ind = 1;
      }
}

/* Selsort je jednostavno prosirenje sortiranja umetanjem koje
   dopusta direktnu razmenu udaljenih elemenata. Prosirenje se
   sastoji u tome da se kroz algoritam umetanja prolazi vise
   puta; u prvom prolazu, umesto koraka 1 uzima se neki korak h
   koji je manji od n (sto omogucuje razmenu udaljenih
   elemenata) i tako se dobija h-sortiran niz, tj. niz u kome su 
   elementi na rastojanju h sortirani, mada susedni elementi to
   ne moraju biti. U drugom prolazu kroz isti algoritam sprovodi 
   se isti postupak ali za manji korak h. Sa prolazima se
   nastavlja sve do koraka h = 1, u kome se dobija potpuno
   sortirani niz. Izbor pocetne vrednosti za h, i nacina
   njegovog smanjivanja menja u nekim slucajevima brzinu
   algoritma, ali bilo koja vrednost ce rezultovati ispravnim
   sortiranjem, pod uslovom da je u poslednjoj iteraciji h imalo 
   vrednost 1. */
void shellsort(int a[], int n)
{
  int h = n / 2, i, j;
  while (h > 0) {
    /* Insertion sort sa korakom h */
    for (i = h; i < n; i++) {
      int temp = a[i];
      j = i;
      while (j >= h && a[j - h] > temp) {
        a[j] = a[j - h];
        j -= h;
      }
      a[j] = temp;
    }
    h = h / 2;
  }
}

#define MAX 1000000

/* Funkcija sortira niz celih brojeva a[] ucesljavanjem.
   Sortiranje se vrsi od elementa na poziciji l do onog na
   poziciji d. Na pocetku, da bismo dobili niz kompletno
   sortiran, l mora biti 0, a d je jednako poslednjem validnom
   indeksu u nizu. Funkcija niz podeli na dve polovine, levu i
   desnu, koje zatim rekurzivno sortira. Od ova dva sortirana
   podniza, dobijamo sortiran niz ucesljavanjem, tj.
   istovremenim prolaskom kroz oba niza i izborom trenutnog
   manjeg elementa koji se smesta u pomocni niz. Na kraju
   algoritma, sortirani elementi su u pomocnom nizu, koji se
   kopira u originalni niz. */
void mergesort(int a[], int l, int d)
{
  int s;
  static int b[MAX];            /* Pomocni niz */
  int i, j, k;

  /* Izlaz iz rekurzije */
  if (l >= d)
    return;

  /* Odredjujemo sredisnji indeks */
  s = (l + d) / 2;

  /* Rekurzivni pozivi */
  mergesort(a, l, s);
  mergesort(a, s + 1, d);

  /* Inicijalizacija indeksa. Indeks i prolazi krozi levu
     polovinu niza, dok indeks j prolazi kroz desnu polovinu
     niza. Indeks k prolazi kroz pomocni niz b[] */
  i = l;
  j = s + 1;
  k = 0;

  /* "Ucesljavanje" koriscenjem pomocnog niza b[] */
  while (i <= s && j <= d) {
    if (a[i] < a[j])
      b[k++] = a[i++];
    else
      b[k++] = a[j++];
  }

  /* U slucaju da se prethodna petlja zavrsila izlaskom
     promenljive j iz dopustenog opsega u pomocni niz
     prepisujemo ostatak leve polovine niza */
  while (i <= s)
    b[k++] = a[i++];

  /* U slucaju da se prethodna petlja zavrsila izlaskom
     promenljive i iz dopustenog opsega u pomocni niz
     prepisujemo ostatak desne polovine niza */
  while (j <= d)
    b[k++] = a[j++];

  /* Prepisujemo "ucesljani" niz u originalni niz */
  for (k = 0, i = l; i <= d; i++, k++)
    a[i] = b[k];
}

/* Funkcija menja mesto i-tom i j-tom elementu niza a */
void swap(int a[], int i, int j)
{
  int tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}


/* Funkcija sortira deo niza brojeva a izmedju pozicija l i r.
   Njena ideja sortiranja je izbor jednog elementa niza, koga
   nazivamo pivot, koga cemo dovesti na svoje mesto. Posle ovog
   koraka, svi elementi levo od njega bice manji, a svi desno
   bice veci od njega. Kako smo pivota doveli na svoje mesto,
   da bismo imali kompletno sortiran niz, treba sortirati
   elemente levo (manje) od njega, i elemente desno (vece).
   Kako je dimenzija ova dva podniza manja od dimenzije
   pocetgnom niza koji je trebalo sortirati, ovaj deo ce za nas
   uraditi rekurzija. */
void quicksort(int a[], int l, int r)
{
  int i, pivot_position;

  /* Izlaz iz rekurzije -- prazan niz */
  if (l >= r)
    return;


  /* Particionisanje niza. Svi elementi na pozicijama <=
     pivot_position (izuzev same pozicije l) su strogo manji od
     pivota. Kada se pronadje neki element manji od pivota,
     uvecava se pivot_position i na tu poziciju se premesta
     nadjeni element. Na kraju ce pivot_position zaista biti
     pozicija na koju treba smestiti pivot, jer ce svi elementi
     levo od te pozicije biti manji a desno biti veci ili
     jednaki od pivota. */
  pivot_position = l;
  for (i = l + 1; i <= r; i++)
    if (a[i] < a[l])
      swap(a, ++pivot_position, i);

  /* Postavljamo pivot na svoje mesto */
  swap(a, l, pivot_position);

  /* Rekurzivno sortiramo elemente manje od pivota */
  quicksort(a, l, pivot_position - 1);
  /* Rekurzivno sortiramo elemente vece pivota */
  quicksort(a, pivot_position + 1, r);
}
