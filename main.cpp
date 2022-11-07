#include "./includes/Vector.hpp"
#include "./includes/Colors.hpp"
#include <vector>

void ft_vectorTest();

int main() {
//  std::vector<int> values;
//
//  values.push_back(1);
//  values.push_back(2);
//  values.push_back(3);
//  values.push_back(4);
//  values.push_back(5);
//
//  std::cout << "Not using iterators" << std::endl;
//  for (int i = 0; i < values.size(); i++) {
//    std::cout << CYAN << values[i] << RESET << std::endl;
//  }
//
//  std::cout << "Using iterators" << std::endl;
//  for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++) {
//    std::cout << GREEN << *it << RESET << std::endl;
//  }

  ft_vectorTest();
  return 0;
}

void ft_vectorTest() {
  ft::vector<int> values;

  std::cout << "ft_vectorTest" << std::endl;
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
  for (ft::vector<int>::iterator it = values.begin(); it != values.end(); it++) {
    std::cout << GREEN << *it << RESET << std::endl;
  }

}
