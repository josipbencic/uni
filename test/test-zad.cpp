#include "gtest/gtest.h"
#include "../src/zadatak.h"
#include <vector>
 
TEST(Zadatak1, Vrijednosti) { 
	std::vector<int> vec = zadatak1("../../src/brojevi.txt");
	
    ASSERT_EQ (vec.size(), 19);
    ASSERT_EQ (vec[0], 1);
    ASSERT_EQ (vec[18], 19);
    ASSERT_EQ (vec[10], 9);

}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
