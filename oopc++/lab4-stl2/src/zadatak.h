#ifndef __ZADATAK_IS_INCLUDED__             
#define __ZADATAK_IS_INCLUDED__             


#include <string>
#include <map>
#include <list>
#include <vector>

// Zadan je raspon iteratora unutar stringa. Pročitati i vratiti prvu riječ iz stringa.
// Postaviti iterator it na prvu interpunkciju/bjelinu iza pročitane riječi ili na itend
// (end-iterator) ako takve nema.
// Riječi su cjeline međusobno odvojene bjelinama i/ili interpunkcijama: ,.!?:;()
// Bjeline su  \n\t\v.
std::string procitaj_rijec(std::string::const_iterator & it, std::string::const_iterator itend);

// Otvoriti datoteku file_name za čitanje, učitati tekst (npr. liniju po liniju)
// i smjestiti riječi u mapu. Riječ je ključ, a vrijednost je broj pnavljanja riječi.
// Riječ se učitava pomoću rutine ucitaj_rijec.
void procitaj_datoteku(std::string file_name, std::map<std::string,int> & word_list);

// Vrati listu riječi koje se najčešće pojavljuju u mapi (std::list) i broj ponavljanja (int).
std::pair<std::list<std::string>, int> naj(std::map<std::string,int> const & word_list);

// Argument grupe sadrži grupe riječi (ključ je ime grupe, a vrijednosti
// su riječi koje pripadaju grupi).
// Funkcija treba za svaku grupu riječi sumirati broj pojavljivanja svih riječi
// iz grupe u tekstu te vratiti vrijednosti u vektoru. Na i-tom mjestu u povratnom vektoru
// je broj pojavljivanja riječi iz i-te grupe (prema uređaju u multimap varijabli).
// Argument word_list je std::map svih riječi s brojem njihovih pojavljivanja.
std::vector<int>
broj_iz_grupe(std::map<std::string,int> const & word_list,
              std::multimap<std::string, std::string> const & grupe);

#endif
