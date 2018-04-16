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
    explicit Vect(size_t n = 0, T v= {});  // Ctor
    // Kontrola kopiranja dolazi ovdje
    // CCtor
    // MCtor
    // OP
    // MOP
    // DTOR

    // dohvat elemenata (operator [])
    // push_back metoda

     // info rutine size() i capacity()

     // operatori +=, -=, *=
     // euklidska norma vraća double !
     double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)
  
        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

        // dodati vlastite privatne metode.
	
        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo 
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
};

// Deklaracija operator +, - i << 
template <typename T>

// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
