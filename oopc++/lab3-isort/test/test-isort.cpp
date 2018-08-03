#include "gtest/gtest.h"
#include "../src/isort.h"
#include <vector>
#include <string>
#include <list>
#include <stdexcept>
 
using namespace std;

TEST(isort, Zadatak) {

    std::vector<int> sorted{1,3,3,5,6,7,8};
    std::vector<int> polje{5,3,7,8,1,3,6};
    insertion_sort_ind(polje);
    ASSERT_EQ(polje, sorted); 

//    std::copy(polje.begin(), polje.end(), std::ostream_iterator<int>(std::cout,","));
//    std::cout << "\n";

    std::vector<std::string> dict{"zui", "rtz", "jkh", "dft", "qwe","aaa"};
    insertion_sort_ind(dict);
//    std::copy(dict.begin(), dict.end(), std::ostream_iterator<std::string>(std::cout,","));
//    std::cout << "\n";

    std::vector<int> polje2{5,3,7,8,1,3,6};
    insertion_sort(polje2.begin(), polje2.end());
    ASSERT_EQ(polje2, sorted); 
//    std::copy(polje2.begin(), polje2.end(), std::ostream_iterator<int>(std::cout,","));
//    std::cout << "\n";

    std::vector<std::string> dict2{"zui", "rtz", "jkh", "dft", "qwe","aaa"};
    insertion_sort(dict2.begin(), dict2.end());
//    std::copy(dict2.begin(), dict2.end(), std::ostream_iterator<std::string>(std::cout,","));
//    std::cout << "\n";

    std::vector<int> polje1{5,3,7,8,1,3,6};
    insertion_sort1(polje1.begin(), polje1.end());
    ASSERT_EQ(polje1, sorted); 
//    std::copy(polje1.begin(), polje1.end(), std::ostream_iterator<int>(std::cout,","));
//    std::cout << "\n";

    std::vector<std::string> dict1{"zui", "rtz", "jkh", "dft", "qwe","aaa"};
    insertion_sort1(dict1.begin(), dict1.end());
 //   std::copy(dict1.begin(), dict1.end(), std::ostream_iterator<std::string>(std::cout,","));
//    std::cout << "\n";


    std::list<int> sortedlist{1,3,3,5,6,7,8};
    std::list<int> list1{5,3,7,8,1,3,6};
    insertion_sort(list1.begin(), list1.end());
    ASSERT_EQ(list1, sortedlist); 
//    std::copy(list1.begin(), list1.end(), std::ostream_iterator<int>(std::cout,","));
//    std::cout << "\n";

    std::list<std::string>list2{"zui", "rtz", "jkh", "dft", "qwe","aaa"};
    insertion_sort(list2.begin(), list2.end());
//    std::copy(list2.begin(), list2.end(), std::ostream_iterator<std::string>(std::cout,","));
//    std::cout << "\n";



}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
