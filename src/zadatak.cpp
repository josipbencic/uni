#include "zadatak.h"
// Ubaciti potrebne include datoteke
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

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

void zadatak3(){
  // Implementacija zadatka 3
}

