# C++ standardna biblioteka

   
C++ standardna biblioteka predstavlja programsku biblioteku koja dolazi s
prevodiocem i stoga je na raspolaganju svakom programu. Njen centralni dio 
je STL (_Standard Template Library_). Generalno standardna biblioteka se 
sastoji od ovih komponenti:
   
* Pomoćne klase, funkcije i konstante (_Utilities_);
* Spremnici, iteratori, algoritmi
* Ulazno izlazna biblioteka i internacionalizacija;
* Podrška za paralelno programiranje.

   
  Referenca: [en.cppreference.com/w/cpp](http://en.cppreference.com/w/cpp).
   

  
Centralni dio standardne biblioteke se sastoji od tri komponente:
  
* Spremnici;
* Iteratori;
* Algoritmi.

##   Spremnici


* **Sekvencijalni spremnici**: array, vector, string, deque, list, forward\_list;
     U sekvencijalnom spremniku element je određen svojim položajem u spremniku
* **Asocijativni spremnici**: set, multiset, map, multimap, unordered\_set, unordered\_multiset, unordered\_map,
   unordered\_multimap;
     U asocijativnom spremniku položaj elementa ovisi o njegovoj vrijednosti ili o vrijednosti _ključa_.  
     Imamo sortirane i nesortirane asocijativne spremnike. 
* **Adapteri spremnika**: stack, queue, priority\_queue. Adapteri adaptiraju spremnike dajući im drugo sučelje.
* **Specijalni spremnici**: bitset

  
 Operacije nad spremnicima vršimo pomoću metoda članica spremnika ili pomoću algoritama. 
 Kada je neki algoritam u danom spremniku implementiran kao metoda članica treba preferirati metodu članicu
 jer je efikasnija.
  

  
 Osnovne **operacije** na spremnicima su sljedeće: kreiranje spremnika, ubacivanje elemenata, transformacija elemenata, 
brisanje elemenata, traženje elementa, sortiranje.
  






## Algoritmi

  
 Algoritmi djeluju na spremnike kroz iteratore. Nikada ne izvršavaju 
 operacije koje nude spremnici i ne mijenjaju veličinu spremnika. To ih čini
 u najvećoj mjeri neovisnim o spremnicima. Svi su algoritmi definirani u 
 zahlavlju `<algorithm>` osim nekoliko numeričkih koji su 
 definirani u zaglavlju `<numeric>`.
  

  
**Primjer 1**: [accumulate](http://en.cppreference.com/w/cpp/algorithm/accumulate) (numerički algoritam). 
Iteratori dozvoljavaju primjenu na svaki tip na kojem je definiran operator +. 
  
```C++
    std::vector<int>  ivec = {1,-1,5,3,9};  // vektor
    int * pi = new int[5]{1,-1,5,3,9};      // polje dinam. alocirano

    // koristimo iteratore. Inicijalna vrijednost je 0.
    int sum = std::accumulate(ivec.cbegin(), ivec.cend(),0);
    std::cout << "sum = " << sum << std::endl;
    // koristimo pokazivače
    sum = std::accumulate(pi, pi+5, 0);
    std::cout << "sum = " << sum << std::endl;

    std::array<char,5> sarr = {'a', 'r', 'r', 'a', 'y'};
    // accumulate koristi operator + (ovdje konkatenaciju)
    // inicijalna vrijednost mora biti tipa string.
    std::string s = std::accumulate(sarr.begin(), sarr.end(), std::string(""));
    std::cout << "s = " << s << std::endl;
```
 
**Primjer 2**.  Spremnik možemo inicijalizirati pomoću algoritma
[fill](http://en.cppreference.com/w/cpp/algorithm/fill). 
 

```C++
    std::fill(ivec.begin(), ivec.end(), -1);
    for(auto &amp; x : ivec) std::cout << x << ",";
    std::cout << std::endl;
```


 
**Primjer 3**. Uspoređivanje spremnika pomoću algoritma  [equal](http://en.cppreference.com/w/cpp/algorithm/equal). 
 
```C++
    // Različite spremnike možemo usporediti s equal
    ivec = {1,-1,5,3,9};
    std::list<int> ilist ={1,-1,5,3,9}; // lista
    bool yes = std::equal(ivec.begin(), ivec.end(), ilist.begin());
    std::cout << "Spremnici " << ((yes) ? "su " : "nisu ") << "jednaki.\n";
```
 
**Primjer 4**. Promjena vrijednosti pomoću algoritma [replace](http://en.cppreference.com/w/cpp/algorithm/replace).
 
```C++
    // replace -- mijenja staru vrijednost za novu vrijednost
    int staro = 3;
    int novo  = 11;
    std::replace(ivec.begin(), ivec.end(), staro, novo);
    for(auto &amp; x : ivec) std::cout << x << ",";
    std::cout << std::endl;
```
 
**Primjer 5**. Kopiranje spremnika pomoću algoritma
[copy](http://en.cppreference.com/w/cpp/algorithm/copy). Dolazni spremnik (onaj u koji se
kopira) mora imati dovoljno mjesta za prihvatiti sve članove što algoritam kopiranja ne provjerava.
 

```C++
    // Kopiranje -- dolazni spremnik mora imati dovoljno veliku dimenziju
    //              što algoritam ne provjerava
    std::deque<double> deq;
    deq.resize(ivec.size());
    // Kopiraj. Prvo navodimo polazni, a zatim dolazni spremnik
    std::copy(ivec.begin(), ivec.end(), deq.begin());
    std::cout << "deq = ";
    for(auto &amp; x : deq) std::cout << x << ",";
    std::cout << std::endl;
```

## Insert iteratori

 
Insert iteratori su adapteri koji uzimaju spremnik i pretvaraju ga u iterator 
koji prilikom dereferenciranja insertira element u spremnik. Ta se operacija može 
obavljati pomoći metoda: `insert()`, `push_back()` i `push_front()` pa imamo :
 

* `inserter`
* `back_inserter`
* `front_inserter`

[back\_inserter](http://en.cppreference.com/w/cpp/iterator/back_inserter) naredbu `*it = value` prevodi u `push_back(value)` .
 

```C++
    // Upotreba insert-iteratora; list2 je prazna
    std::list<int> ilist1 = {1,2,3,4,5,6}, ilist2;
    // back_inserter koristi push_back() za insertiranje elementa u spremnik
    std::copy(ilist1.begin(), ilist1.end(), std::back_inserter(ilist2));
    for(auto &amp; x : ilist2) std::cout << x << ",";
    std::cout << std::endl;
    // rezultat: 1,2,3,4,5,6,
```

 
[front\_inserter](http://en.cppreference.com/w/cpp/iterator/front_inserter) naredbu `*it = value` prevodi u `push_front(value)` .
 

```C++
    // front_inserter koristi push_front() za insertiranje elementa u spremnik
    std::copy(ilist1.begin(), ilist1.end(), std::front_inserter(ilist2));
    for(auto &amp; x : ilist2) std::cout << x << ",";
    std::cout << std::endl;
    // rezultat:  6,5,4,3,2,1,1,2,3,4,5,6,
```

 
[inserter](http://en.cppreference.com/w/cpp/iterator/inserter) naredbu `*it = value` prevodi u `insert(value, it)`.
Naredba `insert` uzima vrijednost i poziciju insertiranja te vrši ubacivanje elementa **ispred** te pozicije. 
U ovom primjeru ćemo ubaciti elemente iz `ilist1` u `ilist2` na mjesto ispred prvog pojavljivanja broja 2. 
 
```C++
    // Nađimo prvo pojavljivanje broja 2. Ako ga nema find vraća ilist2.end()
    auto it = std::find(ilist2.begin(), ilist2.end(), 2);
    // inserter koristi insert(it) za insertiranje elementa u spremnik.
    std::copy(ilist1.begin(), ilist1.end(), std::inserter(ilist2,it));
    for(auto &amp; x : ilist2) std::cout << x << ",";
    std::cout << std::endl;
    // rezultat: 6,5,4,3,1,2,3,4,5,6,2,1,1,2,3,4,5,6,
```

## Iostream iteratori

 
`istream_iterator` služi za čitanje s ulaznog streama, dok `ostream_iterator` služi
za pisanje na izlazni stream. Oba iteratora promatraju stream kao niz vrijednosti 
istog tipa. 
 
 
Kod `istream_iterator`-a operator dereferenciranja vraća pročitanu vrijednost, a operator 
inkrementiranja (++) čita sljedeću vrijednost. Čitanje završava kada se dođe do kraja streama ili kada
dođe do greške. Za čitanje se koristi operator >>.  Prilikom unosa sa tastature kraj unosa se daje 
s Return i Ctrl-D (linux) ili s Return i Ctrl-Z (windows). 
 

```C++
    // istream iteratori
    std::istream_iterator<float> isi(std::cin);
    std::istream_iterator<float> isi_end;

    std::vector<float> fvec;
    // dereferenciranje operatora vraća pročitanu vrijednost. Operator ++
    // čita sljedeću vrijednost
    while(isi != isi_end){
        fvec.push_back(*isi++);
    }
  
    // Malo korisniji primjer -- čitanje iz datoteke.
    std::ifstream in("brojevi.txt");
    std::istream_iterator<float> isi_in(in);

    // čitanje pri konstrukciji vektor.
    std::vector<float> fvec2(isi_in, isi_end);
```   

 
Kod `ostream_iterator`-a operator dereferenciranja i operator 
inkrementiranja (++) ne rade ništa. Vrijednost na stream ispisuje operator pridruživanja.
Ovdje nemamo end-iteratora,ali konstruktor iteratora pored streama mora kao argument 
dobiti i separator podataka (kao C-string). Za pisanje se koristi operator <<. 
 




```C++
    // ostream iteratori
    std::ostream_iterator<float> osi(std::cout, "\n");
//    std::ostream_iterator<float> osi_end;  -- ne postoji !
    // ispis vektora
    std::copy(fvec2.begin(), fvec2.end(), osi);
    // drugi način da se postigne ispis:
    for(auto &amp; x : fvec2)
           *osi++ = x;  // dereferenciranje i inkrementiranje ne rade ništa
    // dovoljno je pisati
    for(auto &amp; x : fvec2)
           osi = x;    // ispis radi operator pridruživanja


    return 0;
}
```


 
**Zadatak 1**. Unutar funkcije učitajte niz cijelih brojeva iz datoteke [brojevi.txt](brojevi.txt) i 
smjestite ih u `std::vector`. Svako pojavljivanje nule u tom nizu zamijenite s 9 i vratite vektor kao 
povratnu vrijednost funkcije. Za upis koristiti `iostream` iteratore, a za zamjenu vrijednosti algoritam iz 
standardne biblioteke. 
 

 
**Zadatak 2**. Učitati iz datoteke niz realnih  brojeva (tip `float`) te ih pomoću back\_insertera  ubaciti u vektor
i zatim ispisati u datoteku imena "3cols.txt" u tri kolone za svaki učitani x: ` x sin(x) exp(x)`.  
Ispis mora biti precizno formatiran na sljedeći način: Brojevi se ispisuju u eksponencijalnom zapisu, sa 6 decimalnih 
znamenaka i znakom + ispred pozitivnog broja. Svaki broj mora imati istu (minimalnu) širinu i između brojeva 
mora biti samo jedna bjelina. 

 
**Zadatak 3**. Inicijalizirajte dvije liste cijelih brojeva brojevima od 1 do 9. Zatim permutirajte te brojeve
pomoću [next\_permutation](http://en.cppreference.com/w/cpp/algorithm/next_permutation)
sve dok u prvoj listi na prvom mjestu ne dobijete 5, a u dugoj 9. Zatim, prije elementa 3 u prvu listu ubacite elemente
iz druge liste koji se nalaze između elemenata 4 i 7 (ili 7 i 4, ovisno u kojem su elementi poretku). Koristite 
[splice](http://en.cppreference.com/w/cpp/container/list/splice) za transfer elemenata jedne 
liste u drugu i algoritam [find](http://en.cppreference.com/w/cpp/algorithm/find)
za nalaženje elementa. Pomoću [assert](http://en.cppreference.com/w/cpp/error/assert)
provjeravajte jesu li elementi nađeni. Kod smjestiti u funkciju koja vraća prvu listu. 
 


## Brisanje elemenata,` std::remove()`, `std::unique()`

 
Algoritmi ne mogu brisati elemente u spremnicima jer ne mogu obavljati operacije na
spremnicima. Stoga algoritam kao što je [std::remove](http://en.cppreference.com/w/cpp/algorithm/remove)
koji eliminira dani element iz spremnika i  
[std::unique](http://en.cppreference.com/w/cpp/algorithm/unique)
koji eliminira sve _kosekutivne_ duplikate u spremiku (otkrivene operatorom `==`) 
samo prebacuju te elemente na začelje spremika i vraćaju pokazivač (iterator)
`it` na prvi tako premješteni duplikat. Svi su duplikati sada u rasponu \[it, end()) 
i za njihovo eliminiranje treba zvati metodu spremnika `erase()`.
 
 
Metoda [std::sort](http://en.cppreference.com/w/cpp/algorithm/sort)
služi sortiranju spremika (pomoću operatora <) i pozivamo ju prije 
`std::unique()` kako bismo osigurali da su duplikati konsekutivni:
 

```C++
    // Izbacivanje duplikata
     std::vector<std::string> lista_imena;
     // Ubacimo neka imena
     lista_imena.push_back("Ante");
     lista_imena.push_back("Lovre");
     lista_imena.push_back("Karmela");
     lista_imena.push_back("Ante");
     lista_imena.push_back("Lovre");
     // Sortirajmo listu kako bi se ista imena našla jedna do drugih
     std::sort(lista_imena.begin(), lista_imena.end());
     // "brisanje" duplikata
     auto it_unique = std::unique(lista_imena.begin(), lista_imena.end());
     // stvarno brisanje
     lista_imena.erase(it_unique, lista_imena.end());
```
 


 
`remove` algoritam se **ne koristi** sa listom koja ima (efikasniju) `remove` metodu te se ne koristi sa 
asocijativnim spremnicima koji imaju verziju `erase` metode koja radi istu operaciju. S listom se ne koristi 
`sort` algoritam već  `sort` metoda liste koja je efikasnija. Asocijativni spremnici map, set, multimap i multiset 
se ne sortiraju jer su u njima po konstrukciji elementi sortirani. 
  





## Adaptiranje algoritama pomoću predikata

 
Mnogi algoritmi imaju preopterećenu verziju koja  uzima unarni ili binarni predikat. 
To su na primjer algoritmi koji koriste operatore `<` ili `==` i dozvoljavaju da 
korisnik zamijeni  standardne operatore s prilagođenim. U tim slučajevima možemo koristiti funkciju, 
funkcijski objekt ili lambda izraz.
 

**Zadatak 4**. Generirajte vektor prvih sto cijelih brojeva i izbacite sve brojeve dijeljive s 3 i 4 iz vektora.
Ispišite rezultat. Koristiti algoritam [remove\_if](http://en.cppreference.com/w/cpp/algorithm/remove)
i lambda funkciju kao predikat. 
 
 
**Zadatak 5**. a) Pomoću verzije algoritma
[std::list::sort](http://en.cppreference.com/w/cpp/container/list/sort) koji uzima operator uspoređivanja
kao treći argument sortirajte listu stringova iz datoteke [stringovi.txt](stringovi.txt) prema duljini stringa. 
b) Analogno, sortirajte niz parova koordinata u R^2 prema njihovoj udaljenosti od ishodišta.
 


 
Brisanje elemenata može _obezvrijediti_  iteratore, pokazivače i reference
na elemente. Kod vektora pri brisanju i umetanju gube vrijednost svi iteratori, pokazivači i reference
nakon upisanog/obrisanog elementa. Kod deque spremnika svi iteratori mogu izgubiti vrijednost.
Kod liste i asocijativnih spremnika (map, set, multimap, multiset) brisanje obezvrijeđuje samo iterator na obrisani element. 
 

 
Na primjer, sljedeći kod je neispravan:
 
```C++
 auto badValue = [](char c){ return c > 'k';};

     for(auto it = s1.begin(); it != s1.end(); ++it){
        if(badValue(*it)) s1.erase(it); // Neodređeno ponašanje -- it obezvrijeđen
     }
```
 
Ispravna verzija bi bila:
 
```C++
      for(auto it = s1.begin(); it != s1.end(); /* nista */){
        if(badValue(*it)) s1.erase(it++); // povećaj it prije no što staru vrijednost predaš funkciji erase
        else ++it;
     }
```

## Generiranje slučajnih brojeva

    
  Biblioteka slučajnih brojeva je dana u zaglavlju `<random>` i uključuje:
   
* Generatore (pseudo) slučajnih brojeva s uniformnom distribucijom ("Random number engines");
* Različite distribucije -- uniformna, normalna,  poissonova itd.
     Svaka distribucija uzima generator slučajnih brojeva i generira brojeve sa zadanom 
     statističkom distribucijom. 

   
Detalji se mogu naći na
[en.cppreference.com/w/cpp/numeric/random](http://en.cppreference.com/w/cpp/numeric/random).
   

   
Vidi i [predavanja](../../../Ch2/auxiliary.html).
   

   
I generatori slučajnih brojeva (SB) i sve distribucije djeluju kao funkcijski objekti.
  Pozivom generatora SB (bez argumenata) generira se sljedeći SB. Isto tako, pozivom 
  distribucije (sa generatorom SB kao argumentom) dobiva se novi SB po toj distribuciji. 
  Na generatoru je nužno pozvati metodu `seed()` s nekim  promjenjivim brojem (na primjer 
  trenutnim vremenom) kako se ne bi pri svakom pozivanju programa generirao isti 
  slučajni niz.
   

   
  Primjer korištenja defaultnog generatora:
   

```C++
#include <iostream>
#include <vector>
#include <random>  // Uključi biblioteku slučajnih brojeva
#include <ctime>   // Za trenutno vrijeme time(0)
#include <algorithm>

//  ...

   std::default_random_engine r_engine;  // Generator slučajnih brojeva
   r_engine.seed( std::time(nullptr) );  // seed = trenutno vrijeme, osigurava da ne generiramo uvijek 
                                         // isti niz brojeva
 ```

 
Iskoristimo normalnu distrinuciju sa očekivanjem 0 i standardnom devijacijom 2:
 

```C++
   // Normalna distribucija sa očekivanjem 0 i standardnom devijacijom 2.
   std::normal_distribution<> nd(0.0, 2.0);
  // Svaka distribucija funkcionira kao funkcija koja uzima generator SB 
  // kao argument i vraća sljedeću SB dane distribucije.
   std::vector<double> rand(20);
   for(auto &amp; x : rand) x = nd(r_engine);

   std::cout << "N(0,2) distribucija.\n";
   for(auto &amp; x : rand) std::cout << x << "\n";
```




 
**Zadatak 6**. Generirati vektor od 20 cijelih brojeva po binomnoj distribuciji (npr. t=26, p=0.4).
Na generiranom vektoru napraviti ove operacije i ispisati rezultat. 

* Sortirati ga pomoću algoritma [sort](http://en.cppreference.com/w/cpp/algorithm/sort).
* Sortirati prvih 5 elemenata niza pomoću 
  [partial\_sort](http://en.cppreference.com/w/cpp/algorithm/partial_sort).
* Particionirati niz ako da peti element bude na svom mjestu, ispred njega manji elementi, a iza 
         njega veći elementi. Koristiti [nth\_element](http://en.cppreference.com/w/cpp/algorithm/nth_element). 
* Particionirati elemente tako da svi elementi manji od 10 budu ispred elemenata većih ili jednakih 10. 
     Prvi dio izdvojiti u novi vektor i ispisati ga. Koristiti algoritam
  [partition](http://en.cppreference.com/w/cpp/algorithm/partition) i lambda izraz. 

 


 
**Zadatak 7**. Učitajte iz datoteke [stringovi.txt](stringovi.txt) niz stringova u vektor 
pomoću `copy` algoritma. Zatim instancirajte [set](http://en.cppreference.com/w/cpp/container/set)
pokazivača na stringove i ubacite u njega adrese učitanih stringova. Ukoliko bismo koristili spremnik 
`set<string *>`  uređaj bi se odnosio na adrese stringova, a ne na same stringove. 
Stoga treba setu dati dodatni template parametar
koji predstavlja tip binarnog operatora uspoređivanja koji će uspoređivati stringove umjesto pokazivača na
stringove. Dakle, treba koristiti `set<string *, Cmp>` gdje je `Cmp` klasa koja 
implementira binarni operator uspoređivanja. Nakon toga ispišite sadržaj set-a na izlazni stream 
koristeći algoritam [transform](http://en.cppreference.com/w/cpp/algorithm/transform) te
[ostream\_iterator](http://en.cppreference.com/w/cpp/iterator/ostream_iterator) 
i lambda funkciju koja će dereferencirati pokazivač na string (to je transformacija koja se radi na svakom elementu).
Stringovi moraju biti ispisani u leksikografskom poretku. 
 

 
**Zadatak 8**. Za normalnu distribuciju `N(mean,sigma)` ispišite histogram - izračunati 
relativne frekvencije nalaženja broja u sljedećim intervalima :
\[-3,-2),\[-2,-1),\[-1,0),\[0,1),\[1,2),\[2,3).
Srednja vrijednost `mean` i standardna devijacija `sigma` neka su argumenti kondne 
linije. 
Povećajte broj generiranih SB, mijenjajte parametre distribucije. Napravite ispis oblika:
```
[-3,-2) : xx
[-2,-1) : xxxxxxxxxxxxx
[-1,-0) : xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
[0,1)   : xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
[1,2)   : xxxxxxxxxxxx
[2,3)   : xx
```
gdje svaki x predstavlja 1 % relativne frekvencije za dani interval. 
 

 
Za račun relativnih frekvencija koristite algoritam 
[std::count\_if](http://en.cppreference.com/w/cpp/algorithm/count)
s predikatom zadanim _lambda izrazom_.
 


## Algoritmi na sortiranim rasponima

 
Na spremnicima čiji su elementi sortirani za pretraživanja možemo koristiti 
algoritme 
[lower\_bound](http://en.cppreference.com/w/cpp/algorithm/lower_bound),
[upper\_bound](http://en.cppreference.com/w/cpp/algorithm/upper_bound),
[equal\_range](http://en.cppreference.com/w/cpp/algorithm/equal_range) i
[binary\_search](http://en.cppreference.com/w/cpp/algorithm/binary_search).
Asocijativni spremnici `map`, `multimap`, `set` i `multiset` imaju implementirane metode
`lower_bound`, `upper_bound` i `equal_range`. Nesortirani asocijativni spremnici 
`unordered_map`, itd.  imaju implementiranu metodu `equal_range`.
 

 
[lower\_bound](http://en.cppreference.com/w/cpp/algorithm/lower_bound)
za dani element vraća iterator na prvu poziciju koja je **veća ili jednaka** od danog elementa. To je 
mjesto na kojem se nalazi traženi element ili mjesto na koje možemo insertirati traženi element da ne narušimo poredak. 
Kada tražene pozicije nema vraća se end iterator.
 

 
[upper\_bound](http://en.cppreference.com/w/cpp/algorithm/upper_bound)
za dani element vraća iterator na prvu poziciju koja je **strogo veća**  od danog elementa. 
Kada tražene pozicije nema vraća se end iterator.
 


 
[equal\_range](http://en.cppreference.com/w/cpp/algorithm/equal_range)
za dani element
vraća par iteratora. Prvi je onaj koji vraća `lower_bound`, a drugi je onaj koji vraća `upper_bound`. 
Ako su vraćeni iteratori jednaki onda element nije nađen. Ako je vraćeni raspon neprazan, onda on sadrži sve elemente ekvivalentne 
traženom elementu. 
 


 
[binary\_search](http://en.cppreference.com/w/cpp/algorithm/binary_search)
ispituje dali je zadani element u rasponu metodom binarnog pretraživanja (i stoga raspon mora biti sortiran).
 


 
**Zadatak 9**. Testirat ćemo operaciju traženja elementa pomoću `equal_range` 
u skupu i u sortiranom vektoru. Za mjerenje vremena moramo uključiti zaglavlje 
`<chrono>` te iskoristiti sljedeći kod:
 
```C++
    auto t_begin = std::chrono::system_clock::now();
    // kod kojem mjerimo vrijeme izvršavanja
    auto t_end = std::chrono::system_clock::now();
    std::cout << " vector Time = " 
              << std::chrono::duration_cast<chrono::nanoseconds>(t_end-t_begin).count() 
              << " nano sec\n";
```
 
U ovom primjeru je vrijeme mjereno i nanosekundama. Za više detalja vidjeti [ovdje](../../../Ch2/auxiliary.html#vrijeme).
 
Definiramo string,
```C++
  std::string str1="abcdef";
```
 
i zatim pomoću algoritna [shuffle](http://en.cppreference.com/w/cpp/algorithm/random_shuffle)
ubacujemo u set slučajne preraspodjele znakova u stringu (za to nam treba generator slučajnih brojeva),
ukupno njih 1000: 
 
```C++
    default_random_engine r_engine1;  // Generator slučajnih brojeva
    r_engine1.seed( std::time(nullptr) );

    set<string>  set1;
    for(unsigned i = 1; i < 1000u; ++i) {
        shuffle(str1.begin(), str1.end(),r_engine1);
        set1.insert(str1);
    }
```
 
Zatim treba vrijednosti iz skupa prekopirati u vektor i sortirati vektor. Nakon toga se radi još jedna 
preraspodjela znakova u stringu da se dobije novi string koji će se tražiti u skupu i vektoru. 
 

 
Prvo potražiti string u skupu pomoću metode članice `equal_range`. Izmjeriti vrijeme traženja
i ispisati ga zajedno s porukom je li string nađen. 
 

 
Zatim potražiti isti string u vektoru pomoću algoritma `equal_range`. Izmjeriti vrijeme traženja 
i ispisati ga zajedno s porukom je li string nađen. 
 
