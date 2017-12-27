#include "gtest/gtest.h"
#include "../src/zadatak.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
 
using namespace std;

TEST(STL, Zadatak1) {
    std::vector<int> vec = zadatak1("../src/brojevi.txt");
	
    ASSERT_EQ ((int)vec.size(), 19);
    ASSERT_EQ (vec[0], 1) << vec[0] << " <> 1";
    ASSERT_EQ (vec[18], 19)<< vec[18] << " <> 19";
    ASSERT_EQ (vec[10], 9)<< vec[10] << " <> 9";
}

TEST(STL, Zadatak2) {
    zadatak2("../src/fpbrojevi.txt");

    ifstream in1("3cols.txt");
    if(!in1)
        throw runtime_error("Cannot open 3cols.txt");

    ifstream in2("../src/3cols.txt");
    if(!in2)
        throw runtime_error("Cannot open ../src/3cols.txt");

    std::string line1, line2;
    std::getline(in1, line1);
    std::getline(in2, line2);
    EXPECT_STREQ(line1.c_str(), line2.c_str());
    std::getline(in1, line1);
    std::getline(in2, line2);
    EXPECT_STREQ(line1.c_str(), line2.c_str());
    std::getline(in1, line1);
    std::getline(in2, line2);
    EXPECT_STREQ(line1.c_str(), line2.c_str());
    in1.close();
    in2.close();
}




TEST(STL, Zadatak3) {

	std::list<int> l = zadatak3();
    auto it = l.begin();
    ASSERT_EQ(*it, 5);
    it++;
    ASSERT_EQ(*it, 1);
    it++;
    ASSERT_EQ(*it, 2);
    it++;
    ASSERT_EQ(*it, 4);
    it++;
    ASSERT_EQ(*it, 5);
    it++;
    ASSERT_EQ(*it, 6);
    it++;
    ASSERT_EQ(*it, 3);
    it++;
    ASSERT_EQ(*it, 4);
    it++;
    ASSERT_EQ(*it, 6);
    it++;
    ASSERT_EQ(*it, 7);
    it++;
    ASSERT_EQ(*it, 8);
    it++;
    ASSERT_EQ(*it, 9);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
