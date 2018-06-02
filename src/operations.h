#include <cstddef>
#include <cassert>
#include <array>   

// Dio implementacije operacija -- nadopuniti

// Deklaracija 
 class Scalar; 

// Klasa obilježja koja nam omogućava da vektor tretiramo kroz 
// reference, a skalare po vrijednosti. 
template <typename T>
struct Traits{
   typedef T const& ExprRef;
};
// Specijalizacija na skalare
// Na skalare ne uzimamo referencu jer im vijek trajanja može biti kraći od 
// vijeka trajanja izraza koji se izračunava.
template <>
struct Traits<Scalar>{
   typedef Scalar ExprRef;
};



// Klasa koja reprezentira zbrajanje. 
template <typename OP1, typename OP2>
class Add{
    private:
	typename Traits<OP1>::ExprRef op1;
	typename Traits<OP2>::ExprRef op2;
    public:
	Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}

	double operator[](int i) const { return op1[i]+op2[i]; };
};

// Operator indeksiranja vraća vrijednost skalara. 
class Scalar{
    private:
        double val;
    public:
    	Scalar(double const& v) : val(v) {}
    	double operator[](size_t) const { return val; }
};

template <size_t N, typename Rep = std::array<double,N> >
class Vector{
    private:
        Rep expr_rep;  // vektor ili reprezentacija operacije nad vektorima
    public:
	// Polje iz skalarne vrijednosti 
	explicit Vector(double val = 0.0) {expr_rep.fill(val);}
	// Polje iz reprezentacije
	Vector(Rep const& r) : expr_rep(r) {}
    // pridruživanje polja različitog tipa
	template <typename Rep2>
	Vector& operator=(Vector<N,Rep2> const& rhs){
	    for(size_t i=0; i < N; ++i) expr_rep[i]= rhs[i];
	    return *this;
	}
    size_t size() const { return N; }

    double  operator[](size_t i) const {  return expr_rep[i]; }
	double& operator[](size_t i) { return expr_rep[i]; }

	Rep const& rep() const { return expr_rep; }
    Rep&       rep()       { return expr_rep; }
};

// Operator zbrajanje vektora
template <size_t N,   typename R1, typename R2>
Vector<N, Add<R1,R2> >
operator+(Vector<N,R1> const& a, Vector<N,R2> const& b){
    return Vector<N, Add<R1,R2> >( Add<R1,R2>( a.rep(),b.rep() ) );
}

// Operator množenje skalar * vektor
template <size_t N, typename R2>
Vector<N, Mult<Scalar,R2> >
operator*(double const& a, Vector<N,R2> const& b)
{
    return Vector<N,Mult<Scalar,R2> >( Mult<Scalar,R2>( Scalar(a), b.rep() ) );
} 
