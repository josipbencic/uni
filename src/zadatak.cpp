#include "zadatak.h"
// Ubaciti potrebne include datoteke
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cassert>

std::vector<int> zadatak1(std::string const & file_name) {
  // Implementacija zadatka 1
  std::ifstream in(file_name);
  if (!in) {
    throw std::runtime_error(std::string("No file named") + file_name);
  }
  std::istream_iterator<int> fit(in);
  std::istream_iterator<int> fit_end;
  std::vector<int> ret(fit, fit_end);
  std::replace(ret.begin(), ret.end(), 0, 9);
  return ret;
}

void zadatak2(std::string const & file_name) {
  // Implementacija zadatka 2
  std::ifstream in(file_name);
  if (!in) {
    throw std::runtime_error(std::string("No file named") + file_name);
  }
  std::istream_iterator<float> fit(in);
  std::istream_iterator<float> fit_end;
  std::vector<float> v;
  std::copy(fit, fit_end, std::back_inserter(v));

  std::ofstream out("3cols.txt");
  if (!out) {
    throw std::runtime_error("Cannot create 3cols.txt!");
  }
  out << std::setprecision(6) << std::showpos << std::scientific;
  for (auto const & x : v) {
    out << x << " " << std::sin(x) << " " << std::exp(x) << "\n";
  }
}

std::list<int> zadatak3() {
  // Implementacija zadatka 3
  std::list<int> l1{1,2,3,4,5,6,7,8,9};
  std::list<int> l2{1,2,3,4,5,6,7,8,9};
  while ((*l1.begin()) != 5 && std::next_permutation(l1.begin(), l1.end()));
  while ((*l2.begin()) != 9 && std::next_permutation(l2.begin(), l2.end()));

  auto it = find(l1.begin(), l1.end(), 3);
  assert(it != l1.end());

  auto it2_7 = find(l2.begin(), l2.end(), 7);
  assert(it2_7 != l2.end());

  auto it2_4 = find(l2.begin(), l2.end(), 4);
  assert(it2_4 != l2.end());

  if (std::distance(it2_7, it2_4) < 0) {
    // 7 comes before 4
    l1.splice(it, l2, it2_7, it2_4);
  }
  else {
    //  4 comes before 7
    l1.splice(it, l2, it2_4, it2_7);
  }
  return l1;
}

