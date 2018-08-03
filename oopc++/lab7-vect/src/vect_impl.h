// Vaša implementacija dolazi ovdje.

#include <memory>
#include <algorithm>

template <typename T>
std::allocator<T> Vect<T>::alloc;

template <typename T>
Vect<T>::Vect(size_t n, T v)
  : mdata(nullptr), mfirst_free(nullptr), mend(nullptr) {
  while (capacity() < n) {
    reallocate();
  }
  for (size_t i = 0u; i < n; i++) {
    alloc.construct(mdata + i, v);
    mfirst_free++;
  }
}

template <typename T>
Vect<T>::Vect(const Vect<T>& src)
  : mdata(nullptr), mfirst_free(nullptr), mend(nullptr) {
  while (capacity() < src.size()) {
    reallocate();
  }
  for (auto i = 0u; i < src.size(); i++) {
    alloc.construct(mfirst_free, src[i]);
    mfirst_free++;
  }
}

template <typename T>
Vect<T>::Vect(Vect<T>&& src)
  : mdata(nullptr), mfirst_free(nullptr), mend(nullptr) {
  mdata = src.mdata;
  mfirst_free = src.mfirst_free;
  mend = src.mend;
  src.mdata = src.mend = src.mfirst_free = nullptr;
}

template <typename T>
const Vect<T>& Vect<T>::operator =(const Vect<T>& rhs) {
  if (this == &rhs) {
    return *this;
  }
  this->free();
  while (capacity() < rhs.size()) {
   // std::cout << __LINE__ << std::endl;
    reallocate();
  }
  for (auto i = 0u; i < rhs.size(); i++) {
    alloc.construct(mfirst_free, rhs[i]);
    mfirst_free++;
  }
  return *this;
}

template <typename T>
const Vect<T>& Vect<T>::operator =(Vect<T>&& rhs) {
  if (this == &rhs) {
    return *this;
  }
  this->free();
  mdata = rhs.mdata;
  mfirst_free = rhs.mfirst_free;
  mend = rhs.mend;
  rhs.mdata = rhs.mend = rhs.mfirst_free = nullptr;
  return *this;
}

template <typename T>
Vect<T>::~Vect() {
  this->free();
}

template <typename T>
const Vect<T>& Vect<T>::operator +=(const Vect<T>& rhs) {
  for (size_t i = 0; i < std::min(size(), rhs.size()); ++i) {
    this->operator[](i) += rhs[i];
  }
  return *this;
}

template <typename T>
const Vect<T>& Vect<T>::operator -=(const Vect<T>& rhs) {
  for (size_t i = 0; i < std::min(size(), rhs.size()); ++i) {
    this->operator[](i) -= rhs[i];
  }
  return *this;
}

template <typename T>
const Vect<T>& Vect<T>::operator *=(double alpha) {
  for (size_t i = 0; i < size(); ++i) {
    this->operator[](i) *= alpha;
  }
  return *this;
}

template <typename T>
double Vect<T>::two_norm() const {
  double sum = 0;
  for (size_t i = 0; i < size(); ++i) {
    sum += (this->operator[](i)) * (this->operator[](i));
  }
  return sqrt(sum);
}

template <typename T>
const Vect<T>& Vect<T>::push_back(const T& x) {
  if (size() >= capacity()) {
    reallocate();
  }
  alloc.construct(mfirst_free, x);
  mfirst_free++;
  return *this;
}

template <typename T>
void Vect<T>::free() {
  if (mdata == nullptr) {
    return;
  }
  for (auto* ptr = mdata; ptr != mfirst_free; ptr++) {
    alloc.destroy(ptr);
  }
  alloc.deallocate(mdata, capacity());
}

template <typename T>
void Vect<T>::reallocate() {
  if (mdata == nullptr) {
    mdata = alloc.allocate(1);
    mfirst_free = mdata;
    mend = mdata + 1;
    return;
  }
  auto cap = capacity();
  auto sz = size();
  auto* tmp = alloc.allocate(2 * cap);
  std::uninitialized_copy(mdata, mfirst_free, tmp);
  this->free();

  mdata = tmp;
  mend = mdata + 2 * cap;
  mfirst_free = mdata + sz;
}

template <typename T>
Vect<T> operator +(const Vect<T>& a, const Vect<T>& b) {
  auto ret{a};
  ret += b;
  return ret;
}

template <typename T>
Vect<T> operator -(const Vect<T>& a, const Vect<T>& b) {
  auto ret{a};
  ret -= b;
  return ret;
}

template <typename T>
std::ostream& operator <<(std::ostream& stream, const Vect<T>& v) {
  if (v.size() == 0u) {
    return stream << "[]";
  }
  stream << "[";
  for (size_t i = 0; (i + 1) < v.size(); i++) {
    stream << v[i] << ",";
  }
  return stream << v[v.size() - 1] << "]";
}
