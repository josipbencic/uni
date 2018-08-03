#ifndef TEST_LISTA_H
#define TEST_LISTA_H

#include "gtest/gtest.h"
#include <cstddef>

template <typename T>
struct Node;

template <typename T>
class ListTest  : public ::testing::Test {
public:
     List<T> l;
     Node<T> * get_mStart() { return l.mStart; }
     Node<T> * get_mPosition() { return l.mPosition; }
     std::size_t get_mPositionIdx() { return l.mPositionIdx; }
     Node<T> * currentNode() { return l.currentNode(); }
};

#endif
