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


#include <iostream>

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
    out << x << " " << sin(x) << " " << exp(x) << "\n";
  }
}

std::list<int> zadatak3() {
  // Implementacija zadatka 3
}

