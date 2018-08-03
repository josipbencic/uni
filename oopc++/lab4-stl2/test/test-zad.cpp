#include "gtest/gtest.h"
#include "../src/zadatak.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iterator>
 
using namespace std;

TEST(STL2, procitaj_rijec) {
    std::string line = "a, \n";
    auto it = line.cbegin();
    std::string rijec = procitaj_rijec(it, line.cend());
    ASSERT_EQ (rijec, std::string("a"));
/////////////////////////////////////////////////////
    line = std::string("  ,bb????");
    it = line.cbegin();
    rijec = procitaj_rijec(it, line.cend());
    ASSERT_EQ (rijec, std::string("bb"));
//////////////////////////////////////////////////////
    line = std::string("\"sss\"");
    it = line.cbegin();
    rijec = procitaj_rijec(it, line.cend());
    ASSERT_EQ (rijec, std::string("sss"));
//////////////////////////////////////////////////////
    line = std::string("    !cc  ,bb?:; ww");
    it = line.cbegin();
    rijec = procitaj_rijec(it, line.cend());
    ASSERT_EQ (rijec, std::string("cc"));

    rijec = procitaj_rijec(it, line.cend());
    ASSERT_EQ (rijec, std::string("bb"));

    rijec = procitaj_rijec(it, line.cend());
    ASSERT_EQ (rijec, std::string("ww"));

    ASSERT_EQ( it, line.cend() );
}

TEST(STL2, procitaj_datoteku) {
    std::map<std::string, int> list;
    procitaj_datoteku("1.txt", list);
    ASSERT_EQ(list.size(),3u);
    ASSERT_EQ(list.count("a"), 1u);
    ASSERT_EQ(list.count("b"), 1u);
    ASSERT_EQ(list.count("c"), 1u);
    auto max =  naj(list);
    ASSERT_EQ(max.first.size(), 3u);
    ASSERT_EQ(max.second, 1);

    list.clear();
    procitaj_datoteku("2.txt", list);
    ASSERT_EQ(list.size(),3u);
    ASSERT_EQ(list.count("a"), 1u);
    ASSERT_EQ(list.count("b"), 1u);
    ASSERT_EQ(list.count("c"), 1u);
    ASSERT_EQ(list["a"], 1);
    ASSERT_EQ(list["b"], 3);
    ASSERT_EQ(list["c"], 4);
    max =  naj(list);
    ASSERT_EQ(max.first.size(), 1u);
    ASSERT_EQ(max.second, 4);

    list.clear();
    procitaj_datoteku("3.txt", list);
    ASSERT_EQ(list.size(),8u);
    ASSERT_EQ(list.count("wer"), 1u);
    ASSERT_EQ(list.count("cer"), 1u);
    ASSERT_EQ(list.count("nnn"), 1u);
    ASSERT_EQ(list.count("pp"), 1u);
    ASSERT_EQ(list.count("u"), 1u);
    ASSERT_EQ(list.count("uu"), 1u);
    ASSERT_EQ(list.count("Z"), 1u);
    ASSERT_EQ(list.count("3"), 1u);
    ASSERT_EQ(list["wer"], 2);
    ASSERT_EQ(list["u"], 4);
    ASSERT_EQ(list["Z"], 3);
    max =  naj(list);
    ASSERT_EQ(max.first.size(), 1u);
    ASSERT_EQ(max.second, 4);
}

TEST(STL2,naj){
    std::map<std::string, int> list;
    procitaj_datoteku("4.txt", list);
    auto max =  naj(list);
    ASSERT_EQ(max.first.size(), 2u);
    ASSERT_EQ(max.second, 3);
    ASSERT_EQ(*max.first.begin(), "a");
    ASSERT_EQ(*std::next(max.first.begin()), "c");
}

TEST(STL2,broj_is_grupe){
    std::multimap<std::string, std::string> grupe;
    grupe.insert(std::make_pair("Grupa1", "the"));
    grupe.insert(std::make_pair("Grupa1", "a"));

    grupe.insert(std::make_pair("Grupa2", "is"));
    grupe.insert(std::make_pair("Grupa2", "are"));

    std::map<std::string,int>  word_list;
    procitaj_datoteku("../src/text.txt", word_list);

    std::vector<int> broj;
    broj = broj_iz_grupe(word_list, grupe);

    ASSERT_EQ(broj.size(), 2u);
    ASSERT_EQ(broj[0], 44);
    ASSERT_EQ(broj[1], 21);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
