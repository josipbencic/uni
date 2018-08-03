#include "gtest/gtest.h"
#include "../src/bin_stablo.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iterator>
#include <vector>
 
using namespace std;

TEST(BST, construstion) {
    BinarySTree<int> t;
    ASSERT_EQ(t.empty(), true);
    ASSERT_EQ(t.size(), 0);
}

TEST(BST, insert) {
    BinarySTree<int> t;
    t.insert(5);
    ASSERT_EQ(t.isInTree(5), true);
    t.insert(6);
    ASSERT_EQ(t.isInTree(6), true);
    t.insert(4);
    ASSERT_EQ(t.isInTree(4), true);
    ASSERT_EQ(t.isInTree(3), false);
    ASSERT_EQ(t.isInTree(11), false);
}

TEST(BST, postorder) {
    BinarySTree<int> t;
    t.insert(5);
    t.insert(6);
    t.insert(4);
    std::vector<int> v;
    t.postOrder([&v](int x){v.push_back(x);});
    std::vector<int> vv{4,6,5};
    ASSERT_EQ(v, vv);
}

TEST(BST, preorder) {
    BinarySTree<int> t;
    t.insert(7);
    t.insert(5);
    t.insert(6);
    t.insert(8);
    t.insert(4);
    std::vector<int> v;
    t.preOrder([&v](int x){v.push_back(x);});
    std::vector<int> vv{7,5,4,6,8};
    ASSERT_EQ(v, vv);
}
TEST(BST, inorder) {
    BinarySTree<int> t;
    t.insert(7);
    t.insert(5);
    t.insert(6);
    t.insert(9);
    t.insert(8);
    std::vector<int> v;
    t.inOrder([&v](int x){v.push_back(x);});
    std::vector<int> vv{5,6,7,8,9};
    ASSERT_EQ(v, vv);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
