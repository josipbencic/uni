# C++  STL 1

   
Referenca: [en.cppreference.com/w/cpp](http://en.cppreference.com/w/cpp).
   

  
 
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
 

