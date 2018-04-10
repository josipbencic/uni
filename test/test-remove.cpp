#include "gtest/gtest.h"
#include "../src/bin_stablo.h"
#include <string>
#include <stdexcept>
#include <vector>
 
using namespace std;


TEST(BST, remove) {
    BinarySTree<int> t;
    t.insert(7);
    t.insert(5);
    t.insert(6);
    t.insert(9);
    t.insert(8);
    ASSERT_EQ(t.remove(5), success);
    std::vector<int> v;
    t.inOrder([&v](int x){v.push_back(x);});
    std::vector<int> vv{6,7,8,9};
    ASSERT_EQ(v, vv);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
