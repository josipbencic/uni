#include <iostream>
#include "zadatak.h"

#include <set>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;


void test_1() {
  string s = "ratata binary search omg";
  auto it = s.cbegin();
  auto rijec = procitaj_rijec(it, s.cend());
  cout << rijec << endl;
  if (it == s.cend()) {
    cout << "it = end" << endl;
  }
  else {
    cout << (*it) << endl;
  }
}

int main() {
  // Ovdje napisati svoje vlastite testove!
  test_1();

  return 0;
}
