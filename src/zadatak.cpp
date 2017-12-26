#include "zadatak.h"
// Ubaciti potrebne include datoteke
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>

std::vector<int> zadatak1(std::string const & file_name){
  // Implementacija zadatka 1
   std::ifstream in(file_name);
   std::istream_iterator<int> isi_in(in);
   std::istream_iterator<int> isi_end;    

   std::vector<int> vec(isi_in, isi_end);
   std::replace(vec.begin(), vec.end(), 0, 9);

   return vec;
}

void zadatak2(){
  // Implementacija zadatka 2
}

std::list<int> zadatak3(){
  // Implementacija zadatka 3
	std::list<int> l1{1,2,3,4,5,6,7,8,9};
	std::list<int> l2 = l1;
	while( *l1.begin() != 5 )
		std::next_permutation(l1.begin(), l1.end());
	while( *l2.begin() != 9 )
		std::next_permutation(l2.begin(), l2.end());

	auto it1 = std::find_if(l2.begin(), l2.end(), [](int x){ return ((x == 4) or (x == 7)); });
	if(it1 == l2.end()) throw std::runtime_error("First element not found.");
	auto it1p = it1++;
	auto it2 = std::find_if(it1p, l2.end(), [](int x){ return ((x == 4) or (x == 7)); });
	if(it2 == l2.end()) throw std::runtime_error("Second element not found.");

	auto it = std::find(l1.begin(), l1.end(), 3);
	if(it == l1.end()) throw std::runtime_error("Element 3 not found.");

	l1.splice(it, l2, it1, it2);
	return l1;
}

