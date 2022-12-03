#include "vector.hpp"

void testFtMap();

void testStdMap();

int main() {

  // time to test the vector
  time_t start = time(NULL);
  testFtMap();
  testStdMap();
  time_t end = time(NULL);
  std::cout << "Time taken by program is:\t" << end - start << " seconds" << std::endl;
  return 0;
}

#include <map>
#include <list>
#include "map.hpp"

void testStdMap() {
  std::cout << "\nstd map" << std::endl;

//  std::map<int, int> map;
//
//  map.insert(std::pair<int, int>(4, 4));
//  map.insert(std::pair<int, int>(2, 2));
//  map.insert(std::pair<int, int>(6, 6));
//
//
//  map.erase(2);
//
//  for (std::map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
//    std::cout << it->first << " " << it->second << std::endl;
//  }

  std::map<const char *, std::string> map2;

  map2["Hello"] = "world";
  map2["Olá"] = "mundo";
  map2["Bonjour"] = "monde";

  // Begin Iterator
  std::map<const char *, std::string>::iterator it = map2.begin();
  std::map<const char *, std::string>::iterator ite = map2.end();

  std::map<const char *, std::string>::const_iterator const_it = map2.begin();
  std::map<const char *, std::string>::const_iterator const_ite = map2.end();

  std::map<const char *, std::string>::reverse_iterator reverse_it = map2.rbegin();
  std::map<const char *, std::string>::reverse_iterator reverse_ite = map2.rend();

  std::map<const char *, std::string>::const_reverse_iterator const_reverse_it = map2.rbegin();
  std::map<const char *, std::string>::const_reverse_iterator const_reverse_ite = map2.rend();

  while (it != ite) {
    std::cout << it->first << " " << it->second << std::endl;
    it++;
  }

  std::cout << map2.empty() << std::endl;

  std::cout << map2.size() << std::endl;

  std::cout << map2.max_size() << std::endl;

  std::cout << map2["Hello"] << std::endl;

  std::cout << map2.at("Hello") << std::endl;

  std::cout << map2.count("Hello") << std::endl;

}

void testFtMap() {
  std::cout << "\nstart of ft map test" << std::endl;

//  ft::map<int, int> map;
//
//  map.insert(ft::pair<int, int>(4, 4));
//  map.insert(ft::pair<int, int>(2, 2));
//  map.insert(ft::pair<int, int>(6, 6));
//
//  map.erase(2);
//
////  for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
////    std::cout << it->first << " " << it->second << std::endl;
////  }

  ft::map<const char *, std::string> map2;

  map2["Hello"] = "world";
  map2["Olá"] = "mundo";
  map2["Bonjour"] = "monde";

  // Begin Iterator
  ft::map<const char *, std::string>::iterator it = map2.begin();
  ++it;
  it++;
  ft::map<const char *, std::string>::iterator ite = map2.end();

  ft::map<const char *, std::string>::const_iterator const_it = map2.begin();
  std::cout << "Teste Aqui Before -> " << const_it->second << std::endl;
  ++const_it;
  std::cout << "Teste Aqui After\n";
  const_it++;
  ft::map<const char *, std::string>::const_iterator const_ite = map2.end();

  ft::map<const char *, std::string>::reverse_iterator reverse_it = map2.rbegin();
  ft::map<const char *, std::string>::reverse_iterator reverse_ite = map2.rend();

  ft::map<const char *, std::string>::const_reverse_iterator const_reverse_it = map2.rbegin();
  ft::map<const char *, std::string>::const_reverse_iterator const_reverse_ite = map2.rend();

  while (it != ite) {
    std::cout << it->first << " " << it->second << std::endl;
    it++;
  }

  std::cout << map2.empty() << std::endl;

  std::cout << map2.size() << std::endl;

  std::cout << map2.max_size() << std::endl;

  std::cout << map2["Hello"] << std::endl;

  std::cout << map2.at("Hello") << std::endl;

  std::cout << map2.count("Hello") << std::endl;

  // Lower Bound
  ft::map<const char *, std::string>::iterator lower_bound = map2.lower_bound("Hello");

  std::cout << "Lower Bound -> " << lower_bound->first << " " << lower_bound->second << std::endl;

  // Upper Bound
  ft::map<const char *, std::string>::iterator upper_bound = map2.upper_bound("Hello");

  std::cout << "Upper Bound -> " << upper_bound->first << " " << upper_bound->second << std::endl;

  // Equal Range
  ft::pair<ft::map<const char *, std::string>::iterator,
           ft::map<const char *, std::string>::iterator> equal_range = map2.equal_range("Hello");

  std::cout << "Equal Range -> " << equal_range.first->first << " " << equal_range.first->second
            << std::endl;

  std::cout << "Get size of map: " << map2["Hello"].size() << '\n';

  std::cout << "Get letter 'o' -> " << map2["Hello"][1] << '\n'; // Saída: o


  ft::map<char, int> first;

  first['a'] = 10;
  first['b'] = 30;
  first['c'] = 50;
  first['d'] = 70;




}

