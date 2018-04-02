#include "zadatak.h"
// Ubaciti potrebne include datoteke
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <cassert>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cctype>

// Zadan je raspon iteratora unutar stringa. Pročitati i vratiti prvu riječ iz stringa.
// Postaviti iterator it na prvu interpunkciju/bjelinu iza pročitane riječi ili na itend
// (end-iterator) ako takve nema.
// Riječi su cjeline međusobno odvojene bjelinama i/ili interpunkcijama: ,.!?:;()
// Bjeline su  \n\t\v.
std::string procitaj_rijec(std::string::const_iterator & it, std::string::const_iterator itend)
{
  // implementacija
  std::set<char> separators;
  {
    std::string str = ",.!?:;()\"";
    for (auto ch : str) {
      separators.insert(ch);
    }
    //std::copy(separators.begin(), separators.end(), std::ostream_iterator<char>(std::cout, "]"));
  }
  auto skip = [&](char x) -> bool {
    return separators.find(x) != separators.end() || isspace(x);
  };

  std::string ret;
  for (; it != itend; ++it) {
    if (skip(*it)) {
      continue;
    }
    while (it != itend && !skip(*it)) {
      ret.push_back(*it);
      ++it;
    }
    break;
  }
  return ret;
}

// Otvoriti datoteku file_name za čitanje, učitati tekst (npr. liniju po liniju)
// i smjestiti riječi u mapu. Riječ je ključ, a vrijednost je broj pnavljanja riječi.
// Riječ se učitava pomoću rutine ucitaj_rijec.
void procitaj_datoteku(std::string file_name, std::map<std::string,int> & word_list){
  // implementacija
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error(std::string("Cannot open ") + file_name);
  }
  std::string line;
  while (std::getline(file, line, '\n')) {
    auto it = line.cbegin();
    while (it != line.cend()) {
      auto word = procitaj_rijec(it, line.cend());
      if (word == std::string()) {
        continue;
      }
      if (word_list.find(word) == word_list.end()) {
        word_list[word] = 1;
      }
      else {
        word_list[word]++;
      }
    }
  }
}

// Vrati listu riječi koje se najčešće pojavljuju u mapi (std::list) i broj ponavljanja (int).
std::pair<std::list<std::string>, int> naj(std::map<std::string,int> const & word_list){
  // implementacija

  std::list<std::string> ret;
  int M = 0;
  for (auto& word : word_list) {
    if (word.second > M) {
      ret = std::list<std::string>{word.first};
      M = word.second;
    }
    else if (word.second == M) {
      ret.push_back(word.first);
    }
  }
  return std::make_pair(ret, M);
}

// Argument grupe sadrži grupe riječi (ključ je ime grupe, a vrijednosti
// su riječi koje pripadaju grupi).
// Funkcija treba za svaku grupu riječi sumirati broj pojavljivanja svih riječi
// iz grupe u tekstu te vratiti vrijednosti u vektoru. Na i-tom mjestu u povratnom vektoru
// je broj pojavljivanja riječi iz i-te grupe (prema uređaju u multimap varijabli).
// Argument word_list je std::map svih riječi s brojem njihovih pojavljivanja.
std::vector<int>
broj_iz_grupe(std::map<std::string,int> const & word_list,
              std::multimap<std::string, std::string> const & grupe) {
  // implementacija
  std::vector<int> ret;
  std::map<std::string, int> id;
  int i = 0;
  for (auto& elem : grupe) {

    auto it_id = id.find(elem.first);
    if (it_id == id.end()) {
      id[elem.first] = i++;
      ret.push_back(0);
    }

    auto it_wl = word_list.find(elem.second);
    if (it_wl == word_list.end()) {
      continue;
    }
    ret[id[elem.first]] += it_wl->second;
  }
  return ret;
}
