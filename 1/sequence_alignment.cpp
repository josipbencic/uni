#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<char, map<char, double>> blosum50() {
    constexpr const char* toChar = "ARNDCQEGHILKMFPSTWYVBJZX*";
    constexpr int N = strlen(toChar);

    ifstream in("blosum50.txt");

    map<char, map<char, double>> ret;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char x = toChar[i];
            char y = toChar[j];
            double tmp; in >> tmp;
            ret[x][y] = tmp;
        }
    }
    return ret;
}

int main(int argc, char** argv) {
    /*
    if (argc < 3) {
        cout << "No sequences specified!" << endl;
        return 0;
    }
    */

    auto blosum = blosum50();

    string x = "HPEW__" ;//"HPEWAAKEGHI"; // argv[1];
    string y = "_P_WAA"; //"_PWALVN_GSE"; // argv[2];
    {
        auto up = [](char x) -> char { return toupper(x); };
        transform(begin(x), end(x), begin(x), up);
        transform(begin(y), end(y), begin(y), up);

        //cout << x << " " << y << endl;
    }
    const int n = max(x.size(), y.size());
    double ans = 0.0;
    for (int i = 0; i < n; i++) {
        char xi = i < static_cast<int>(x.size()) ? x[i] : '_';
        char yi = i < static_cast<int>(y.size()) ? y[i] : '_';
        double tmp = 0.0;
        if (xi == '_' || yi == '_') {
            tmp = -8.0;
        }
        else {
            tmp = blosum[xi][yi];
        }
        cout << xi << " " << yi << " -> " << tmp << endl;
        ans += tmp;
    }
    cout << ans << endl;
}