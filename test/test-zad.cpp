#include "gtest/gtest.h"
#include "../src/lista.h"
#include "test-lista.h"

#include <string>
#include <fstream>
#include <stdexcept>
#include <iterator>
 

using namespace std;

// Lista tipova za koje ćemo vršiti testove
typedef ::testing::Types<int, double> MyTypes;
TYPED_TEST_CASE(ListTest, MyTypes);

TYPED_TEST(ListTest, size) {
    // Test defaultnog konstruktora
  ASSERT_EQ(this->l.empty(), true);
  ASSERT_EQ(this->l.size(), 0);
  ASSERT_EQ(this->get_mStart(), nullptr);
  ASSERT_EQ(this->get_mPosition(), nullptr);
  ASSERT_EQ(this->get_mPositionIdx(), 0);
}

TYPED_TEST(ListTest, insert) {
    // Test ubacivanja jednog elementa
  this->l.insert(0,1);
  ASSERT_EQ(this->l.empty(), false);
  ASSERT_EQ(this->l.size(), 1);
  ASSERT_NE(this->get_mStart(), nullptr);
  ASSERT_NE(this->get_mPosition(), nullptr);
  ASSERT_EQ(this->get_mPositionIdx(), 0);
  ASSERT_EQ(this->l.current(), 1);

  this->l.remove(0);
  ASSERT_EQ(this->get_mStart(), nullptr);
  ASSERT_EQ(this->get_mPosition(), nullptr);
  ASSERT_EQ(this->get_mPositionIdx(), 0);
  ASSERT_EQ(this->l.empty(), true);
}

TYPED_TEST(ListTest, push_back){
     // Test push_back metode
    this->l.push_back(1);
    this->l.push_back(10);
    this->l.push_back(100);
    ASSERT_EQ(this->l.size(), 3);
    ASSERT_EQ(this->l.empty(), false);
    ASSERT_EQ(this->l.current(),100);
    this->l.setPosition(1);
    ASSERT_EQ(this->l.current(),10);
    this->l.remove(1);
    ASSERT_EQ(this->l.size(), 2);
    ASSERT_EQ(this->l.current(),1);
}

TYPED_TEST(ListTest, push_insert){
     // Test push_back metode
    this->l.push_back(1);
    this->l.push_back(10);
    this->l.push_back(100);
    this->l.insert(0,-1);
    ASSERT_EQ(this->l.current(),-1);
    ASSERT_EQ(this->l.size(), 4);
    this->l.insert(2,-10);
    ASSERT_EQ(this->l.current(),-10);
    this->l.setPosition(3);
    ASSERT_EQ(this->l.current(), 10);
    this->l.remove(3);
    ASSERT_EQ(this->l.current(), -10);
    this->l.current() = -20;
    ASSERT_EQ(this->l.current(), -20);
    this->l.remove(0);
    ASSERT_EQ(this->currentNode()->value,1);
}

TYPED_TEST(ListTest, values){
   this->l.insert(0,1);
   this->l.insert(0,2);
   this->l.insert(1,3);
   this->l.push_back(4);
   std::vector<TypeParam> v{2,3,1,4};
   for(std::size_t i =0; i<v.size(); ++i){
        this->l.setPosition(i);
       ASSERT_EQ(this->l.current(), v[i]);
   }
   this->l.remove(1);
   this->l.remove(1);
   this->l.remove(1);
   this->l.remove(0);
   ASSERT_EQ(this->l.empty(), true);
}

TYPED_TEST(ListTest, clear){
   this->l.insert(0,1);
   this->l.insert(0,2);
   this->l.insert(1,3);
   this->l.push_back(4);
   this->l.clear();
   ASSERT_EQ(this->l.size(), 0);
   ASSERT_EQ(this->l.empty(), true);

   ASSERT_EQ(this->get_mStart(), nullptr);
   ASSERT_EQ(this->get_mPosition(), nullptr);
   ASSERT_EQ(this->get_mPositionIdx(), 0);
}

TYPED_TEST(ListTest, sort){
   this->l.push_back(2);
   this->l.push_back(1);
   this->l.push_back(4);
   this->l.push_back(3);
   this->l.sort();
   this->l.setPosition(0);
   ASSERT_EQ(this->l.current(), 1);
   this->l.setPosition(1);
   ASSERT_EQ(this->l.current(), 2);
   this->l.setPosition(2);
   ASSERT_EQ(this->l.current(), 3);
   this->l.setPosition(3);
   ASSERT_EQ(this->l.current(), 4);

   this->l.clear();
   this->l.push_back(2);
   this->l.sort();
   this->l.setPosition(0);
   ASSERT_EQ(this->l.current(), 2);

   this->l.clear();
   this->l.insert(0, 11);
   this->l.insert(1, 10);
   this->l.insert(0, 12);
   this->l.sort();
   this->l.setPosition(0);
   ASSERT_EQ(this->l.current(), 10);
   this->l.setPosition(1);
   ASSERT_EQ(this->l.current(), 11);
   this->l.setPosition(2);
   ASSERT_EQ(this->l.current(), 12);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
