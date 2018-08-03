#include <iostream>

#include "bin_stablo.h"


using namespace std;

int main()
{
    // Vlastiti testovi

    BinarySTree<int> t;
    t.insert(5);
    t.insert(1);
    t.insert(3);
    t.insert(9);
    t.insert(8);
    t.clear();
    cout << t.size() << endl;
    return 0;
}
