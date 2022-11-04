//#include "./includes/Vector.hpp"
//#include "./includes/Colors.hpp"
//#include <vector>

#include <iostream>
#include <math.h>


int main() {
  std::vector<int> values;

  int t = std::stoi("123");

  values.push_back(1);
  values.push_back(2);
  values.push_back(3);
  values.push_back(4);
  values.push_back(5);

  std::cout << "Not using iterators" << std::endl;
  for (int i = 0; i < values.size(); i++) {
    std::cout << CYAN << values[i] << RESET << std::endl;
  }

    std::cout << "Using iterators" << std::endl;
  for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++) {
    std::cout << GREEN << *it << RESET << std::endl;
  }

  return 0;
}
