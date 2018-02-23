# Sortiranje umetanjem (insertion sort)

Osnovni korak ovog algoritma sortiranja je dodavanje novog elementa u već sortiranu 
listu. Da bi lista sa dodatnim elementom bila sortirana potrebno je dodani element ubaciti na pravo mjesto 
u listu. Ta je opearcija jednostavna jer su svi ostali elementi već sortirani.

Algoritam kreće od prvog elementa do pretposljednjeg. U prvom koraku sortirani dio liste je 
prvi element liste (jedan element je uvijek "sortiran"). Toj se listi dodaje drugi element liste 
koji se umeće na pravo mjesto. Sada su prva dva elementa sortirana. U drugom koraku se listi od prva dva 
elementa dodaje treći element koji se smješta na odgovarajuće mjesto, nakon čega su prva tri elementa 
sortirana. Algoritam se nastavlja doke se ne iscrpe svi elementi polazne liste. 

Osnovna operacija u svakom koraku algoritma je premiještanje elemenata. 

 **Zadatak.**  1) Napisati parametriziranu funkciju 


```C++
template <typename Record>
void insertion_sort_ind(std::vector<Record> & vec)
{
 // ...
}
```
koja implementira sortiranje umetanjem i dohvaća elemente vektora kroz cjelobrojni indeks. 

2) Napisati generalniju verziju algoritma koja umjesto spremnika uzima raspon iteratora
i implementira a sortiranje umetanjem. Ova verzija od algoritama koristi samo std::next i std::prev.

```C++
// Verzija koja uzima raspon iteratora -- koristiti samo std::next i std::prev
template <typename Iter>
void insertion_sort(Iter first, Iter last) {
 // ...
}
```
3) Napisati verziju algoritma koja koristi algoritme std::rotate i std::upper_bound

```C++
  
// verzija sa algoritmima rotate i upper_bound
template <typename Iter>
void insertion_sort1(Iter first, Iter last)
 // ...
}
```
Testirati kod u main funkciji.

