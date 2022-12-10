#include "../includes/3-map/map.hpp"
#include <iostream>

#include <list>
#include <map>
int main() {

  time_t start = time(NULL);

  ft::map<char, int> myMap;

  std::list <std::map<char, int>::value_type> lst;
  std::map<char, int> mp(lst.begin(), lst.end());

  std::list <ft::map<char, int>::value_type> lst2;
  ft::map<char, int> mp2(lst2.begin(), lst2.end());


  time_t end = time(NULL);
  std::cout << "Time taken by program is:\t" << end - start << " seconds" << std::endl;
  return 0;
}

