#include "../includes/3-map/map.hpp"
#include <iostream>

int main() {

  // time to test the vector
  time_t start = time(NULL);

  ft::map<char, int> myMap;

  time_t end = time(NULL);
  std::cout << "Time taken by program is:\t" << end - start << " seconds" << std::endl;
  return 0;
}

