#include "lista.h"


#include <iostream>
using namespace std;

int main()
{
// Ovdje pišete vlastite testove klase. 
  List<int> l;

  l.insert(0, 1);
  l.insert(1, 2);

  l.insert(0, 5);
  cout << l.current() << endl;  // 5


  auto print = [&]() {
    for (int i = 0; i < l.size(); i++) {
      l.setPosition(i);
      cout << l.current() << " ";
    }
    cout << endl;
  };

  print(); // 5 1 2
  l.remove(0);
  print();


  l.clear();

  l.push_back(33);

  l.push_back(3);
  l.push_back(2);
  l.push_back(16);
  l.push_back(13);
  l.push_back(4);

  l.insert(0, 33);
  l.sort();

  print();
  return 0;



  l.insert(l.size(), -2);
  l.insert(0, 17);
  l.insert(5, 44);

  print();

  l.remove(0);
  l.remove(l.size() - 1);
  l.remove(5);

  print();


  return 0;
}
 
