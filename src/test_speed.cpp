#include <iostream>
#include <chrono>
#include <array>
#include <algorithm>

using std::cout;
using std::endl;
using namespace std::chrono;
  
template <typename T, size_t dim>
std::array<T,dim> operator+(std::array<T,dim> const& lhs, std::array<T,dim> const& rhs)
{
    std::array<T,dim> tmp; 
    for(size_t i=0; i < dim; ++i) 
       tmp[i] = lhs[i] + rhs[i];
    return tmp;
}

int main()
{
    const size_t dim = 100000;
    std::array<double,dim> A1;
    std::array<double,dim> A2;
    std::array<double,dim> A3;
    for(auto & x : A1) x = 2.3;
    for(auto & x : A2) x = 3.7;

    auto start = system_clock::now();
    for(int c=0; c<1000; ++c){
    	double coef = 5.0;
        for(unsigned int i=0; i < dim; ++i) A3[i] = A1[i] + A2[i];
        coef += 0.01;
    }
    auto end = system_clock::now();  
    auto duration = duration_cast<milliseconds>(system_clock::now() - start);

    cout<< "C time for " << dim << " additions = "<<  duration.count() <<" ms.\n";
    cout << A3[5678] << endl; // Da spriječi potpunu eliminaciju koda s opcijom -O2

    start = system_clock::now();
    for(int c=0; c<1000; ++c){
    	double coef = 1.0;
    	A3 = A1 + A2;
        coef += 0.01;
    }
    end = system_clock::now();
    duration = duration_cast<milliseconds> (system_clock::now() - start);

    cout<< "C++ time for " << dim << " additions = "<<  duration.count() <<" ms.\n";
    cout << A3[5678] << endl;// Da spriječi potpunu eliminaciju koda s opcijom -O2

    return 0;
}
