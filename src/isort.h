#ifndef _ISORT_H_ 
#define _ISORT_H_ 

#include <vector>
#include <algorithm>

// Verzija s indeksima
template <typename Record>
void insertion_sort_ind(std::vector<Record> & vec) {
   // Vaša implementacija
  for (int i = 1; i < static_cast<int>(vec.size()); ++i) {
    int first_bigger = i;
    for (int j = 0; j < i; ++j) {
      if (!(vec[j] < vec[i])) {
        first_bigger = j;
        break;
      }
    }
    if (first_bigger == i) {
      continue;
    }
    auto tmp = vec[i];
    for (int j = i; j > first_bigger; --j) {
      vec[j] = vec[j - 1];
    }
    vec[first_bigger] = tmp;
  }
}


// Verzija koja uzima iterator range -- koristiti samo std::next i std::prev
template <typename Iter>
void insertion_sort(Iter first, Iter last) {
   // Vaša implementacija
  for (auto it = std::next(first); it != last; it = std::next(it)) {
    auto cur = it;
    for (auto it2 = first; it2 != it; it2 = std::next(it2)) {
      if (!(*it2 < *it)) {
        cur = it2;
        break;
      }
    }
    if (cur == it) {
      continue;
    }
    auto tmp = *it;
    for (auto it2 = it; it2 != cur; it2 = std::prev(it2)) {
      *it2 = *std::prev(it2);
    }
    *cur = tmp;
  }
}

// verzija sa algoritmima std::rotate i std::upper_bound
template <typename Iter>
void insertion_sort1(Iter first, Iter last) {
   // Vaša implementacija
  for (auto it = first; it != last; ++it) {
    auto from = std::upper_bound(first, it, *it);
    std::rotate(from, it, it + 1);
  }
}


#endif
