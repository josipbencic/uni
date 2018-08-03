#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>

// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
  friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
public:
  explicit Vect(size_t n = 0, T v = {});  // Ctor
  // Kontrola kopiranja dolazi ovdje
  // CCtor
  Vect(const Vect<T>& src);
  // MCtor
  Vect(Vect<T>&& src);

  // OP
  const Vect<T>& operator =(const Vect<T>& rhs);

  // MOP
  const Vect<T>& operator =(Vect<T>&& rhs);

  // DTOR
  ~Vect();

  // dohvat elemenata (operator [])
  const T& operator [](size_t i) const {
    return  *(mdata + i);
  }

  T& operator [](size_t i) {
    return *(mdata + i);
  }

  // push_back metoda
  const Vect<T>& push_back(const T&);

  // info rutine size() i capacity()
  inline size_t size() const {
    return mfirst_free - mdata;
  }

  inline size_t capacity() const {
    return mend - mdata;
  }

  // operatori +=, -=, *=
  const Vect<T>& operator +=(const Vect<T>& rhs);

  const Vect<T>& operator -=(const Vect<T>& rhs);

  const Vect<T>& operator *=(double alpha);

  // euklidska norma vraća double !
  double two_norm() const;

private:
  T *mdata;       // pokazivač na prvi element
  T *mfirst_free; // pokazivač na prvo slobodno mjesto
  T *mend;        // pokazivač na kraj alociranog prostora
                  // (jedno mjesto iza posljednjeg)

  // Oslobodi zauzeti prostor (pomoću alokatora)
  void free();

  // realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
  // vektor prazan alociraj jedan element.
  void reallocate();

  // dodati vlastite privatne metode.

  // alokator ne mora imati pristup varijablama članicama klase pa ga činimo
  // statičkim. Ne zaboraviti definirati ga.
  static std::allocator<T> alloc;
};

// Deklaracija operator +, - i <<

template <typename T>
Vect<T> operator +(const Vect<T>&, const Vect<T>&);


template <typename T>
Vect<T> operator -(const Vect<T>&, const Vect<T>&);

template <typename T>
std::ostream& operator <<(std::ostream& stream, const Vect<T>&);


// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
