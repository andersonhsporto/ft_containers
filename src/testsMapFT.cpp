//
// Created by Anderson Porto on 12/11/22.
//

#include "../includes/3-map/map.hpp"
#include <iostream>

void testElementAccess() {
  ft::map<char, int> map;

  map['a'] = 10;
  map['b'] = 30;
  map['c'] = 50;

  std::cout << "map['a'] = " << map['a'] << std::endl;
  std::cout << "map['b'] = " << map['b'] << std::endl;
  std::cout << "map['c'] = " << map['c'] << std::endl;

  std::cout << "map.at('a') = " << map.at('a') << std::endl;
  std::cout << "map.at('b') = " << map.at('b') << std::endl;
  std::cout << "map.at('c') = " << map.at('c') << std::endl;
}

void testBeginIterator() {
  ft::map<int, int> map;

  map[1] = 10;
  map[2] = 30;
  map[3] = 50;
  map[4] = 70;
  map[5] = 1;

  ft::map<int, int>::iterator it = map.begin();
  ft::map<int, int>::const_iterator it2 = map.begin();

  std::cout << "map.begin chave = " << it->first << std::endl;
  std::cout << "map.begin valor = " << it->second << std::endl;

  std::cout << "const map.begin chave = " << it2->first << std::endl;
  std::cout << "const map.begin valor = " << it2->second << std::endl;
}

void testEndIterator() {
  ft::map<int, int> map;

  map[1] = 10;
  map[2] = 30;
  map[3] = 50;
  map[4] = 70;
  map[5] = 1;

  ft::map<int, int>::iterator it = map.end();
  ft::map<int, int>::const_iterator it2 = map.end();

  std::cout << "map.end chave = " << it->first << std::endl;
  std::cout << "map.end valor = " << it->second << std::endl;

  std::cout << "const map.end chave = " << it2->first << std::endl;
  std::cout << "const map.end valor = " << it2->second << std::endl;
}

void testRbeginIterator() {
  ft::map<const char *, std::string> map;

  map["a"] = "È a";
  map["b"] = "È b";
  map["c"] = "È c";
  map["dado"] = "È dado";
  map["hexa"] = "È hexa";

  ft::map<const char *, std::string>::reverse_iterator it = map.rbegin();
  ft::map<const char *, std::string>::const_reverse_iterator it2 = map.rbegin();

  std::cout << "map.rbegin chave = " << it->first << std::endl;
  std::cout << "map.rbegin valor = " << it->second << std::endl;
}