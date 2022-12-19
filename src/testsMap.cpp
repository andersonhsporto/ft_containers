//
// Created by Anderson Porto on 12/11/22.
//


#include "../includes/0-Utilities/testsMap.hpp"
#include <iostream>

#if DEFAULT == 1
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
  std::cout << "TEST ELEMENT ACCESS [ ] and 'at'" << std::endl;
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

  std::cout << "------------------------" << std::endl;
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
  std::cout << "const map.rbegin chave = " << it2->first << std::endl;
  std::cout << "const map.rbegin valor = " << it2->second << std::endl;
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
  std::cout << "const map.rend chave = " << it2->first << std::endl;
  std::cout << "const map.rend valor = " << it2->second << std::endl;
}

void testConstIterator() {
  std::cout << "TEST CONST ITERATOR" << std::endl;
  ft::map<const char *, std::string> map;

  map["a"] = "È a";
  map["b"] = "È b";
  map["c"] = "È c";
  map["dado"] = "È dado";
  map["hexa"] = "È hexa";

  ft::map<const char *, std::string>::const_iterator it = map.begin();
  ft::map<const char *, std::string>::const_iterator it2 = map.end();

  std::cout << "map.begin chave = " << it->first << std::endl;
  std::cout << "map.begin valor = " << it->second << std::endl;

  std::cout << "map.end chave = " << it2->first << std::endl;
  std::cout << "map.end valor = " << it2->second << std::endl;
  std::cout << "------------------------" << std::endl;
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

void testInsert_char() {
  ft::map<char, int> map;

  map.insert(ft::pair<char, int>('a', 1));
  map.insert(ft::pair<char, int>('b', 2));
  map.insert(ft::pair<char, int>('c', 3));
  map.insert(ft::pair<char, int>('d', 4));
  map.insert(ft::pair<char, int>('e', 5));
  map.insert(ft::pair<char, int>('f', 6));
  map.insert(ft::pair<char, int>('g', 7));

  ft::map<char, int>::iterator it = map.begin();
  ft::map<char, int>::const_iterator it2 = map.begin();

  ft::map<char, int>::iterator end_it = map.end();

  while (it != end_it) {
    std::cout << "map.begin chave = " << it->first << std::endl;
    std::cout << "map.begin valor = " << it->second << std::endl;

    std::cout << "const map.begin chave = " << it2->first << std::endl;
    std::cout << "const map.begin valor = " << it2->second << std::endl;
    it++;
    it2++;
  }
}

void testInsert_emplace() {
  ft::map<int, int> map;

  map.insert(ft::pair<int, int>(1, 10));
  map.insert(ft::pair<int, int>(2, 30));
  map.insert(ft::pair<int, int>(3, 50));
  map.insert(ft::pair<int, int>(4, 70));
  map.insert(ft::pair<int, int>(5, 1));

  ft::map<int, int>::iterator it = map.begin();
  ft::map<int, int>::const_iterator it2 = map.begin();

  ft::map<int, int>::iterator end_it = map.end();

  while (it != end_it) {
    std::cout << "map.begin chave = " << it->first << std::endl;
    std::cout << "map.begin valor = " << it->second << std::endl;

    std::cout << "const map.begin chave = " << it2->first << std::endl;
    std::cout << "const map.begin valor = " << it2->second << std::endl;
    it++;
    it2++;
  }

  std::cout << "map.size() = " << map.size() << std::endl;
  std::cout << "---------------------------------" << std::endl;
}

void testErase() {
  ft::map<int, int> map;

  map[1] = 10;
  map[2] = 30;
  map[3] = 50;
  map[4] = 70;
  map[5] = 1;

  ft::map<int, int>::iterator it = map.begin();

  ft::map<int, int>::iterator end_it = map.end();

  while (it != end_it) {
    std::cout << "map.begin chave = " << it->first << std::endl;
    std::cout << "map.begin valor = " << it->second << std::endl;
    it++;
  }

  std::cout << "map.size() = " << map.size() << std::endl;

  std::cout << "Before erase Value 50, Size of map is: " << map.size() << std::endl;
  map.erase(3);
  std::cout << "After erase Value 50, Size of map is: " << map.size() << std::endl;

  ft::map<int, int>::iterator afterIt = map.begin();

  ft::map<int, int>::iterator afterEndIt = map.end();

  while (afterIt != afterEndIt) {
    std::cout << "map.begin chave = " << afterIt->first << std::endl;
    std::cout << "map.begin valor = " << afterIt->second << std::endl;
    afterIt++;
  }

  std::cout << "map.size() = " << map.size() << std::endl;
  std::cout << "---------------------------------" << std::endl;
}

void testEraseRange() {
  ft::map<char, std::string> map;

  map['a'] = "anderson";
  map['b'] = "bruno";
  map['c'] = "camila";
  map['d'] = "daniel";
  map['e'] = "eduarda";
  map['f'] = "fabiano";
  map['g'] = "gabriela";
  map['h'] = "helena";

  ft::map<char, std::string>::iterator it = map.begin();
  it++;

  ft::map<char, std::string>::iterator it2 = map.end();
  it2--;

  map.erase(it, it2);

  ft::map<char, std::string>::iterator afterIt = map.begin();
  ft::map<char, std::string>::iterator afterEndIt = map.end();

  while (afterIt != afterEndIt) {
    std::cout << "map.begin chave = " << afterIt->first << std::endl;
    std::cout << "map.begin valor = " << afterIt->second << std::endl;
    afterIt++;
  }
}

void testSwap() {
  ft::map<float, std::string> map_1;
  ft::map<float, std::string> map_2;

  map_1[1.1] = "Anderson_1";
  map_1[2.2] = "bruno_1";

  map_2[1.1] = "Anderson_2";
  map_2[2.2] = "bruno_2";
  map_2[3.3] = "camila_2";

  std::cout << "Size of map 1 = " << map_1.size() << std::endl;
  std::cout << "Size of map 2 = " << map_2.size() << std::endl;

  std::cout << "Before Swap" << std::endl;

  std::cout << "map_1[1.1] = " << map_1[1.1] << std::endl;
  std::cout << "map_1[2.2] = " << map_1[2.2] << std::endl;

  std::cout << "map_2[1.1] = " << map_2[1.1] << std::endl;
  std::cout << "map_2[2.2] = " << map_2[2.2] << std::endl;
  std::cout << "map_2[3.3] = " << map_2[3.3] << std::endl;

  map_1.swap(map_2);

  std::cout << "After Swap" << std::endl;

  std::cout << "Size of map 1 = " << map_1.size() << std::endl;
  std::cout << "Size of map 2 = " << map_2.size() << std::endl;

  std::cout << "map_1[1.1] = " << map_1[1.1] << std::endl;
  std::cout << "map_1[2.2] = " << map_1[2.2] << std::endl;
  std::cout << "map_1[3.3] = " << map_1[3.3] << std::endl;

  std::cout << "map_2[1.1] = " << map_2[1.1] << std::endl;
  std::cout << "map_2[2.2] = " << map_2[2.2] << std::endl;
}

void testCount() {
  ft::map<int, int> map;

  map[1] = 10;
  map[2] = 30;
  map[3] = 50;
  map[4] = 70;
  map[5] = 1;

  std::cout << "map.count(1) = " << map.count(1) << std::endl;
  std::cout << "map.count(2) = " << map.count(2) << std::endl;
  std::cout << "map.count(3) = " << map.count(3) << std::endl;
  std::cout << "map.count(4) = " << map.count(4) << std::endl;
  std::cout << "map.count(5) = " << map.count(5) << std::endl;
  std::cout << "map.count(6) = " << map.count(6) << std::endl;
  std::cout << "map.count(42) = " << map.count(42) << std::endl;
}

void testFind() {
  ft::map<int, std::string> map;

  map[1] = "Frodo";
  map[2] = "Sam";
  map[3] = "Merry";
  map[4] = "Pippin";
  map[5] = "Gandalf";
  map[6] = "Aragorn";
  map[7] = "Legolas";
  map[8] = "Gimli";
  map[9] = "Boromir";

  ft::map<int, std::string>::iterator it = map.find(5);

  std::cout << "Chave 5 ( Mithrandir ) = " << it->first << std::endl;
  std::cout << "Valor 5 ( Mithrandir ) = " << it->second << std::endl;

  it = map.find(42);

  if (it == map.end()) {
    std::cout << "Chave 42 nao encontrada" << std::endl;
  }

  ft::map<int, std::string>::const_iterator constIt = map.find(5);
  ft::map<int, std::string>::const_iterator constEndIt = map.end();

  std::cout << "Sociedade do Anel A Partir do Iterador 'Olórin'" << std::endl;
  while (constIt != constEndIt) {
    std::cout << "Chave = " << constIt->first << std::endl;
    std::cout << "Valor = " << constIt->second << std::endl;
    constIt++;
  }

  ft::map<int, std::string>::reverse_iterator reverseIt = map.rbegin();
  ft::map<int, std::string>::reverse_iterator reverseEndIt = map.rend();

  std::cout << "Sociedade do Anel A Partir do Iterador 'Boromir'" << std::endl;

  while (reverseIt != reverseEndIt) {
    std::cout << "Chave = " << reverseIt->first << std::endl;
    std::cout << "Valor = " << reverseIt->second << std::endl;
    reverseIt++;
  }
  std::cout << "---------------------------------" << std::endl;
}

void testEqualRange() {
  ft::map<int, std::string> map;

  map[1] = "Frodo";
  map[2] = "Sam";
  map[3] = "Merry";
  map[4] = "Pippin";
  map[5] = "Gandalf";
  map[6] = "Aragorn";
  map[7] = "Legolas";
  map[8] = "Gimli";
  map[9] = "Boromir";

  ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ret;

  ret = map.equal_range(5);

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << std::endl;

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << std::endl;
}

void testEqualRange2() {
  ft::map<char, int> mymap;

  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;

  ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void testConstEqualRange() {
  ft::map<int, std::string> map;

  map[1] = "Frodo";
  map[2] = "Sam";
  map[3] = "Merry";
  map[4] = "Pippin";
  map[5] = "Gandalf";
  map[6] = "Aragorn";
  map[7] = "Legolas";
  map[8] = "Gimli";
  map[9] = "Boromir";

  ft::pair<ft::map<int, std::string>::const_iterator, ft::map<int, std::string>::const_iterator>
      ret;

  ret = map.equal_range(5);

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << std::endl;

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << std::endl;

  ft::map<int, std::string>::const_iterator constIt = map.begin();

  std::cout << "Sociedade do Anel A Partir do Iterador 'Olórin'" << std::endl;
  while (constIt != map.end()) {
    std::cout << "Chave = " << constIt->first << std::endl;
    std::cout << "Valor = " << constIt->second << std::endl;
    constIt++;
  }

  std::cout << "---------------------------------" << std::endl;
}

void lowerBound() {
  ft::map<char, int> map;

  map['a'] = 10;
  map['b'] = 20;
  map['c'] = 30;

  ft::map<char, int>::iterator it = map.lower_bound('b');
  ft::map<char, int>::const_iterator constIt = map.lower_bound('b');

  std::cout << "lower bound points to: " << std::endl;
  std::cout << "Chave: " << it->first << " => " << "Valor: " << it->second << std::endl;
  std::cout << "Const Chave: " << constIt->first << " => " << "Const Valor: " << constIt->second
            << std::endl;
  std::cout << "---------------------------------" << std::endl;
}

void testUpperBound() {
  ft::map<char, int> map;

  map['a'] = 10;
  map['b'] = 20;
  map['c'] = 30;

  ft::map<char, int>::iterator it = map.upper_bound('b');
  ft::map<char, int>::const_iterator constIt = map.upper_bound('b');

  std::cout << "upper bound points to: " << std::endl;
  std::cout << "Chave: " << it->first << " => " << "Valor: " << it->second << std::endl;
  std::cout << "Const Chave: " << constIt->first << " => " << "Const Valor: " << constIt->second
            << std::endl;
  std::cout << "---------------------------------" << std::endl;
}

void testKeyComp() {
  ft::map<char, int> map;

  map['x'] = 1001;
  map['y'] = 2002;
  map['z'] = 3003;

  // Create a key comparer using the map's key_comp() function
  ft::map<char, int>::key_compare mycomp = map.key_comp();

  std::cout << "map contains:" << std::endl;

  // Get the key value of the last element in the map
  char highest = map.rbegin()->first;

  // Create an iterator pointing to the first element in the map
  ft::map<char, int>::iterator it = map.begin();

  // Iterate through each element in the map
  do {
    // Print out the element's key and value
    std::cout << it->first << " => " << it->second << std::endl;
  } while (mycomp((*it++).first,
                  highest)); // The loop breaks when the current element's key is equal to the highest key.

  std::cout << std::endl;
  std::cout << "---------------------------------" << std::endl;
}

void testValueComp() {
  ft::map<int, char> map;

  map[1] = 'a';
  map[2] = 'b';
  map[3] = 'c';
  map[4] = 'd';
  map[5] = 'e';
  map[6] = 'f';

  ft::map<int, char>::iterator iter = map.begin();
  ft::pair<int, char> high = *map.rbegin();

  while (map.value_comp()(*iter, high)) {
    std::cout << iter->first << " => " << iter->second << std::endl;
    iter++;
  }

  ft::pair<int, char> copy = ft::make_pair(1, 'a');

  ft::map<int, char>::iterator begin = map.begin();
  if (map.value_comp()(*begin, copy)) {
    std::cout << "begin < copy" << std::endl;
  } else {
    std::cout << "begin >= copy" << std::endl;
  }

  std::cout << "---------------------------------" << std::endl;
}

void testsOperator() {
  ft::map<char, int> map;

  map['a'] = 10;
  map['b'] = 20;
  map['c'] = 30;

  ft::map<char, int> copy(map);

  ft::map<char, int> different(copy);

  different['a'] = 100;
  different['z'] = 1000;

  std::cout << "map == copy: " << (map == copy) << std::endl;
  std::cout << "map == different: " << (map == different) << std::endl;

  std::cout << "map != copy: " << (map != copy) << std::endl;
  std::cout << "map != different: " << (map != different) << std::endl;

  std::cout << "map < copy: " << (map < copy) << std::endl;
  std::cout << "map < different: " << (map < different) << std::endl;

  std::cout << "map <= copy: " << (map <= copy) << std::endl;
  std::cout << "map <= different: " << (map <= different) << std::endl;

  std::cout << "map > copy: " << (map > copy) << std::endl;
  std::cout << "map > different: " << (map > different) << std::endl;

  std::cout << "map >= copy: " << (map >= copy) << std::endl;
  std::cout << "map >= different: " << (map >= different) << std::endl;

  std::cout << "---------------------------------" << std::endl;
}

void testSlowOperation() {
  ft::map<int, int> map;

  for (int i = 0; i < 20000; i++) {
    map.insert(ft::make_pair(i, i));
  }
  std::cout << "Tteste;\n";

  std::cout << "---------------------------------" << std::endl;
}