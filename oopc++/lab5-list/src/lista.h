#ifndef LISTA_H
#define LISTA_H 

#include <cstddef>  // za std::size_t
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <utility>

template <typename> class ListTest;

// Paramtrizirana struktura koja predstavlja čvor u listi.
// Sadrži vrijednost (value) i pokazivače na prethodni i sljedeći
// element u listi.
template <typename T>
struct Node{
	T value{};
	Node * previous = nullptr;
	Node * next = nullptr;
};

/**
 * Dvostruko povezana lista s elementima indeksiranim cjelobrojnim indeksima.
 * Indeksi elemenata počinju s nulom. Sve metode koje uzimaju indeks provjeravaju
 * da li je unutar granica i u suprotnom izbacuju std::runtime_error.  
 **/
template <typename T>
class List{
    friend class ListTest<T>;
	public:
		// Konstruktor
		List() :  mSize(0), mPositionIdx(0), mStart(nullptr), mPosition(nullptr) {}
		// Destruktor
		~List() { clear(); }
		// Obriši (dealociraj) sve elemente liste. 
		void clear();
		// Da li je lista prazna?
		bool empty() const;
		// Broj elemenata u listi. 
		std::size_t size() const;
		// Ubaci element "t" na poziciju "i" u listi. Pozicija "i" mora biti važeća 
		// i tada se element ubacuje na to mjesto, a prijašnji "i"-ti element postaje 
		// "i"+1-vi element. Pozicija "i" može biti jednaka size()  i tada se element ubacuje na kraj liste. 
		// Metoda mora ispravno ubacivati i u praznu listu. Metoda pozicionira listu na novom
		// i-tom elementu (pozivom metode setPosition()). 
  // Novi element se alocira dinamički pomoću new operatora.
		void insert(std::size_t i, T const & t);
		// Izbaciti element iz liste i dealocirati ga pomoću delete. Trenutna pozicija
		// nakon izbacivanja pokazuje na prethodni element ako postoji; kada se izabacuje prvi element
		// onda pokazuje na novi prvi element ili lista ostaje prazna. 
		void remove(std::size_t i);
		// Postaviti trenutnu poziciju na i-to mjesto. Dozvoljeni "i" ide od 0 do 
		// size()-1. Inače izbaci izuzetak std::runtime_error.
		void setPosition(std::size_t i) const;
		// Vrati selektirani element. Konstantan verzija.
  T const & current() const;
		// Vrati selektirani element. Nekonstantna verzija.
  T & current();
  // Dodaje element na kraj liste. Listu pozicionira na novom elementu.
		void push_back(T const & t);
  // Sortira listu pomoću operatora <. Implementirati "insertion sort".
  void sort();
	private:
	   std::size_t mSize;
	   mutable std::size_t mPositionIdx;
            Node<T> * mStart;
	   mutable Node<T> * mPosition;

	   // Vrati pokazivač na selektirani node.
	   Node<T> * currentNode() { return mPosition; }
};


template <typename T>
bool List<T>::empty() const {
  // Implementacija
  return mSize == 0;
}

template <typename T>
std::size_t List<T>::size() const { return mSize; }

template <typename T>
T const & List<T>::current() const {
 // Implementacija
  assert(mPosition != nullptr);
  return mPosition->value;
}

template <typename T>
T & List<T>::current() {
 // Implementacija
  assert(mPosition != nullptr);
  return mPosition->value;
}

template <typename T>
void List<T>::setPosition(std::size_t i) const {
 // Implementacija
  if (i >= mSize) {
    throw std::runtime_error("Index out of bounds!");
    return;
  }
  if (i == mPositionIdx) {
    assert(mPosition != nullptr);
    return;
  }
  if (i == 0) {
    mPosition = mStart;
    mPositionIdx = 0;
    return;
  }

  while (i < mPositionIdx) {
    mPosition = mPosition->previous;
    mPositionIdx--;
  }

  while (i > mPositionIdx) {
    assert(mPosition != nullptr);
    assert(mPositionIdx < mSize);
    mPosition = mPosition->next;
    mPositionIdx++;
  }
  assert(mPosition != nullptr);
}

template <typename T>
void List<T>::insert(std::size_t i, T const & t) {
   // Implementacija
  if (i > mSize) {
     throw std::runtime_error("Index out of bounds!");
     return;
  }
  auto* tmp = new Node<T>{};
  tmp->value = t;

  if (mSize == 0) {
    mSize++;
    mStart = tmp;
    mPosition = tmp;
    mPositionIdx = 0;
    return;
  }

  if (i == mSize) {
    auto* it = mStart;
    for (; it->next != nullptr; it = it->next);
    it->next = tmp;
    tmp->previous = it;
    mPositionIdx = i;
    mPosition = tmp;
    mSize++;
    return;
  }

  setPosition(i);

  if (i == 0) {
    tmp->next = mStart;
    mStart->previous = tmp;
    mStart = tmp;
    mSize++;
    mPosition = mStart;
    mPositionIdx = 0;
    return;
  }

  auto* prev = mPosition->previous;
  prev->next = tmp;
  mPosition->previous = tmp;
  tmp->previous = prev;
  tmp->next = mPosition;

  mSize++;
  mPositionIdx++;
  setPosition(i);
}

template <typename T>
void List<T>::remove(std::size_t i){
 // Implementacija
  setPosition(i);

  assert(mPosition != nullptr);

  auto* prev = mPosition->previous;
  auto* next = mPosition->next;
  if (prev != nullptr) {
    prev->next = mPosition->next;
  }
  if (next != nullptr) {
    next->previous = mPosition->previous;
  }
  delete mPosition;
  mSize--;

  if (empty()) {
    mStart = nullptr;
    mPosition = nullptr;
    mPositionIdx = 0;
    mSize = 0;
  }
  else if (prev != nullptr) {
    mPosition = prev;
    mPositionIdx = i - 1;
  }
  else {
    mStart = next;
    mPosition = next;
    mPositionIdx = i;
  }
}

template <typename T>
void List<T>::clear(){
 // Implementacija
  if (empty()) {
    return;
  }
  for (auto* it = mStart; it->next != nullptr; it = it->next) {
    delete it->next;
  }
  delete mStart;
  mStart = nullptr;
  mPosition = nullptr;
  mSize = 0;
  mPositionIdx = 0;
}

template <typename T>
void List<T>::push_back(T const & t) {
 // Implementacija
 insert(size(), t);
}

template <typename T>
void List<T>::sort() {
  if (empty()) {
    return;
  }
  // Implementacija
  for (auto* it = mStart->next; it != nullptr; it = it->next) {
    auto* cur = it;
    for (auto* jt = mStart; jt != it; jt = jt->next) {
      if (!(jt->value < it->value)) {
        cur = jt;
        break;
      }
    }
    auto tmp = it->value;
    for (auto* jt = it; jt != cur; jt = jt->previous) {
      jt->value = jt->previous->value;
    }
    cur->value = tmp;
  }
}

#endif /* LISTA_H */
