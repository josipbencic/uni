#include <array>
#include <cassert>
#include <cstddef>

// Dio implementacije operacija -- nadopuniti

// Deklaracija
class Scalar;

// Klasa obilježja koja nam omogućava da vektor tretiramo kroz
// reference, a skalare po vrijednosti.
template <typename T>
struct Traits { typedef T const& ExprRef; };
// Specijalizacija na skalare
// Na skalare ne uzimamo referencu jer im vijek trajanja može biti kraći od
// vijeka trajanja izraza koji se izračunava.
template <>
struct Traits<Scalar> { typedef Scalar ExprRef; };

// Klasa koja reprezentira zbrajanje.
template <typename OP1, typename OP2>
class Add {
private:
  typename Traits<OP1>::ExprRef op1;
  typename Traits<OP2>::ExprRef op2;

public:
  Add(OP1 const& a, OP2 const& b)
    : op1(a), op2(b) {
  }

  double operator[](int i) const {
    return op1[i] + op2[i];
  }
};

template <typename OP1, typename OP2>
class Sub {
private:
  typename Traits<OP1>::ExprRef op1;
  typename Traits<OP2>::ExprRef op2;

public:
  Sub(OP1 const& a, OP2 const& b)
    : op1(a), op2(b) {
  }

  double operator[](int i) const {
    return op1[i] - op2[i];
  }
};

template <typename OP1, typename OP2>
class Mult {
private:
  typename Traits<OP1>::ExprRef op1;
  typename Traits<OP2>::ExprRef op2;

public:
  Mult(OP1 const& a, OP2 const& b)
    : op1(a), op2(b) {
  }

  double operator[](int i) const {
    return op1[i] * op2[i];
  }
};

// Operator indeksiranja vraća vrijednost skalara.
class Scalar {
private:
  double val;

public:
  Scalar(double const& v)
    : val(v) {
  }
  inline double operator[](size_t) const {
    return val;
  }
};

template <size_t N, typename Rep = std::array<double, N>>
class Vector {
private:
  Rep expr_rep; // vektor ili reprezentacija operacije nad vektorima
public:
  // Polje iz skalarne vrijednosti
  explicit Vector(double val = 0.0) {
    expr_rep.fill(val);
  }

  // Polje iz reprezentacije
  Vector(Rep const& r)
    : expr_rep(r) {
  }
  // pridruživanje polja različitog tipa
  template <typename Rep2>
  Vector& operator=(Vector<N, Rep2> const& rhs) {
    for (size_t i = 0; i < N; ++i) {
      expr_rep[i] = rhs[i];
    }
    return *this;
  }
  size_t size() const {
    return N;
  }

  double operator[](size_t i) const {
    return expr_rep[i];
  }

  double& operator[](size_t i) {
    return expr_rep[i];
  }
  Rep const& rep() const {
    return expr_rep;
  }
  Rep& rep() {
    return expr_rep;
  }
};

template <size_t N, typename R1, typename R2>
inline Vector<N, Add<R1, R2>> operator+(Vector<N, R1> const& a,
                                        Vector<N, R2> const& b) {
  return Vector<N, Add<R1, R2>>(Add<R1, R2>(a.rep(), b.rep()));
}

template <size_t N, typename R1>
inline Vector<N, Add<R1, Scalar>> operator+(Vector<N, R1> const& a, double b) {
  return Vector<N, Add<R1, Scalar>>(Add<R1, Scalar>(a.rep(), Scalar(b)));
}

template <size_t N, typename R1>
inline Vector<N, Add<R1, Scalar>> operator+(double b, Vector<N, R1> const& a) {
  return a + b;
}

template <size_t N, typename R2>
inline Vector<N, Mult<Scalar, R2>> operator*(double const& a, Vector<N, R2> const& b) {
  return Vector<N, Mult<Scalar, R2>>(Mult<Scalar, R2>(Scalar(a), b.rep()));
}

template <size_t N, typename R2>
inline Vector<N, Mult<Scalar, R2>> operator*(Vector<N, R2> const& b, double const& a) {
  return a * b;
}

template <size_t N, typename R1, typename R2>
inline Vector<N, Sub<R1, R2>> operator-(Vector<N, R1> const& a,
                                        Vector<N, R2> const& b) {
  return Vector<N, Sub<R1, R2>>(Sub<R1, R2>(a.rep(), b.rep()));
}


template <typename T, size_t N, size_t M>
class Array2D {
private:
  T m_data[N][M];

public:
  const T& operator()(size_t i, size_t j) const {
    return m_data[i][j];
  }
  T& operator()(size_t i, size_t j) {
    return m_data[i][j];
  }

  // Izbrisana kontrola kopiranja

  size_t rows() const {
    return N;
  }
  size_t cols() const {
    return M;
  }
};

template <size_t N, size_t M, typename Rep = Array2D<double, N, M>>
class Matrix {
private:
  Rep expr_rep;

public:
  explicit Matrix(double val = 0.0) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        expr_rep(i, j) = val;
      }
    }
  }

  Matrix(Rep const& src)
    : expr_rep(src.expr_rep) {
  }

  inline const double& operator()(size_t i, size_t j) const {
    return expr_rep(i, j);
  }

  inline double& operator()(size_t i, size_t j) {
    return expr_rep(i, j);
  }

  size_t rows() const {
    return N;
  }

  size_t cols() const {
    return M;
  }

  double operator[](size_t i) const {
    return expr_rep[i];
  }

  double& operator[](size_t i) {
    return expr_rep[i];
  }

  Rep const& rep() const {
    return expr_rep;
  }

  Rep& rep() {
    return expr_rep;
  }
};

template <typename OP1, typename OP2>
class MatrixVectMult {
private:
  typename Traits<OP1>::ExprRef op1;
  typename Traits<OP2>::ExprRef op2;

public:
  MatrixVectMult(OP1 const& a, OP2 const& b)
    : op1(a), op2(b) {
  }

  double operator[](int i) const {
    double ret = 0.0;
    int n = op1.rows();
    for (int k = 0; k < n; ++k) {
      ret += op1(i, k) * op2[k];
    }
    return ret;
  }
};

template <size_t N, size_t M, typename R1, typename R2>
Vector<N, MatrixVectMult<R1, R2>> operator*(Matrix<N, M, R1> const& A, Vector<M, R2> const& x) {
  return Vector<N, MatrixVectMult<R1, R2>>(MatrixVectMult<R1, R2>(A.rep(), x.rep()));
}
