#include "./includes/Vector.hpp"
#include "./includes/Colors.hpp"
#include <vector>

void testVectorPushBack();

void testVectorOperatorEqual();

void testAssignIntVector();

void testVectorPushBack10K();

void testVectorSize();

void testVectorResize();

void testVectorCapacity();

int main() {
//  testVectorOperatorEqual();
//  testAssignIntVector();
//  testVectorPushBack();
//  testVectorPushBack10K();
//  testVectorSize();
//  testVectorResize();
//  testVectorCapacity();
  return 0;
}

void printIntVector(ft::vector<int> &vec) {
  std::cout << BLUE << "Vector content: " << RESET;
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << BLUE << vec[i] << " " << RESET;
  }
  std::cout << std::endl;
}

void printCharVector(ft::vector<char> &vec) {
  std::cout << BLUE << "Vector content: " << RESET;
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << BLUE << vec[i] << " " << RESET;
  }
  std::cout << std::endl;
}

void testVectorOperatorEqual() {
  std::cout << GREEN << "Test operator= using 0 to 9" << RESET << std::endl;

  ft::vector<int> vec1;
  ft::vector<int> vec2;

  for (int i = 0; i < 10; i++) {
    vec1.push_back(i);
  }

  vec2 = vec1;

  printIntVector(vec2);
}

void testAssignIntVector() {
  std::cout << GREEN << "Test assign member function " << RESET << std::endl;

  ft::vector<char> characters;

  std::cout << BLUE << "Assigning 5 'a' characters to the vector" << RESET << std::endl;
  characters.assign(5, 'a');
  printCharVector(characters);

  std::cout << BLUE << "Assigning 3 'b' characters to the vector using iterator" << RESET << std::endl;
  const std::string extra(6, 'b');
  characters.assign(extra.begin(), extra.end());
  printCharVector(characters);
}

void testVectorPushBack() {
  std::cout << GREEN << "\nVector push_back test using 0 to 10" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10; i++) {
    ft_vector.push_back(i);
  }

  printIntVector(ft_vector);
}

void testVectorPushBack10K() {
  std::cout << GREEN << "\nVector push_back test using 0 to 10K" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 10000; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
}

void testVectorSize() {
  std::cout << GREEN << "\nVector size test using 0 to 42" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 42; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
}

void testVectorResize() {
  std::cout << GREEN << "\nVector resize test using 0 to 15" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 15; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector before resize 10" << RESET << std::endl;
  printIntVector(ft_vector);

  ft_vector.resize(10);

  std::cout << CYAN << "Vector after resize 10" << RESET << std::endl;
  printIntVector(ft_vector);
}

void testVectorCapacity() {
  std::cout << GREEN << "\nVector capacity test using 0 to 15" << RESET << std::endl;

  ft::vector<int> ft_vector;

  for (int i = 0; i < 15; i++) {
    ft_vector.push_back(i);
  }

  std::cout << CYAN << "Vector size: " << ft_vector.size() << RESET << std::endl;
  std::cout << CYAN << "Vector max_size: " << ft_vector.max_size() << RESET << std::endl;
  std::cout << CYAN << "Vector capacity: " << ft_vector.capacity() << RESET << std::endl;
  std::cout << CYAN << "Vector is empty: " << ft_vector.empty() << RESET << std::endl;

  ft::vector<int> empty_vector;

  std::cout << CYAN << "\nEmpty vector size: " << empty_vector.size() << RESET << std::endl;
  std::cout << CYAN << "Empty vector max_size: " << empty_vector.max_size() << RESET << std::endl;
  std::cout << CYAN << "Empty vector capacity: " << empty_vector.capacity() << RESET << std::endl;
  std::cout << CYAN << "Empty vector is empty: " << empty_vector.empty() << RESET << std::endl;
}
