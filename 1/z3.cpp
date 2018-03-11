#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>
using namespace std;

pair<string,string> createArray(string a, string b) {
    string up;
    string down;

    vector<int> v;  // 1 -> b ; 0 -> a
    {
        unsigned ones = 0;
        unsigned zero = 0;
        for (int i = 0;; i++) {
            if (ones == b.size() && zero == a.size()) {
                break;
            }
            if (ones == b.size()) {
                v.push_back(0);
                ++zero;
                continue;
            }
            if (zero == a.size()) {
                v.push_back(1);
                ++ones;
                continue;
            }
            int what = rand() % 2;
            if (what) {
                v.push_back(1);
                ++ones;
            }
            else {
                v.push_back(0);
                ++zero;
            }
        }
    }
    //cout << v.size() << endl;
    for (auto x : v) {
        cout << x;
    }
    cout << endl;

    int bit = 0;
    int ait = 0;
    int last = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != last) {
            up += a[ait++];
            down += b[bit++];
        } else {
            if (!v[i]) {
                up += a[ait++];
                down += '_';
            } else {
                up += '_';
                down += b[bit++];
            }
        }
        last = v[i];
    }
    return make_pair(up, down);
}

int main() {
    string a, b;
    cin >> a >> b;

    srand(time(0));

    for (int i = 0; i < 100; i++) {
        auto x = createArray(a, b);
        cout << x.first << endl;
        cout << x.second << endl;
        cout << endl;
    }
    return 0;
}