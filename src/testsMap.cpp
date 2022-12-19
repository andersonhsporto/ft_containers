//
// Created by Anderson Porto on 12/11/22.
//


#include "../includes/0-Utilities/testsMap.hpp"
#include <iostream>

#if STD == 1
    #include <map>
	namespace ft = std;
#else
  #include "../includes/3-map/map.hpp"
#endif

void testMap() {
  testElementAccess();
  testBeginIterator();
}

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

void testRendIterator() {
  ft::map<const char *, std::string> map;

  map["a"] = "È a";
  map["b"] = "È b";
  map["c"] = "È c";
  map["dado"] = "È dado";
  map["hexa"] = "È hexa";

  ft::map<const char *, std::string>::reverse_iterator it = map.rend();
  ft::map<const char *, std::string>::const_reverse_iterator it2 = map.rend();

  std::cout << "map.rend chave = " << it->first << std::endl;
  std::cout << "map.rend valor = " << it->second << std::endl;
}

void testEmpty() {
  ft::map<int, int> map;
  ft::map<int, int> emptyMap;

  map[1] = 10;
  map[2] = 30;
  map[3] = 50;
  map[4] = 70;
  map[5] = 1;

  std::cout << "map.empty() = " << map.empty() << std::endl;
  std::cout << "emptyMap.empty() = " << emptyMap.empty() << std::endl;
}

void testSize() {
  ft::map<int, int> map;
  ft::map<int, int> emptyMap;

  for (int i = 0; i < 1042; i++) {
    map[i] = i;
  }

  std::cout << "map.empty() = " << map.empty() << std::endl;
  std::cout << "emptyMap.empty() = " << emptyMap.empty() << std::endl;
}

void testClear() {
  ft::map<int, int> map;

  map[1] = 10;
  map[2] = 30;
  map[3] = 50;
  map[4] = 70;
  map[5] = 1;

  std::cout << "map.size() = " << map.size() << std::endl;
  map.clear();
  std::cout << "map.size() = " << map.size() << std::endl;
}

void testInsert() {
  ft::map<int, int> map;

  map.insert(ft::pair<int, int>(1, 10));
  map.insert(ft::pair<int, int>(2, 30));
  map.insert(ft::pair<int, int>(3, 50));
  map.insert(ft::pair<int, int>(4, 70));
  map.insert(ft::pair<int, int>(5, 1));

  ft::map<int, int>::iterator it = map.begin();
  ft::map<int, int>::const_iterator it2 = map.begin();

  std::cout << "map.begin chave = " << it->first << std::endl;
  std::cout << "map.begin valor = " << it->second << std::endl;

  std::cout << "const map.begin chave = " << it2->first << std::endl;
  std::cout << "const map.begin valor = " << it2->second << std::endl;
}
