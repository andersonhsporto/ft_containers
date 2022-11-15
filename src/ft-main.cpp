#include "vector.hpp"

void testFtMap();

int main() {

  // time to test the vector
  time_t start;
  time_t end;

  start = time(NULL);
//  testFtVector();
  end = time(NULL);
  testFtMap();
  std::cout << "Time taken by program is : " << end - start << " seconds" << std::endl;
  return 0;
}

#include <map>

void testFtMap() {

  std::map<int, int> map;

  map.insert(std::pair<int, int>(1, 1));
  map.insert(std::pair<int, int>(2, 2));

  std::cout << map[1] << std::endl;
}

