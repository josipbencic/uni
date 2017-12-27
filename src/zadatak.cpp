#include "zadatak.h"
// Ubaciti potrebne include datoteke
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <stdexcept>

std::vector<int> zadatak1(std::string const & file_name){
  // Implementacija zadatka 1
   std::ifstream in(file_name);
   if(!in)
       throw std::runtime_error("File "+ file_name +" not found.");
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
    std::list<int> l2{l1};
    while( *l1.begin() != 5 ){
		std::next_permutation(l1.begin(), l1.end());
    }
//    std::cout << "l1 : ";
//    for(auto const & x : l1) std::cout << x << ",";
//    std::cout << std::endl;

	while( *l2.begin() != 9 )
		std::next_permutation(l2.begin(), l2.end());

//    std::cout << "l2 : ";
//    for(auto const & x : l2) std::cout << x << ",";
//    std::cout << std::endl;

    auto f = [](int &x){ return ((x == 4) || (x == 7)); };
    auto it1 = std::find_if(l2.begin(), l2.end(), f);
	if(it1 == l2.end()) throw std::runtime_error("First element not found.");
    it1++;
    auto it2 = std::find_if(it1, l2.end(), [](int &x){ return ((x == 4) || (x == 7)); });
	if(it2 == l2.end()) throw std::runtime_error("Second element not found.");
    it1--;

	auto it = std::find(l1.begin(), l1.end(), 3);
	if(it == l1.end()) throw std::runtime_error("Element 3 not found.");

//    std::cout << "*it1 = "  << *it1 << std::endl;
//    std::cout << "*it2 = "  << *it2 << std::endl;
//    std::cout << "*it = "  << *it << std::endl;

	l1.splice(it, l2, it1, it2);
//    std::cout << "l1 : ";
//	for(auto const & x : l1) std::cout << x << ",";
//	std::cout << std::endl;

//    std::cout << "l2 : ";
//    for(auto const & x : l2) std::cout << x << ",";
//    std::cout << std::endl;

	return l1;
}

