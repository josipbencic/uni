#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Bignum {
public:
	Bignum()
	{}

	Bignum(int x)
	{
		parseInt(x);
	}
	
	static const Bignum Neutral() {
		return Bignum(1);
	}
	
	const int& operator [](size_t i) const {
		return a[i];
	}
	
	int& operator [](size_t i) {
		return a[i];
	}
	
	size_t size() const {
		return a.size();
	}
	
	inline void parseInt(int x)
	{
		if (x == 0)
		{
			a.push_back(0);
			return;
		}
		
		while (x > 0)
		{
			a.push_back(x%10);
			x /= 10;
		}
	}
	
	static inline void RemoveOver10(Bignum& a)
	{
		int n = a.size();
		for (int i = 0; i < n - 1; i++)
			if (a[i] > 9) {
				a[i+1] += a[i]/10;
				a[i] %= 10;
			}
		
		bool bDone = false;
		while (!bDone)
		{
			bDone = true;
			if (a[n-1] > 9)
			{
				bDone = false;
				n++;
				a.a.resize(n);
				a[n-1] = a[n-2]/10;
				a[n-2] %= 10;
			}
		}
	}
	
	static inline void ClearExtras(Bignum& a)
	{
		for (int i = a.size() - 1; i > -1; i--)
			if (a[i] == 0) a.a.pop_back();
			else return;
	}
	
	static inline long long GetDigitSum(Bignum& a)
	{
		int n = a.size();
		long long ret = 0ll;
		for (int i = 0; i < n; i++)
			ret += a[i];
		
		return ret;
	}
	
	vector<int> a;
};

ostream& operator <<(ostream& stream, const Bignum& a)
{
	if (a.size() == 0)
	{
		stream << 0; return stream;
	}
	for (int i = a.a.size() - 1; i > -1; i--)
		stream << a[i];
	return stream;
}

bool operator <(const Bignum& a, const Bignum& b)
{	
	if (a.size() != b.size()) return (a.size() < b.size());
	
	for (int i = b.size() - 1; i >= 0; i--)
		if (a[i] != b[i]) return (a[i] < b[i]);

	return false;
}
	
const Bignum operator +(const Bignum& a, const Bignum& b)
{
	//cout << a << " + " << b << " = ";
	Bignum ret;
	if (b < a) 	ret = a;
	else 		ret = b;
	int n = std::min(a.size(), b.size());
	
	for (int i = 0; i < n; i++)
		ret[i] = a[i] + b[i];
	//cout << ret << " = ";
	Bignum::RemoveOver10(ret);
	//cout << ret << endl;
	return ret;
}


const Bignum operator *(const Bignum& a, const Bignum& b)
{	
	int n = std::max(a.size(), b.size());
	Bignum ret;
	for (int i = 0; i < (int)b.size(); i++)
	{
		Bignum tmp;
		for (int j = 0; j < i; j++) tmp.a.push_back(0);
		
		for (int j = i; j < i + (int)a.size(); j++)
			tmp.a.push_back(b[i] * a[j - i]);
		
		ret = ret + tmp;
	}
	Bignum::RemoveOver10(ret);
	//cout << ret << endl;
	return ret;
}


using ll = long long;
using mat = vector<vector<Bignum>>;

mat PAM1() {
    mat ret(20, vector<Bignum>(20, 0));
    ifstream in("PAM1.txt");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            ll a; in >> a;
            ret[i][j] = a;
        }
    }

    cout << "loaded matrix!" << endl;
    return ret;
}

template <class T> struct Traits { };

template<>
struct Traits<mat> {
    static mat Identity(const mat& m) {
        mat ret(m.size(), vector<Bignum>(m.size(), 0));
        for (int i = 0; i < m.size(); i++) {
            ret[i][i] = 1;
        }
        return ret;
    }

    static mat Multiply(const mat& a, const mat& b) {
        mat ret(a.size(), vector<Bignum>(b[0].size(), 0));
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b[i].size(); j++) {
                for (int k = 0; k < b.size(); k++) {
                    ret[i][j] += a[i][k] * b[k][j];
               }
            }
        }
        return ret;
    }
};

template <typename T>
inline T FastExp(T Base, int Exp) {
	T Ret = Traits<T>::Identity(Base);
	while (Exp) {
		if (Exp & 1) {
            Ret = Traits<T>::Multiply(Ret, Base);
        }
		Base = Traits<T>::Multiply(Base, Base);
		Exp >>= 1;
	}
	return Ret;
}


int main() {
    auto m = PAM1();

    auto M = FastExp(m, 100);

    for (auto x : M) {
        for (auto y : x) {
            cout << y << "\t";
        }
        cout << endl;
    }
}