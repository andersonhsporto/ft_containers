#include "vector.hpp"

void testFtMap();
void testStdMap();

int main() {

  // time to test the vector
  time_t start = time(NULL);
  testStdMap();
  testFtMap();
  time_t end = time(NULL);
  std::cout << "Time taken by program is : " << end - start << " seconds" << std::endl;
  return 0;
}

#include <map>
#include "map.hpp"


void testStdMap() {

  std::map<int, int> map;

  map.insert(std::pair<int, int>(4, 4));
  map.insert(std::pair<int, int>(2, 2));
  map.insert(std::pair<int, int>(6, 6));

  std::cout << "std\t- map begin iterator: " << map.begin()->first << std::endl;
//  std::cout << "map end iterator: " << map.end()->first << std::endl;
}

void testFtMap() {

  ft::map<int, int> map;

  map.insert(ft::pair<int, int>(4, 4));
  map.insert(ft::pair<int, int>(2, 2));
  map.insert(ft::pair<int, int>(6, 6));

  std::cout << "ft\t- map begin iterator: " << map.begin()->first << std::endl;
//  std::cout << "map end iterator: " << map.end()->first << std::endl;
}

