#include "isort.h"


#include <vector>
#include <list>
#include <iostream>
using namespace std;

int main()
{
    // Testirajte vaše algoritme na vektoru i listi. 
    vector<int> v{7, 6, 5, 9, 13};
    list<int> l{7, 6, 5, 9, 13};

    insertion_sort_ind(v);
    insertion_sort(begin(l), l.end()--);

    for (auto x : v) cout << x << " ";
    cout << endl;
    for (auto x : l) cout << x << " ";
    cout << endl;

    return 0;
}
