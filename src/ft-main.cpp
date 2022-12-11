#include "../includes/3-map/map.hpp"
#include <iostream>

#include <list>
#include <map>

int main() {

  time_t start = time(NULL);
//
//  std::map<const char *, std::string> mapa;
//  mapa["a"] = "È a";
//  std::cout << "std: " << mapa.size() << std::endl;
//  //const iterator
//  std::map<const char *, std::string>::const_iterator std_it = mapa.begin();
//  try {
//    mapa.at("zap");
//  } catch (std::exception &e) {
//    std::cout << "std: " << e.what() << std::endl;
//  }
//
//
//
//
//  mapa.value_comp();
//
//  ft::map<const char *, std::string> mapa2;
//  mapa2["b"] = "È b";
//  std::cout << "ft : " << mapa2.size() << std::endl;
//  // const iterator
//  ft::map<const char *, std::string>::const_iterator it = mapa2.begin();
//  std::cout << "const iterator: " << it->first << std::endl;
//  std::cout << "const iterator: " << it->second << std::endl;
//
//  // iterator
//  // iterator
//  std::map<const char *, std::string>::iterator std_it2 = mapa.begin();
//  ft::map<const char *, std::string>::iterator it2 = mapa2.begin();
//
//    // Erase
//    std::cout << "STD ERASE: " << mapa.erase("a") << std::endl;
//    std::cout << "FT ERASE: " << mapa2.erase("b") << std::endl;
//
//  std::cout << "size: " << mapa.size() << std::endl;
//    std::cout << "size: " << mapa2.size() << std::endl;
//
//
//
//  mapa2.value_comp();
//
////  std::list <ft::map<char, int>::value_type> lst2;
////  ft::map<char, int> mp2(lst2.begin(), lst2.end());
////
////  mp2.insert(mp2.begin(), ft::pair<char, int>('a', 1));
//
//
////
////  std::cout << "mp2.size() = " << mp2.size() << std::endl;

  time_t end = time(NULL);
  std::cout << "Time taken by program is:\t" << end - start << " seconds" << std::endl;
  return 0;
}

